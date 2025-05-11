#include "shared.h"

#include "hook.h"

static void ban();
static void unban();
std::tuple<bool, int, int, std::string> getBanInfoForIp(char* ip);
void UCMD_custom_sprint(client_t *cl);