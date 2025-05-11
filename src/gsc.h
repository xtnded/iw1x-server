#ifndef GSC_H
#define GSC_H

#include "shared.h"

#define STACK_UNDEFINED 0
#define STACK_STRING 1
#define STACK_LOCALIZED_STRING 2
#define STACK_VECTOR 3
#define STACK_FLOAT 4
#define STACK_INT 5
#define STACK_OBJECT 7
#define STACK_FUNCTION 9

const char * stackGetParamTypeAsString(int param);
int stackGetParams(const char *params, ...);
void stackError(const char *format, ...);

int stackGetParamInt(int param, int *value);
int stackGetParamFunction(int param, int *value);
int stackGetParamString(int param, char **value);
int stackGetParamConstString(int param, unsigned int *value);
int stackGetParamLocalizedString(int param, char **value);
int stackGetParamVector(int param, vec3_t value);
int stackGetParamFloat(int param, float *value);
int stackGetParamObject(int param, unsigned int *value);

//// For tests
void gsc_testfunction();
void gsc_testmethod(scr_entref_t ref);
////

//// Entity
void gsc_entity_setbounds(scr_entref_t ref);
void gsc_entity_setclipmask(scr_entref_t ref);
void gsc_entity_getclipmask(scr_entref_t ref);
void gsc_entity_showtoplayer(scr_entref_t ref);
////

//// Player
void gsc_player_setvelocity(scr_entref_t ref);
void gsc_player_getvelocity(scr_entref_t ref);
void gsc_player_button_ads(scr_entref_t ref);
void gsc_player_button_left(scr_entref_t ref);
void gsc_player_button_right(scr_entref_t ref);
void gsc_player_button_forward(scr_entref_t ref);
void gsc_player_button_back(scr_entref_t ref);
void gsc_player_button_jump(scr_entref_t ref);
void gsc_player_button_leanleft(scr_entref_t ref);
void gsc_player_button_leanright(scr_entref_t ref);
void gsc_player_button_reload(scr_entref_t ref);
void gsc_player_getangles(scr_entref_t ref);
void gsc_player_getstance(scr_entref_t ref);
void gsc_player_getuserinfokey(scr_entref_t ref);
void gsc_player_setuserinfokey(scr_entref_t ref);
void gsc_player_getip(scr_entref_t ref);
void gsc_player_getping(scr_entref_t ref);
void gsc_player_processclientcommand(scr_entref_t ref);
void gsc_player_dropclient(scr_entref_t ref);
void gsc_player_setspeed(scr_entref_t ref);
void gsc_player_setjumpheight(scr_entref_t ref);
void gsc_player_setgravity(scr_entref_t ref);
void gsc_player_setairjumps(scr_entref_t ref);
void gsc_player_getairjumps(scr_entref_t ref);
void gsc_player_getfps(scr_entref_t ref);
void gsc_player_isonladder(scr_entref_t ref);
void gsc_player_noclip(scr_entref_t ref);
void gsc_player_ufo(scr_entref_t ref);
void gsc_player_connectionlesspackettoclient(scr_entref_t ref);
void gsc_player_disableitemautopickup(scr_entref_t ref);
void gsc_player_enableitemautopickup(scr_entref_t ref);
void gsc_player_getsprintremaining(scr_entref_t ref);
void gsc_player_playscriptanimation(scr_entref_t ref);
void gsc_player_isbot(scr_entref_t ref);
void gsc_player_sethiddenfromscoreboard(scr_entref_t ref);
void gsc_player_ishiddenfromscoreboard(scr_entref_t ref);
////

//// Bots
void gsc_bots_setwalkvalues(scr_entref_t id);
void gsc_bots_setwalkdir(scr_entref_t id);
void gsc_bots_setbotstance(scr_entref_t id);
void gsc_bots_setlean(scr_entref_t id);
void gsc_bots_setaim(scr_entref_t id);
void gsc_bots_fireweapon(scr_entref_t id);
void gsc_bots_meleeweapon(scr_entref_t id);
void gsc_bots_reloadweapon(scr_entref_t id);
void gsc_bots_switchtoweaponid(scr_entref_t id);
////

//// Weapons
void gsc_weapons_setweaponcookable();
void gsc_weapons_setweaponfusetime();
////

//// Utils
#if COMPILE_SSL == 1
#include <openssl/evp.h>
void gsc_utils_hash();
#endif

void gsc_utils_file_exists();
void gsc_utils_fopen();
void gsc_utils_fread();
void gsc_utils_fwrite();
void gsc_utils_fclose();

void gsc_utils_sendcommandtoclient();
void gsc_utils_logprintconsole();
void gsc_utils_getsubstr();
void gsc_utils_getascii();
void gsc_utils_toupper();
void gsc_utils_tolower();
void gsc_utils_strtok();
void gsc_utils_replace();
void gsc_utils_getserverstarttime();
void gsc_utils_getsystemtime();
void gsc_utils_strftime();
void gsc_utils_getconfigstring();
void gsc_utils_makelocalizedstring();
void gsc_utils_getlocalizedstringindex();
void gsc_utils_makeupdatedlocalizedstring();
void gsc_utils_ban();
void gsc_utils_unban();
void gsc_utils_strip();
void gsc_utils_strstr();
void gsc_utils_monotone();
void gsc_utils_gettype();
////

//// Exec
void gsc_exec();
void gsc_exec_async_create();
void gsc_exec_async_create_nosave();
void gsc_exec_async_checkdone();
////

#if COMPILE_CURL == 1
#include <curl/curl.h>
#include <thread>
#include <memory>
void gsc_curl_webhookmessage();
#endif

//// SQLite
void gsc_sqlite_open();
void gsc_sqlite_query();
void gsc_sqlite_close();
void gsc_sqlite_escape_string();
void gsc_sqlite_databases_count();
void gsc_sqlite_tasks_count();

void gsc_async_sqlite_initialize();
void gsc_async_sqlite_create_query();
void gsc_async_sqlite_create_query_nosave();
void gsc_async_sqlite_checkdone();
void gsc_async_sqlite_create_entity_query(scr_entref_t entid);
void gsc_async_sqlite_create_entity_query_nosave(scr_entref_t entid);
////

#endif