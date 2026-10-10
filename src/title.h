/* title.h: title screen
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef TITLE_H_INCLUDED
#define TITLE_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

void title_init     (void);
void title_update   (void);
void title_reset    (void);

int title_leaving (void);
int title_level_select (void);

#ifdef __cplusplus
}
#endif

#endif /* TITLE_H_INCLUDED */
