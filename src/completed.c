#include <config.h>

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlf.h>
#include <strdupf.h>
#include <gamescript.h>

static int db[128];
static int id;

static void evalf (FILE *);

static char *savepath = NULL;
static char *ttt5x5path = NULL;

static char *command = NULL;
size_t command_size = 0;

static void
mem_init ()
{
  for (size_t i = 0; i < 128; ++i)
    db[i] = 0;
}

void
mem_complete ()
{
  db[id] = 1;
}

static void
io_init ()
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

  FILE *file = fopen (savepath, "r");

  if (!file)
    {
      perror ("Unable to open save file for reading");
      return;
    }

  evalf (file);
}

static void
io_complete ()
{
  FILE *file;

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

void
completed_init (void)
{
  mem_init ();
  io_init ();
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
  if (completed ())
    return;

  mem_complete ();
  io_complete ();
}

static void
evalf (FILE *f)
{
  int value;
  const char *field = NULL;
  dlf_setsource (f);

  while (-1 != eval ())
  {
  }
}

