/* picker.h: 5x5 level picker
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef PICKER_H_INCLUDED
#define PICKER_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

void picker_init     (void);
void picker_update   (void);
int  picker_leaving  (void);
int  picker_starting (void);
int  picker_reset    (void);

#ifdef __cplusplus
}
#endif

#endif /* PICKER_H_INCLUDED */
