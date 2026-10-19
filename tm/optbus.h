/* optbus.h: Definitions for simple argument parsing api.
   Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef TMLIB_OPTBUS_H_INCLUDED
#define TMLIB_OPTBUS_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

/* Should be called before library is used. */
void optbus_init (void);

/* Automatically import all dependencies and init */
void autodep_optbus_init (void);

/* Sets a message shown if --help is called. */
void optbus_doc (const char *doc);

/* Pushes an argument.  When --'name' is passed as an argument, 'handler' is
   called.  If 'doc' is not null a small notice appears if --help is passed. */
void optbus_push (const char *name, const char *doc, void (*handler)(void));

/* Does the parsing. 'argc' and 'argv' are argument you get from main. */
void optbus_parse (int argc, char **argv);

#ifdef __cplusplus
}
#endif

#endif /* TMLIB_OPTBUS_H_INCLUDED */
