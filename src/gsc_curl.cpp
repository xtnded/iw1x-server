#include "gsc.h"

#if COMPILE_CURL == 1
struct WebhookData
{
    std::string url;
    std::string message;
};

void async_webhook_message(std::shared_ptr<WebhookData> data)
{
    CURL *curl;
    CURLcode responseCode;
    struct curl_slist *headers = NULL;
    std::string payload = "{\"content\":\"" + data->message + "\"}";

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl)
    {
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_URL, data->url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());

        responseCode = curl_easy_perform(curl);
        if(responseCode != CURLE_OK)
            Com_Printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(responseCode));

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
    else
        Com_Printf("curl_easy_init() failed\n");
    
    curl_global_cleanup();
}

void gsc_curl_webhookmessage()
{
    char *url;
    char *message;

    if (!stackGetParams("ss", &url, &message))
    {
        stackError("gsc_curl_webhookmessage() one or more arguments are undefined or have a wrong type");
        Scr_AddUndefined();
        return;
    }

    std::shared_ptr<WebhookData> data = std::make_shared<WebhookData>();
    data->url = url;
    data->message = message;

    std::thread(async_webhook_message, data).detach();

    Scr_AddBool(qtrue);  // Return true to indicate the async operation has started
}
#endif