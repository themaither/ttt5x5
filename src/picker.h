/* picker.h: 5x5 level picker
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef PICKER_H_INCLUDED
#define PICKER_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

void picker_init     ();
void picker_update   ();
int  picker_leaving  ();
int  picker_starting ();
int  picker_reset    ();

#ifdef __cplusplus
}
#endif

#endif /* PICKER_H_INCLUDED */
