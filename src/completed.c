#include <stddef.h>
#include <stdio.h>
#include <string.h>

static int db[128];
static int id;

static void eval (FILE *);

void
completed_init (void)
{
  for (size_t i = 0; i < 128; ++i)
    db[i] = 0;

  FILE *f = fopen ("./save.dlf", "r");

  if (!f)
    {
      perror ("Unable to open save file './save.dlf' for reading");
      return;
    }

  eval (f);
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
  FILE *f = fopen ("./save.dlf", "a");

  if (!f)
    {
      perror ("Unable to open save file './save.dlf' for writing");
      return;
    }

  fprintf (f, "completed_setid %d\n", id);
  fprintf (f, "complete\n");
  fclose (f);
}

static void
eval (FILE *f)
{
  char *line = NULL;
  const char *field = NULL;
  size_t n = 0;
  int line_number = 0;

  for (;;)
  {
    if (-1 == getline (&line, &n, f))
      return;
    ++line_number;

    field = strtok (line, " \t\r\n");

    if (0 == strcmp (field, "completed_setid"))
      {
        int value;
        field = strtok (NULL, " \t\r\n");

        if (sscanf (field, "%d", &value) != 1)
          {
            fprintf (stderr,
                    "./save.dlf:%d: expected number after 'completed_setid'\n",
                    line_number);
            return;
          }

        completed_setid (value);
      }
    else if (0 == strcmp (field, "complete"))
      {
        puts ("COMPLETE");
        complete ();
      }
    else
      {
        fprintf (stderr,
                "./save.dlf:%d: unrecognized '%s'\n",
                line_number, field);
        return;
      }
  }
}

