/* gamescript.h: dlf gamescript engine
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef GAMESCRIPT_H_INCLUDED
#define GAMESCRIPT_H_INCLUDED

#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

void gamescript_register (const char *command, void (*fn)());

/* reads from dlf stream */
void eval ();

#ifdef __cplusplus
}
#endif

#endif /* GAMESCRIPT_H_INCLUDED */
