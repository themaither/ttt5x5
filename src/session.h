/* session.h: 5x5 game session
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef SESSION_H_INCLUDED
#define SESSION_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

extern int session_status;

void session_init    ();
void session_update  ();
int  session_leaving ();
int  session_reset   ();

#ifdef __cplusplus
}
#endif

#endif /* SESSION_H_INCLUDED */
