/* session.h: 5x5 game session
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef SESSION_H_INCLUDED
#define SESSION_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

extern int session_status;

void session_init    (void);
void session_update  (void);
int  session_leaving (void);
int  session_reset   (void);

#ifdef __cplusplus
}
#endif

#endif /* SESSION_H_INCLUDED */
