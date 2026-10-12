#include <config.h>

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <dlf.h>
#include <config.h>
#include <lib/string-buffer.h>

static int db[128];
static int id;

static void eval (FILE *);

static char *savepath = NULL;
static char *ttt5x5path = NULL;

static char *command = NULL;
size_t command_size = 0;

struct string_buffer buffer;

static char *
strdupf (const char *fmt, ...)
{
  va_list args;
  va_start (args, fmt);

  sb_init (&buffer);
  sb_appendvf (&buffer, fmt, args);

  va_end (args);

  return sb_dupfree_c (&buffer);
}

static void
db_reset ()
{
  for (size_t i = 0; i < 128; ++i)
    db[i] = 0;
}

static void
init_dirpaths ()
{
  const char *xdg = getenv ("XDG_DATA_HOME");
  const char *home = getenv ("HOME");

  if (xdg)
    ttt5x5path = strdupf ("%s/" PACKAGE_NAME "/", xdg);
  else if (home)
    ttt5x5path = strdupf ("%s/.local/share/" PACKAGE_NAME "/", home);
  else
    ttt5x5path = strdup ("./");

  savepath = strdupf ("%s%s", ttt5x5path, "save.dlf");
}

void
completed_init (void)
{
  sb_init (&buffer);
  db_reset ();
  init_dirpaths ();

  FILE *file = fopen (savepath, "r");

  if (!file)
    {
      perror ("Unable to open save file for reading");
      return;
    }

  eval (file);
}

void
completed_setid (int x)
{
  id = x;
}

int
completed (void)
{
  return db[id];
}

void
complete (void)
{
  FILE *file;

  if (db[id])
    return;

  db[id] = 1;

  command = strdupf ("/usr/bin/ls %s 2>/dev/null >/dev/null", ttt5x5path);

  if (0 != system (command));
    {
      free (command);
      command = strdupf ("/usr/bin/mkdir -p %s 2>/dev/null >/dev/null", ttt5x5path);
      system (command);
    }
  free (command);

  file = fopen (savepath, "a");

  if (!file)
    {
      perror ("Unable to open save file for writing");
      return;
    }

  fdlputs (file, "completed_setid");
  fdlputi (file, id);
  fdline  (file);
  fdlputs (file, "complete");
  fdline  (file);

  fclose (file);
}

static void
eval (FILE *f)
{
  int value;
  const char *field = NULL;
  dlf_setsource (f);

  while (-1 != dlnext ())
  {
    field = dlgets ();

    if (0 == strcmp (field, "completed_setid"))
      {
        field = dlgets ();

        if (sscanf (field, "%d", &value) != 1)
          {
            fprintf (stderr,
                    "%s:%d:F%d: expected number after 'completed_setid'\n",
                    savepath, dlf_ln (), dlf_fn ());
            return;
          }

        completed_setid (value);
      }
    else if (0 == strcmp (field, "complete"))
      {
        complete ();
      }
    else
      {
        fprintf (stderr,
                "%s:%d:F%d: unrecognized '%s'\n",
                savepath, dlf_ln (), dlf_fn (), field);
        return;
      }
  }
}

