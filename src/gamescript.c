#include <config.h>

#include <stdio.h>
#include <dlf.h>
#include <string.h>
#include <completed.h>

int
eval ()
{
  if (-1 == dlnext ())
    return -1;

  int value;
  const char *field = NULL;

  field = dlgets ();

  if (0 == strcmp (field, "print"))
    {
      field = dlgets ();
      dlf_errorf ("%s\n", field);
    }
  else if (0 == strcmp (field, "completed_setid"))
    {
      field = dlgets ();

      if (sscanf (field, "%d", &value) != 1)
        {
          dlf_errorf ("expected number after 'completed_setid'\n");
          return 0;
        }

      completed_setid (value);
    }
  else if (0 == strcmp (field, "complete"))
    {
      mem_complete ();
    }
  else
    {
      dlf_errorf ("unrecognized '%s'\n", field);
    }

  return 1;
}
