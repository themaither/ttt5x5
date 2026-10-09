/* dlf.h: document-line-field writer and reader
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef DLF_H_INCLUDED
#define DLF_H_INCLUDED

#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

void dlf_init ();

void fdlputs (FILE *, const char *field);
void fdlputi (FILE *, int);
void fdline (FILE *);

void dlf_setsink (FILE *f);
FILE *dlf_sink ();
void dlputs (const char *field);
void dlputi (int);
void dline ();

void dlf_setsource (FILE *f);
FILE *dlf_source ();
int dlnext ();
const char * dlgets ();
int dlf_ln ();
int dlf_fn ();

#ifdef __cplusplus
}
#endif

#endif /* DLF_H_INCLUDED */
