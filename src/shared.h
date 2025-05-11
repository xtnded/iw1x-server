#ifndef SHARED_H
#define SHARED_H

#include "pch.h"

#include "types.h"
#include "functions.h"

extern uintptr_t resume_addr_Jump_Check;
extern uintptr_t resume_addr_Jump_Check_2;

extern customPlayerState_t customPlayerState[MAX_CLIENTS];

__attribute__ ((naked)) void hook_Jump_Check_Naked();
__attribute__ ((naked)) void hook_Jump_Check_Naked_2();

xfunction_t Scr_GetCustomFunction(const char **fname, qboolean *fdev);
xmethod_t Scr_GetCustomMethod(const char **fname, qboolean *fdev);

void Scr_CodeCallback_Error(qboolean terminal, qboolean emit, const char *internal_function, char *message);

void free_sqlite_db_stores_and_tasks();

#endif