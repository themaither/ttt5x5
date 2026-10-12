/* strdupf.h: strdup with formatting
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef STRDUP_H_INCLUDED
#define STRDUP_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/* returned string should be freed using free */
char * strdupf (const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* STRDUP_H_INCLUDED */
