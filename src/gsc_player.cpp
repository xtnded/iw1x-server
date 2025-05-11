#include "gsc.h"

extern cvar_t *player_sprintTime;

void gsc_player_setvelocity(scr_entref_t ref)
{
    int id = ref.entnum;
    vec3_t velocity;

    if (!stackGetParams("v", &velocity))
    {
        stackError("gsc_player_setvelocity() argument is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_setvelocity() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    playerState_t *ps = SV_GameClientNum(id);
    VectorCopy(velocity, ps->velocity);

    Scr_AddBool(qtrue);
}

void gsc_player_getvelocity(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_getvelocity() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    playerState_t *ps = SV_GameClientNum(id);

    Scr_AddVector(ps->velocity);
}

void gsc_player_getuserinfokey(scr_entref_t ref)
{
    int id = ref.entnum;
    char *key;

    if (!stackGetParams("s", &key))
    {
        stackError("gsc_player_getuserinfokey() argument is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_getuserinfokey() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    client_t *client = &svs.clients[id];
    char *val = Info_ValueForKey(client->userinfo, key);

    if (strlen(val))
        Scr_AddString(val);
    else
        Scr_AddString("");
}

void gsc_player_setuserinfokey(scr_entref_t ref)
{
    int id = ref.entnum;
    char *key, *value;

    if (!stackGetParams("ss", &key, &value))
    {
        stackError("gsc_player_setuserinfokey() one or more arguments is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_setuserinfokey() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    client_t *client = &svs.clients[id];
    Info_SetValueForKey(client->userinfo, key, value);

    Scr_AddBool(qtrue);
}

void gsc_player_button_ads(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_button_ads() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    Scr_AddBool(client->lastUsercmd.buttons & KEY_MASK_ADS_MODE ? qtrue : qfalse);
}

void gsc_player_button_left(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_button_left() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    Scr_AddBool(client->lastUsercmd.rightmove == KEY_MASK_MOVELEFT ? qtrue : qfalse);
}

void gsc_player_button_right(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_button_right() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    Scr_AddBool(client->lastUsercmd.rightmove == KEY_MASK_MOVERIGHT ? qtrue : qfalse);
}

void gsc_player_button_forward(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_button_forward() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    Scr_AddBool(client->lastUsercmd.forwardmove == KEY_MASK_FORWARD ? qtrue : qfalse);
}

void gsc_player_button_back(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_button_back() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    Scr_AddBool(client->lastUsercmd.forwardmove == KEY_MASK_BACK ? qtrue : qfalse);
}

void gsc_player_button_jump(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_button_jump() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    Scr_AddBool(client->lastUsercmd.upmove == KEY_MASK_JUMP ? qtrue : qfalse);
}

void gsc_player_button_leanleft(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_button_leanleft() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    client_t *client = &svs.clients[id];
    
    Scr_AddBool(client->lastUsercmd.wbuttons & KEY_MASK_LEANLEFT ? qtrue : qfalse);
}

void gsc_player_button_leanright(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_button_leanright() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    Scr_AddBool(client->lastUsercmd.wbuttons & KEY_MASK_LEANRIGHT ? qtrue : qfalse);
}

void gsc_player_button_reload(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_button_reload() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    Scr_AddBool(client->lastUsercmd.wbuttons & KEY_MASK_RELOAD ? qtrue : qfalse);
}

void gsc_player_getangles(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_getangles() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }
    
    playerState_t *ps = SV_GameClientNum(id);

    Scr_AddVector(ps->viewangles);
}

void gsc_player_getstance(scr_entref_t ref)
{
    int id = ref.entnum;
    
    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_getstance() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }
    
    playerState_t *ps = SV_GameClientNum(id);
    if(ps->eFlags & EF_CROUCHING)
        Scr_AddString("crouch");
    else if(ps->eFlags & EF_PRONE)
        Scr_AddString("prone");
    else
        Scr_AddString("stand");
}

void gsc_player_getip(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_getip() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    client_t *client = &svs.clients[id];
    char ip[16];
    
    snprintf(ip, sizeof(ip), "%d.%d.%d.%d",
        client->netchan.remoteAddress.ip[0],
        client->netchan.remoteAddress.ip[1],
        client->netchan.remoteAddress.ip[2],
        client->netchan.remoteAddress.ip[3]);

    Scr_AddString(ip);
}

void gsc_player_getping(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_getping() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    client_t *client = &svs.clients[id];
    Scr_AddInt(client->ping);
}

void gsc_player_processclientcommand(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_processclientcommand() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    ClientCommand(id);

    Scr_AddBool(qtrue);
}

void gsc_player_dropclient(scr_entref_t ref)
{
    int id = ref.entnum;
    char *reason;

    if (Scr_GetNumParam() > 0 && !stackGetParams("s", &reason))
    {
        stackError("gsc_player_dropclient() argument has a wrong type");
        Scr_AddUndefined();
        return;
    }

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_dropclient() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    if(Scr_GetNumParam() > 0)
        SV_DropClient(client, reason);
    else
        SV_DropClient(client, NULL);

    Scr_AddBool(qtrue);
}

void gsc_player_setspeed(scr_entref_t ref)
{
    int id = ref.entnum;
    int speed;

    if (!stackGetParams("i", &speed))
    {
        stackError("gsc_player_setspeed() argument is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_setspeed() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    if (speed < 0)
    {
        stackError("gsc_player_setspeed() param must be equal or above zero");
        Scr_AddUndefined();
        return;
    }

    customPlayerState[id].speed = speed;

    Scr_AddBool(qtrue);
}

void gsc_player_setgravity(scr_entref_t ref)
{
    int id = ref.entnum;
    int gravity;

    if (!stackGetParams("i", &gravity))
    {
        stackError("gsc_player_setgravity() argument is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_setgravity() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    if (gravity < 0)
    {
        stackError("gsc_player_setgravity() param must be equal or above zero");
        Scr_AddUndefined();
        return;
    }

    customPlayerState[id].gravity = gravity;

    Scr_AddBool(qtrue);
}

void gsc_player_getfps(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_getfps() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    Scr_AddInt(customPlayerState[id].fps);
}

void gsc_player_isonladder(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_isonladder() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    playerState_t *ps = SV_GameClientNum(id);

    Scr_AddBool(ps->pm_flags & PMF_LADDER ? qtrue : qfalse);
}

void gsc_player_noclip(scr_entref_t ref)
{
    int id = ref.entnum;
    char *noclip;

    if (!stackGetParams("s", &noclip))
    {
        stackError("gsc_player_noclip() argument is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_noclip() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    gentity_t *entity = &g_entities[id];

    if (!Q_stricmp(noclip, "on") || atoi(noclip))
    {
        entity->client->noclip = qtrue;
    }
    else if (!Q_stricmp(noclip, "off") || !Q_stricmp(noclip, "0"))
    {
        entity->client->noclip = qfalse;
    }
    else
    {
        entity->client->noclip = !entity->client->noclip;
    }

    Scr_AddBool(qtrue);
}

void gsc_player_ufo(scr_entref_t ref)
{
    int id = ref.entnum;
    char *ufo;

    if (!stackGetParams("s", &ufo))
    {
        stackError("gsc_player_ufo() argument is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_ufo() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    gentity_t *entity = &g_entities[id];

    if (!Q_stricmp(ufo, "on") || atoi(ufo))
    {
        entity->client->ufo = qtrue;
    }
    else if (!Q_stricmp(ufo, "off") || !Q_stricmp(ufo, "0"))
    {
        entity->client->ufo = qfalse;
    }
    else
    {
        entity->client->ufo = !entity->client->ufo;
    }

    Scr_AddBool(qtrue);
}

void gsc_player_connectionlesspackettoclient(scr_entref_t ref)
{
    int id = ref.entnum;
    char *cmd;

    if (!stackGetParams("s", &cmd))
    {
        stackError("gsc_player_connectionlesspackettoclient() argument is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_connectionlesspackettoclient() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    client_t *client = &svs.clients[id];
    NET_OutOfBandPrint(NS_SERVER, client->netchan.remoteAddress, cmd);

    Scr_AddBool(qtrue);
}

void gsc_player_setjumpheight(scr_entref_t ref)
{
    int id = ref.entnum;
    float jump_height;

    if (!stackGetParams("f", &jump_height))
    {
        stackError("gsc_player_setjumpheight() argument is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_setjumpheight() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    if(jump_height < 0)
        customPlayerState[id].overrideJumpHeight = false;
    else
    {
        customPlayerState[id].overrideJumpHeight = true;
        customPlayerState[id].jumpHeight = jump_height;
    }

    Scr_AddBool(qtrue);
}

void gsc_player_setairjumps(scr_entref_t ref)
{
    int id = ref.entnum;
    int airJumps;

    if (!stackGetParams("i", &airJumps))
    {
        stackError("gsc_player_setairjumps() argument is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_setairjumps() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    customPlayerState[id].airJumpsAvailable = airJumps;

    Scr_AddBool(qtrue);
}

void gsc_player_getairjumps(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_getairjumps() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    Scr_AddInt(customPlayerState[id].airJumpsAvailable);
}

void gsc_player_disableitemautopickup(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_disableitempickup() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    int old_setting = !customPlayerState[id].noAutoPickup;
    customPlayerState[id].noAutoPickup = true;

    Scr_AddInt(old_setting);
}

void gsc_player_enableitemautopickup(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_enableitempickup() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    int old_setting = !customPlayerState[id].noAutoPickup;
    customPlayerState[id].noAutoPickup = false;

    Scr_AddInt(old_setting);
}

void gsc_player_getsprintremaining(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_getsprintremaining() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }
    
    float sprint_time = player_sprintTime->value * 1000.0;
    int timeUsed = customPlayerState[id].sprintTimer;
    int timeRemaining = sprint_time - timeUsed;
    
    Scr_AddInt(timeRemaining);
}

void gsc_player_playscriptanimation(scr_entref_t ref)
{
    int id = ref.entnum;
    int scriptAnimEventType;
    int isContinue;
    int force;

    if (!stackGetParams("iii", &scriptAnimEventType, &isContinue, &force))
    {
        stackError("gsc_player_playscriptanimation() argument is undefined or has a wrong type");
        Scr_AddUndefined();
        return;
    }

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_playscriptanimation() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    if (scriptAnimEventType < 0 || scriptAnimEventType >= NUM_ANIM_EVENTTYPES)
    {
        stackError("gsc_player_playscriptanimation() argument is not a valid scriptAnimEventType");
        Scr_AddUndefined();
        return;
    }
    
    gentity_t *entity = &g_entities[id];

    Scr_AddInt(BG_AnimScriptEvent(&entity->client->ps, (scriptAnimEventTypes_t)scriptAnimEventType, isContinue, force));
}

void gsc_player_isbot(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_isbot() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    Scr_AddBool(client->bIsTestClient);
}
void gsc_player_sethiddenfromscoreboard(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_sethiddenfromscoreboard() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    bool hidden = Scr_GetInt(0);
    customPlayerState[id].hiddenFromScoreboard = hidden;

    Scr_AddBool(true);
}

void gsc_player_ishiddenfromscoreboard(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_ishiddenfromscoreboard() entity %i is not a player", id);
        Scr_AddUndefined();
        return;
    }

    Scr_AddBool(customPlayerState[id].hiddenFromScoreboard);
}