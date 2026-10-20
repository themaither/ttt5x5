#include <config.h>

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlf.h>
#include <dlf_getline.h>
#include <strdupf.h>
#include <gamescript.h>
#include <raylib.h>

static int db[128];
static int id;

static void evalf (FILE *);

static char *savepath = NULL;
static char *ttt5x5path = NULL;

static char *command = NULL;
size_t command_size = 0;

static char *saveptr = NULL;

static void
mem_init (void)
{
  for (size_t i = 0; i < 128; ++i)
    db[i] = 0;
}

void
mem_complete (void)
{
  db[id] = 1;
}

static void
io_init (void)
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

  char *text = LoadFileText (savepath);
  const char *line;

  if (!text)
    {
      perror ("Unable to open save file for reading");
      UnloadFileText (text);
      return;
    }

  dlf_pushsource_manual ();

  if (line = mbstok_r (text, "\n", &saveptr))
    do
      {
        dlf_feed (line);
        if (eval () == -1)
          break;
      }
    while (line = mbstok_r (NULL, "\n", &saveptr));

  UnloadFileText (text);

  dlf_popsource ();
}

static void
io_complete (void)
{
  FILE *file;

  command = strdupf ("/usr/bin/ls %s 2>/dev/null >/dev/null", ttt5x5path);

  if (0 != system (command))
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

  dlf_pushsink (file);
  dlputs ("completed_setid");
  dlputi (id);
  dline  ();
  dlputs ("complete");
  dline  ();
  dlf_popsink ();

  fclose (file);
}

void
completed_init (void)
{
  mem_init ();
  io_init ();
}

void
autodep_completed_init (void)
{
  static int imported = 0;

  if (imported)
    return;

  autodep_dlf_init ();

  completed_init ();
  imported = 1;
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
