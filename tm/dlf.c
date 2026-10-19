#include <config.h>

#include "dlf.h"

#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <string-buffer.h>
#include <assert.h>

#ifndef TMLIB_USE_READLINE
#define TMLIB_USE_READLINE 1
#endif /* TMLIB_USE_READLINE */

#if TMLIB_USE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif /* TMLIB_USE_READLINE */


struct source_state
{
  FILE *file;

  /* Name shown in error messages. */
  char *name;

  /* If set to 1, 'dlnext' calls are non-blocking. */
  int async;

  /* If set to 1, 'dlnext' uses readline instead of getline. */
  int interactive;

  int line_number;

  /* Set to 1 by readline callback to indicate end of file. */
  int eof;
};

struct sink_state
{
  FILE *file;
};

static int sink_curidx = 0;
static int source_curidx = 0;

enum {
  SOURCE_STACK_CAP = 16,
  SINK_STACK_CAP = 16
};

/* Stack of sources, where 'dlnext' gets lines.  'dlf_pushsource' can add
   additional source, which is processed instead of original.  When pushed
   source reaches EOF, stack is poped, activating previous source with
   its state preserved. */
static struct source_state source[SOURCE_STACK_CAP];

/* Where to print lines of fields made by 'dline' and 'dlputs'. */
static struct sink_state sink[SINK_STACK_CAP];

/* Amount of fields written.  Resets to 0 when fields are flushed by 'dline' */
static int fc = 0;

/* Line, used to get fields by 'dlgets'. */
static char *line = NULL;

/* Used by 'getline'. */
static size_t n = 0;

/* Queue, used to store lines read by asynchronous readline callback.
   Currently can only store one line. */
static char *line_queue = NULL;

/* Set to 1 by readline callback to indicate end of file. */
static int line_eof = 0;

static int line_number = 0;

/* Amount of fields read */
static int ifc = 0;

/* Used by 'mbstok_r'. */
static char *saveptr = NULL;

#if TMLIB_USE_READLINE
/* Used to detect if readline callback hander was installed. */
static int handler_installed = 0;
#endif /* TMLIB_USE_READLINE */

void
dlf_async (void)
{
  source[source_curidx].async = 1;
}

void
dlf_sync (void)
{
  source[source_curidx].async = 0;
}

void
dlf_interactive (void)
{
  source[source_curidx].interactive = 1;
}

void
dlf_noninteractive (void)
{
  source[source_curidx].interactive = 0;
}

#if TMLIB_USE_READLINE
static void
callback_handler (char *_line)
{
  if (!_line)
    {
      line_queue = NULL;
      line_eof = 1;
      rl_callback_handler_remove ();
      return;
    }

  /* No more space left in queue */
  assert (("Not enough space in queue.", !line_queue));

  line_queue = _line;

  if (handler_installed >= 1)
    --handler_installed;

  rl_callback_handler_remove ();
}
#endif /* TMLIB_USE_READLINE */

void
dlf_init (void)
{
  sink_curidx = 0;
  sink[sink_curidx].file = stdout;
  source_curidx = 0;
  source[source_curidx].file = stdin;
  source[source_curidx].name = strdup ("<stdin>");
  source[source_curidx].async = 0;
  source[source_curidx].interactive = 0;
  source[source_curidx].line_number = 0;
  source[source_curidx].eof = 0;

  fc = 0;
  ifc = 0;

  line = NULL;
  n = 0;
  line_queue = NULL;

#if TMLIB_USE_READLINE
  handler_installed = 0;
  using_history ();
#endif /* TMLIB_USE_READLINE */
}

void
autodep_dlf_init (void)
{
  static int imported = 0;

  if (imported)
    return;

  dlf_init ();
  imported = 1;
}

void
fdlputs (FILE *f, const char *s)
{
  if (fc == 0)
    {
      fputs (s, f);
    }
  else
    {
      fputc (' ', f);
      fputs (s, f);
    }
  ++fc;
}

void
fdlputi (FILE *f, int n)
{
  if (fc == 0)
    {
      fprintf (f, "%d", n);
    }
  else
    {
      fprintf (f, " %d", n);
    }
  ++fc;
}

void
fdline (FILE *f)
{
  fc = 0;
  fputc ('\n', f);
}

void
dlf_setsink (FILE *f)
{
  sink[sink_curidx].file = f;
  fc = 0;
}

void
dlputs (const char *s)
{
  fdlputs (sink[sink_curidx].file, s);
}

void
dlputi (int n)
{
  fdlputi (sink[sink_curidx].file, n);
}

void
dline (void)
{
  fdline (sink[sink_curidx].file);
}

void
dlf_setsource (FILE *f)
{
  source[source_curidx].file = f;

  /* Killing all state */
  source[source_curidx].line_number = 0;
  source[source_curidx].interactive = 0;
  source[source_curidx].async = 0;
  source[source_curidx].line_number = 0;
  source[source_curidx].eof = 0;

  ifc = 0;
  saveptr = NULL;

  if (line_queue)
    {
      free (line_queue);
      line_queue = NULL;
    }

  if (line)
    {
      free (line);
      line = NULL;
    }

#if TMLIB_USE_READLINE
  if (handler_installed)
    {
      rl_callback_handler_remove ();
      handler_installed = 0;
    }
#endif /* TMLIB_USE_READLINE */
}

void
dlf_pushsource (FILE *f)
{
  ++source_curidx;
  assert (("Stack out of memory", source_curidx < SOURCE_STACK_CAP));

  dlf_setsource (f);
}

void
dlf_setsourcename (const char *name)
{
  free (source[source_curidx].name);
  source[source_curidx].name = strdup (name);
}

static int
dlnext_sync ()
{
  ifc = 0;
  int result = getline (&line, &n, source[source_curidx].file);
  if (result != -1)
    {
      ++source[source_curidx].line_number;
      return DLNEXT_OK;
    }
  else
    {
      return DLNEXT_EOF;
    }
}


#if TMLIB_USE_READLINE
static int
dlnext_sync_readline (void)
{
  ifc = 0;
  line = readline (PACKAGE_NAME "-" PACKAGE_VERSION "$ ");

  if (line)
    {
      ++line_number;

      add_history (line);

      return DLNEXT_OK;
    }
  else
    {
      return DLNEXT_EOF;
    }
}
#endif /* TMLIB_USE_READLINE */

#if TMLIB_USE_READLINE
static int
dlnext_async_readline (void)
{
  if (!handler_installed)
    {
      rl_callback_handler_install (PACKAGE_NAME "-" PACKAGE_VERSION "$ ",
                                   callback_handler);
      handler_installed = 1;
    }

  struct timeval time;
  time.tv_sec = 0;
  time.tv_usec = 0;

  fd_set fds;
  FD_ZERO (&fds);
  FD_SET (fileno (source[source_curidx].file), &fds);
  int r = select (FD_SETSIZE, &fds, NULL, NULL, &time);

  if (r < 0 && errno != EINTR)
    {
      perror ("rltest: select");

      if (handler_installed)
        {
          rl_callback_handler_remove ();
          handler_installed = 0;
        }

      return DLNEXT_ERROR;
    }

  if (r < 0)
    return DLNEXT_NOTAVAIL;

  if (FD_ISSET (fileno (source[source_curidx].file), &fds))
    {
      rl_callback_read_char ();
    }

  ifc = 0;

  if (line_eof)
    {
      return DLNEXT_EOF;
    }

  if (line)
    {
      free (line);
      line = NULL;
    }

  if (line_queue)
    {
      line = line_queue;
      line_queue = NULL;

      ifc = 0;

      if (line)
        ++line_number;
      else
        return DLNEXT_EOF;

      add_history (line);
      return DLNEXT_OK;
    }
  else
    {
      return DLNEXT_NOTAVAIL;
    }
}
#endif /* TMLIB_USE_READLINE */

int
dlnext (void)
{
  int result;

#if TMLIB_USE_READLINE
  if (source[source_curidx].interactive)
    {
      if (!source[source_curidx].async)
        {
          result = dlnext_sync_readline ();
        }
      else
        {
          result = dlnext_async_readline ();
        }
    }
  else
    {
      result = dlnext_sync ();
    }
#else
  result = dlnext_sync ();
#endif /* TMLIB_USE_READLINE */

  if (result == DLNEXT_EOF && source_curidx > 0)
    {
      --source_curidx;
      ifc = 0;
      saveptr = NULL;

      if (line_queue)
        {
          free (line_queue);
          line_queue = NULL;
        }

      if (line)
        {
          free (line);
          line = NULL;
        }

#if TMLIB_USE_READLINE
      if (handler_installed)
        {
          rl_callback_handler_remove ();
          handler_installed = 0;
        }
#endif /* TMLIB_USE_READLINE */

      return dlnext ();
    }

  return result;
}

const char *
dlgets (void)
{
  if (ifc++ == 0)
    return mbstok_r (line, " \t\r\n", &saveptr);
  else
    return mbstok_r (NULL, " \t\r\n", &saveptr);
}

const char *
dlrest (void)
{
  static struct string_buffer sb;
  static char *buffer = NULL;

  const char *field = NULL;
  int count = 0;

  sb_init (&sb);

  while (field = dlgets ())
    {
      if (count != 0)
        sb_append1 (&sb, ' ');

      sb_append_c (&sb, field);
      ++count;
    }

  if (field)
    free (buffer);

  buffer = sb_dupfree_c (&sb);
}

int
dlf_ln (void)
{
  return line_number;
}

int
dlf_fn (void)
{
  return ifc;
}

void
dlf_errorf (const char *fmt, ...)
{
  va_list args;
  va_start (args, fmt);

  fprintf (stderr,
          "%s:%d:F%d: ",
          source[source_curidx].name, dlf_ln (), dlf_fn ());

  vfprintf (stderr, fmt, args);

  va_end (args);
}
