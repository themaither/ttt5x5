/* gamescript.h: dlf gamescript engine
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef GAMESCRIPT_H_INCLUDED
#define GAMESCRIPT_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

/* reads line from dlf source, returns -1 on eof */
int eval (void);

#ifdef __cplusplus
}
#endif

#endif /* GAMESCRIPT_H_INCLUDED */
