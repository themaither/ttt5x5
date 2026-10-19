/* string.h: Definition of 'strdupf'
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef TMLIB_STRDUPF_H_INCLUDED
#define TMLIB_STRDUPF_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

/* Allocate an formatted string.  Returned value should be freed using
  'free' function. */
char * strdupf (const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* TMLIB_STRDUPF_H_INCLUDED */
