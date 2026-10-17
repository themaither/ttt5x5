/* dlf.h: document-line-field writer and reader
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef DLF_H_INCLUDED
#define DLF_H_INCLUDED

#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* Should be called before any further functions */
void dlf_init (void);

void autodep_dlf_init (void);

/* Puts a field */
void fdlputs (FILE *, const char *field);

/* Puts a field with an integer */
void fdlputi (FILE *, int);

/* Flushes line */
void fdline (FILE *);

/* Sets a sink, where text is written. stdout by default */
void dlf_setsink (FILE *f);

/* Get current sink stream */
FILE *dlf_sink (void);

/* Puts a field into sink */
void dlputs (const char *field);

/* Puts a field with an integer into sink*/
void dlputi (int);

/* Flushes a line */
void dline (void);

/* Sets a source stream, where all input is read. stdin by default */
void dlf_setsource (FILE *f);

/* Get current source stream */
FILE *dlf_source (void);

/* Get next line. Should be called BEFORE dlgets and similar */
int dlnext (void);

/* Gets a field from source stream. Return value points to internal buffer,
 * which can be overwritten by further calls. */
const char *dlgets (void);

/* Gets rest of the fields left separate by space from source stream.
   Return value points to internal buffer, which can be overwritten by
   further calls. */
const char *dlrest (void);

/* Get line number */
int dlf_ln (void);

/* Get field number */
int dlf_fn (void);

/* Sets source name. Generally it's just a path to the file being read.
   Used only in dlf_errorf*/
void dfl_setsourcename (const char *);

/* Print an error message associated with previously read field. */
void dlf_errorf (const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* DLF_H_INCLUDED */
