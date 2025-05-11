#include "gsc.h"

void gsc_utils_sendcommandtoclient()
{
    int clientNum;
    char *message;

    if (!stackGetParams("is", &clientNum, &message))
    {
        stackError("gsc_utils_sendcommandtoclient() one or more arguments is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }

    trap_SendServerCommand(clientNum, SV_CMD_CAN_IGNORE, message);
    Scr_AddBool(qtrue);
}

void gsc_utils_logprintconsole()
{
    char *str;

    if (!stackGetParams("s", &str))
    {
        stackError("gsc_utils_logprintconsole() argument is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }

    if (!strlen(str) || strlen(str) > MAX_STRINGLENGTH)
    {
        stackError("gsc_utils_logprintconsole() invalid string length");
        Scr_AddUndefined();
        return;
    }

    Com_Printf("%s", str);

    Scr_AddBool(qtrue);
}

void gsc_utils_getsubstr()
{
    int end;
    char c;
    int i;
    int source;
    int start;
    const char *string;
    char tempString[1024];

    string = Scr_GetString(0);
    start = Scr_GetInt(1u);

    if (Scr_GetNumParam() <= 2)
        end = 0x7FFFFFFF;
    else
        end = Scr_GetInt(2u);

    source = start;

    for (i = 0; source < end; ++i)
    {
        if (i > 1023)
            stackError("gsc_utils_getsubstr() string too long");

        c = string[source];

        if (!c)
            break;

        tempString[i] = c;
        ++source;
    }

    tempString[i] = 0;
    Scr_AddString(tempString);
}

void gsc_utils_getascii()
{
    char *str;

    if (!stackGetParams("s", &str))
    {
        stackError("gsc_utils_getascii() argument is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }

    if (!strlen(str))
    {
        stackError("gsc_utils_getascii() string length is 0");
        Scr_AddUndefined();
        return;
    }

    Scr_AddInt(str[0]);
}

void gsc_utils_toupper()
{
    char *str;

    if (!stackGetParams("s", &str))
    {
        stackError("gsc_utils_toupper() argument is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }

    if (!strlen(str))
    {
        stackError("gsc_utils_toupper() string length is 0");
        Scr_AddUndefined();
        return;
    }

    Scr_AddString(Q_strupr(str));
}

void gsc_utils_tolower() // From cod2rev
{
    char c;
    int i;
    const char *string;
    char tempString[MAX_STRINGLENGTH];

    if (!stackGetParams("s", &string))
    {
        stackError("gsc_utils_tolower() argument is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }

    for (i = 0; i < MAX_STRINGLENGTH; ++i)
    {
        c = tolower(*string);
        tempString[i] = c;

        if (!c)
        {
            Scr_AddString(tempString);
            return;
        }

        ++string;
    }

    stackError("gsc_utils_tolower() string too long");
}

void gsc_utils_strtok() // From cod2rev
{
    signed int j;
    char c;
    int dest;
    int i;
    signed int len;
    const char *tok;
    const char *delim;
    char tempString[1024];

    delim = Scr_GetString(0);
    tok = Scr_GetString(1u);
    len = strlen(tok);
    dest = 0;

    Scr_MakeArray();

    for (i = 0; ; ++i)
    {
        c = delim[i];

        if (!c)
            break;

        for (j = 0; j < len; ++j)
        {
            if (c == tok[j])
            {
                if (dest)
                {
                    tempString[dest] = 0;
                    Scr_AddString(tempString);
                    Scr_AddArray();
                    dest = 0;
                }

                goto skip;
            }
        }

        tempString[dest] = c;

        if (++dest > 1023)
            stackError("gsc_utils_strtok() string too long");
skip:
        ;
    }

    if (dest)
    {
        tempString[dest] = 0;
        Scr_AddString(tempString);
        Scr_AddArray();
    }
}

void gsc_utils_replace() //TODO: check if needs improvements
{
    char* orig;
    char* rep;
    char* with;

    if (!stackGetParams("sss", &orig, &rep, &with))
    {
        stackError("gsc_utils_replace() one or more arguments is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }
    
    char *result; // the return string
    char *ins; // the next insert point
    char *tmp; // varies
    int len_rep; // length of rep
    int len_with; // length of with
    int len_front; // distance between rep and end of last rep
    int count; // number of replacements

    if (!orig)
        return;
    if (!rep || !(len_rep = strlen(rep)))
        return;
    if (!(ins = strstr(orig, rep))) 
        return;
    if (!with)
        with = (char*)"";
    len_with = strlen(with);

    for (count = 0; (tmp = strstr(ins, rep)); ++count) {
        ins = tmp + len_rep;
    }

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    tmp = result = (char*)malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return;

    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    
    Scr_AddString(result);
}

void gsc_utils_file_exists()
{
    char *filename;

    if (!stackGetParams("s", &filename))
    {
        stackError("gsc_utils_file_exists() argument is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }

    int file_exists = access(filename, F_OK) != -1;
    Scr_AddInt(file_exists);
}

void gsc_utils_fopen()
{
    FILE *file;
    char *filename, *mode;

    if (!stackGetParams("ss", &filename, &mode))
    {
        stackError("gsc_utils_fopen() one or more arguments is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }

    file = fopen(filename, mode);

    if (!file)
    {
        stackError("gsc_utils_fopen() returned an error");
        Scr_AddUndefined();
        return;
    }

    Scr_AddInt((int)file);
}

void gsc_utils_fread()
{
    FILE *file;

    if (!stackGetParams("i", &file))
    {
        stackError("gsc_utils_fread() argument is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }

    if (!file)
    {
        stackError("gsc_utils_fread() returned an error");
        Scr_AddUndefined();
        return;
    }

    char buffer[256];
    int ret = fread(buffer, 1, 255, file);

    if (!ret)
    {
        Scr_AddUndefined();
        return;
    }

    buffer[ret] = '\0';
    Scr_AddString(buffer);
}

void gsc_utils_fwrite()
{
    FILE *file;
    char *buffer;

    if (!stackGetParams("is", &file, &buffer))
    {
        stackError("gsc_utils_fwrite() one or more arguments is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }

    if (!file)
    {
        stackError("gsc_utils_fwrite() returned an error");
        Scr_AddUndefined();
        return;
    }

    Scr_AddInt(fwrite(buffer, 1, strlen(buffer), file));
}

void gsc_utils_fclose()
{
    FILE *file;

    if (!stackGetParams("i", &file))
    {
        stackError("gsc_utils_fclose() argument is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }

    if (!file)
    {
        stackError("gsc_utils_fclose() returned an error");
        Scr_AddUndefined();
        return;
    }

    Scr_AddInt(fclose(file));
}

static int starttime = time(NULL);
void gsc_utils_getserverstarttime()
{
    Scr_AddInt(starttime);
}

void gsc_utils_getsystemtime()
{
    time_t timer;
    Scr_AddInt(time(&timer));
}

void gsc_utils_strftime()
{
    int timestamp;
    char *timezone;
    char *format;
    
    if (!stackGetParams("iss", &timestamp, &timezone, &format))
    {
        stackError("gsc_utils_strftime() one or more arguments is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }

    time_t rawTime = timestamp;
    struct tm *timeInfo;

    if(!strcmp(timezone, "utc"))
        timeInfo = gmtime(&rawTime);
    else if(!strcmp(timezone, "local"))
        timeInfo = localtime(&rawTime);
    else
    {
        stackError("gsc_utils_strftime() invalid argument '%s'. Valid arguments are: 'utc' 'local'", timezone);
        Scr_AddUndefined();
        return;
    }

    char buffer[100];
    if(strftime(buffer, sizeof(buffer), format, timeInfo))
        Scr_AddString(buffer);
    else
    {
        stackError("gsc_utils_strftime() failed to format time");
        Scr_AddUndefined();
    }
}

void gsc_utils_getconfigstring()
{
    int index;

    if (!stackGetParams("i", &index))
    {
        stackError("gsc_utils_getconfigstring() argument is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }
    
    if (index < 0 || index >= MAX_CONFIGSTRINGS)
    {
        stackError("gsc_utils_getconfigstring() configstring index is out of range");
        Scr_AddUndefined();
        return;
    }

    const char *string = trap_GetConfigstringConst(index);

    if (!*string)
        Scr_AddUndefined();
    else
        Scr_AddString(string);
}

void gsc_utils_makelocalizedstring()
{
    char *str;

    if (!stackGetParams("s", &str))
    {
        stackError("gsc_utils_makelocalizedstring() argument is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }

    Scr_AddString(str);

    VariableValue *var;
    int param = 0;

    var = &scrVmPub.top[-param];
    var->type = STACK_LOCALIZED_STRING;
}

void gsc_utils_getlocalizedstringindex()
{
    char *str;

    if (!stackGetParams("l", &str))
    {
        stackError("gsc_utils_getlocalizedstringindex() argument is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }

    Scr_AddInt(G_LocalizedStringIndex(str));
}

void gsc_utils_makeupdatedlocalizedstring()
{
    char *str;
    int index;
    
    if (!stackGetParams("si", &str, &index))
    {
        stackError("gsc_utils_makeupdatedlocalizedstring() argument is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }
    
    trap_SetConfigstring(index + 1244, str);
    
    Scr_AddString(str);

    VariableValue *var;
    int param = 0;

    var = &scrVmPub.top[-param];
    var->type = STACK_LOCALIZED_STRING;
}

void gsc_utils_ban()
{
    int numParam = Scr_GetNumParam();
    if (numParam)
    {
        std::string command = "ban";
        command.append(" ");
        for (int i = 0; i < numParam; i++)
        {
            std::string param = Scr_GetString(i);
            command.append(param);
        }
        Cbuf_ExecuteText(EXEC_APPEND, va(command.c_str()));
    }
}

void gsc_utils_unban()
{
    int numParam = Scr_GetNumParam();
    if (numParam)
    {
        std::string command = "unban";
        command.append(" ");
        for (int i = 0; i < numParam; i++)
        {
            std::string param = Scr_GetString(i);
            command.append(param);
        }
        Cbuf_ExecuteText(EXEC_APPEND, va(command.c_str()));
    }
}

void gsc_utils_strip() 
{
    const char *input;
    char result[256] = {0};
    int start = 0, end = 0, i = 0;

    if(!stackGetParams("s", &input)) 
    {
        stackError("gsc_utils_strip() argument is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }
    
    while(input[start] == ' ') 
    {
        start++;
    }

    if(input[start] == '\0') 
    {
        Scr_AddString("");
        return;
    }

    end = strlen(input) - 1;
    while(input[end] == ' ') 
    {
        end--;
    }

    for(i = start; i <= end; i++) 
    {
        result[i - start] = input[i];
    }

    Scr_AddString(result);
}

void gsc_utils_strstr() 
{
    const char *str, *sub;
    
    if(!stackGetParams("ss", &str, &sub)) 
    {
        stackError("gsc_utils_pmatch() arguments are undefined or have a wrong type");
        Scr_AddUndefined();
        return;
    }

    if (strstr(str, sub) != NULL) 
    {
        Scr_AddBool(qtrue);
    } 
    else 
    {
        Scr_AddBool(qfalse);
    }
}

void gsc_utils_monotone() 
{
    char *input;

    if(!stackGetParams("s", &input)) 
    {
        stackError("gsc_utils_monotone() argument is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }

    char buffer[256];
    strncpy(buffer, input, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    char *src = buffer, *dst = buffer;
    while (*src) {
        if (*src == '^') {
            if (*(src + 1) == '^' && (*(src + 2) >= '0' && *(src + 2) <= '7') && (*(src + 3) >= '0' && *(src + 3) <= '7')) {
                src += 4;
            }
            else if (*(src + 1) == '^' && (*(src + 2) >= '0' && *(src + 2) <= '7')) {
                src += 3;
            }
            else if (*(src + 1) >= '0' && *(src + 1) <= '7') {
                src += 2;
            } 
            else {
                *dst++ = *src++;
            }
        } else {
            *dst++ = *src++;
        }
    }
    *dst = '\0';

    Scr_AddString(buffer);
}

void gsc_utils_gettype()
{
    if (Scr_GetNumParam() == 0)
    {
        stackError("gsc_utils_gettype() argument is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }

    Scr_AddString(stackGetParamTypeAsString(0));
}

#if COMPILE_SSL == 1
void gsc_utils_hash()
{
    const char *input;
    int _len; //thanks iBuddie

    if(!stackGetParams("si", &input, &_len))
    {
        stackError("gsc_utils_hash() argument is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }
    if(_len > 64) {
        _len = 64;
    }
    char hashed_str[65];  // 64 characters + null terminator

    EVP_MD_CTX *mdctx;
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;

    mdctx = EVP_MD_CTX_new();
    if(mdctx == NULL)
    {
        stackError("Failed to create EVP_MD_CTX");
        Scr_AddUndefined();
        return;
    }

    if(EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) != 1)
    {
        EVP_MD_CTX_free(mdctx);
        stackError("Failed to initialize digest");
        Scr_AddUndefined();
        return;
    }

    if(EVP_DigestUpdate(mdctx, input, strlen(input)) != 1)
    {
        EVP_MD_CTX_free(mdctx);
        stackError("Failed to update digest");
        Scr_AddUndefined();
        return;
    }

    if(EVP_DigestFinal_ex(mdctx, hash, &hash_len) != 1)
    {
        EVP_MD_CTX_free(mdctx);
        stackError("Failed to finalize digest");
        Scr_AddUndefined();
        return;
    }

    for(unsigned int i = 0; i < hash_len; i++)
    {
        sprintf(hashed_str + (i * 2), "%02x", hash[i]);
    }
    hashed_str[hash_len * 2] = 0;

    EVP_MD_CTX_free(mdctx);

    hashed_str[_len] = '\0';

    Scr_AddString(hashed_str);
}
#endif