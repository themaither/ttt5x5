/* picker.h: 5x5 level picker
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef PICKER_H_INCLUDED
#define PICKER_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

/* Should be called before library is used. */
void picker_init         (void);
void autodep_picker_init (void);

/* Should be called after graphical context was initialized. */
void picker_ginit         (void);
void autodep_picker_ginit (void);

void picker_update (void);
void picker_reset  (void);

int  picker_leaving  (void);
int  picker_starting (void);

#ifdef __cplusplus
}
#endif

#endif /* PICKER_H_INCLUDED */
