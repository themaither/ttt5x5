/* dlf.h: document-line-field writer
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef DLF_H_INCLUDED
#define DLF_H_INCLUDED

#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

extern FILE *dlf_sink;

void dlf_init ();

void fdlputs (FILE *, const char *field);

void fdlputi (FILE *, int);

void fdline (FILE *);

void dlputs (const char *field);

void dlputi (int);

void dline ();

#ifdef __cplusplus
}
#endif

#endif /* DLF_H_INCLUDED */
