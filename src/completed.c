#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

int save = 0;

struct string_buffer buffer;

void
completed_init (void)
{
  const char *xdg = getenv ("XDG_DATA_HOME");
  const char *home = getenv ("HOME");

  sb_init (&buffer);
  if (xdg)
    {
      sb_appendf (&buffer, "%s/" PACKAGE_NAME "/", xdg);
    }
  else if (home)
    {
      sb_appendf (&buffer, "%s/.local/share/" PACKAGE_NAME "/", home);
    }
  else
    {
      sb_appendf (&buffer, "./");
    }

  ttt5x5path = sb_dupfree_c (&buffer);
  sb_init (&buffer);
  sb_appendf (&buffer, "%s%s", ttt5x5path, "save.dlf");
  savepath = sb_dupfree_c (&buffer);
  printf ("%s\n", savepath);

  for (size_t i = 0; i < 128; ++i)
    db[i] = 0;

  FILE *f = fopen (savepath, "r");

  if (!f)
    {
      perror ("Unable to open save file for reading");

      save = 1;

      return;
    }

  eval (f);

  save = 1;
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
  if (db[id] == 1)
    return;

  db[id] = 1;

  if (!save)
    return;

  FILE *cs;

  sb_init (&buffer);
  sb_appendf (&buffer, "/usr/bin/ls %s 2>/dev/null >/dev/null", ttt5x5path);
  command = sb_dupfree_c (&buffer);
  if (0 != system (command));
    {
      free (command);

      sb_init (&buffer);
      sb_appendf (&buffer, "/usr/bin/mkdir -p %s 2>/dev/null >/dev/null", ttt5x5path);
      command = sb_dupfree_c (&buffer);

      system (command);
    }

  free (command);

  FILE *f = fopen (savepath, "a");

  if (!f)
    {
      perror ("Unable to open save file for writing");
      return;
    }

  fdlputs (f, "completed_setid");
  fdlputi (f, id);
  fdline  (f);
  fdlputs (f, "complete");
  fdline  (f);

  fclose (f);
}

static void
eval (FILE *f)
{
  const char *field = NULL;
  dlf_setsource (f);

  for (;;)
  {
    if (-1 == dlnext ())
      return;

    field = dlgets ();

    if (0 == strcmp (field, "completed_setid"))
      {
        int value;
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

