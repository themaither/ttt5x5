/* session.h: 5x5 game session
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef SESSION_H_INCLUDED
#define SESSION_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

extern int session_status;

/* Should be called before library is used. */
void session_init         (void);
void autodep_session_init (void);

/* Should be called after graphical context was initialized. */
void session_ginit         (void);
void autodep_session_ginit (void);

void session_update (void);
void session_reset  (void);

int  session_leaving (void);

#ifdef __cplusplus
}
#endif

#endif /* SESSION_H_INCLUDED */
