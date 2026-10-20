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
  int manual;

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

  /* When EOF is reached, pops source stack and proceeds instead of failing. */
  int autowrap;
};

struct sink_state
{
  int manual;

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

/* Queue to be read from by using 'dlf_eat'. */
static char *sink_line_queue = NULL;

/* Used by manual 'dlputs' and 'dline' to store fields before they're
   flushed. */
static struct string_buffer manual_sink_sb;

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
  source[source_curidx].manual = 0;
  source[source_curidx].name = strdup ("<stdin>");
  source[source_curidx].async = 0;
  source[source_curidx].interactive = 0;
  source[source_curidx].line_number = 0;
  source[source_curidx].eof = 0;

  sb_init (&manual_sink_sb);

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

static void
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

static void
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

static void
fdline (FILE *f)
{
  fc = 0;
  fputc ('\n', f);
}

void
dlf_setsink (FILE *f)
{
  sink[sink_curidx].file = f;
  sink[sink_curidx].manual = 0;
  fc = 0;
}

void
dlf_setsink_manual (void)
{
  sink[sink_curidx].manual = 1;
  fc = 0;
}

void
dlf_pushsink (FILE *f)
{
  ++sink_curidx;
  assert (("Stack out of memory", sink_curidx < SOURCE_STACK_CAP));

  dlf_setsink (f);
}

void
dlf_pushsink_manual (void)
{
  ++sink_curidx;
  assert (("Stack out of memory", sink_curidx < SOURCE_STACK_CAP));

  dlf_setsink_manual ();
}

void
dlf_popsink (void)
{
  assert (("Cannot pop last sink", sink_curidx > 0));
  --sink_curidx;
  fc = 0;
}

void
dlputs (const char *s)
{
  if (sink[sink_curidx].manual == 0)
    return fdlputs (sink[sink_curidx].file, s);

  if (fc == 0)
    {
      sb_append_c (&manual_sink_sb, s);
    }
  else
    {
      sb_append1 (&manual_sink_sb, ' ');
      sb_append_c (&manual_sink_sb, s);
    }
  ++fc;
}

void
dlputi (int n)
{
  if (sink[sink_curidx].manual == 0)
    return fdlputi (sink[sink_curidx].file, n);

  if (fc == 0)
    {
      sb_appendf (&manual_sink_sb, "%d", n);
    }
  else
    {
      sb_appendf (&manual_sink_sb, " %d", n);
    }
  ++fc;
}

void
dline (void)
{
  if (sink[sink_curidx].manual == 0)
    return fdline (sink[sink_curidx].file);

  fc = 0;
  assert (("Not enough space in queue", sink_line_queue == NULL));

  sink_line_queue = sb_dupfree_c (&manual_sink_sb);
  sb_init (&manual_sink_sb);
}

char *
dlf_eat (void)
{
  if (sink_line_queue == NULL)
    return NULL;

  char *result = sink_line_queue;
  sink_line_queue = NULL;
  return result;
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
  source[source_curidx].autowrap = 0;
  source[source_curidx].manual = 0;

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
dlf_popsource (void)
{
  assert (("Cannot pop last source", source_curidx > 0));

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
}

void
dlf_setsourcename (const char *name)
{
  free (source[source_curidx].name);
  source[source_curidx].name = strdup (name);
}

void
dlf_source_autowrap (void)
{
  source[source_curidx].autowrap = 1;
}

static int
dlnext_sync (void)
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

static int
dlnext_feed (void)
{
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

      return DLNEXT_OK;
    }
  else
    {
      return DLNEXT_NOTAVAIL;
    }
}

int
dlnext (void)
{
  int result;

  if (source[source_curidx].manual)
    {
      result = dlnext_feed ();
    }
  else
    {
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
    }

  if (result == DLNEXT_EOF
        && source[source_curidx].autowrap
        && source_curidx > 0)
    {
      dlf_popsource ();

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

void
dlf_setsource_manual (void)
{
  source[source_curidx].manual = 1;

  /* Killing all state */
  source[source_curidx].line_number = 0;
  source[source_curidx].interactive = 0;
  source[source_curidx].async = 0;
  source[source_curidx].line_number = 0;
  source[source_curidx].eof = 0;
  source[source_curidx].autowrap = 0;

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
dlf_pushsource_manual (void)
{
  ++source_curidx;
  assert (("Stack out of memory", source_curidx < SOURCE_STACK_CAP));

  dlf_setsource_manual ();
}

void
dlf_feed (const char *_line)
{
  if (!_line)
    {
      line_queue = NULL;
      line_eof = 1;
      return;
    }

  /* No more space left in queue */
  assert (("Not enough space in queue.", !line_queue));

  line_queue = strdup (_line);
}
