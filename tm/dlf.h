/* dlf.h: Document-Line-Field writer and reader.
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef TMLIB_DLF_H_INCLUDED
#define TMLIB_DLF_H_INCLUDED

#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* Should be called before any further functions. */
void dlf_init (void);

/* Automatically import all dependencies and init. */
void autodep_dlf_init (void);

/* Sets a sink, where text is written.  Set to 'stdout' by default. */
void dlf_setsink (FILE *f);

/* Pushes a sink.  Previous sink can be restored by calling 'dlf_popsink'. */
void dlf_pushsink (FILE *f);

void dlf_setsink_manual (void);

void dlf_pushsink_manual (void);

void dlf_popsink (void);

/* Returns a line flushed by dline.  Returned value should be freed using
   'free'. */
char *dlf_eat (void);

/* Puts a field into a line.  To write a line use 'dline'. */
void dlputs (const char *field);

/* Puts a field with an integer into sink. */
void dlputi (int);

/* Flushes a line to stream, selected by 'dlf_setsink' (stdout by default). */
void dline (void);

/* Sets a source stream, where all input is read. 'stdin' by default.
   This function does not preserve current source state, Setting source to
   previous stream would mean "start from beginning".  To preserve current
   source state use 'dlf_pushsource'. */
void dlf_setsource (FILE *);

/* Pushes a file to source stack.  After file was fully read, source return
   to previous file with all state intact. Previous source can be returned by
   calling 'dlf_popsource'. */
void dlf_pushsource (FILE *);

void dlf_setsource_manual (void);

void dlf_pushsource_manual (void);

/* Pops last source, returning to previous file with all it's state. */
void dlf_popsource (void);

void dlf_feed (const char *);

/* Sets source name. Generally it's just a path to the file being read.
   Used only in 'dlf_errorf'. */
void dlf_setsourcename (const char *);

/* When source reaches EOF, 'dlnext', instead of returning EOF, pops a
   source stack and continues reading like nothing happened.  Usefull for
   making file includes.

   If this function is called, there should not be
   a call to 'dlf_popsource' because this function pops automatically, and
   calling 'dlf_popsource' would mean to pop twice. */
void dlf_source_autowrap (void);

/* Note to use asynchronous reading mode.  In this mode, 'dlnext' polls source
   stream before reading.  If source stream has nothing to read, 'dlnext'
   returns 'DLNEXT_EOF', described by 'DLNEXT_RESULT' enum. */
void dlf_async (void);

/* Note to use synchronous reading mode.  In this mode, call to dlnext blocks
   program until line is read. */
void dlf_sync (void);

/* Note to use interactive mode.  This will enable all interactive stuff
   like history, keybinds, and of course label before each line. */
void dlf_interactive (void);

/* Note to use noninteractive mode.  Used to read any file and is set
   by default. */
void dlf_noninteractive (void);

/* Get next line. Should be called BEFORE dlgets and similar.  Returns values
   described in 'DLNEXT_RESULT'. */
int dlnext (void);

/* Values, which can be returned from 'dlnext'. */
enum DLNEXT_RESULT
{
  /* Can be recovered from by calling 'dlf_setsource'. */
  DLNEXT_EOF     = 0,

  /* You're doomed. */
  DLNEXT_ERROR   = 0,

  /* Parsing functions are good to call. */
  DLNEXT_OK      = 1,

  /* Line was not read.  Only appears in asynchronous mode. */
  DLNEXT_NOTAVAIL = 2
};

/* Gets a field from source stream. Return value points to internal buffer,
   which can be overwritten by further calls. */
const char *dlgets (void);

/* Gets rest of the fields left separate by space from source stream.
   Return value points to internal buffer, which can be overwritten by
   further calls. */
const char *dlrest (void);

/* Get line number. */
int dlf_ln (void);

/* Get field number. */
int dlf_fn (void);


/* Print an error message associated with previously read field. */
void dlf_errorf (const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* TMLIB_DLF_H_INCLUDED */
