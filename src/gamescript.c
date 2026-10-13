#include <config.h>

#include <stdio.h>
#include <dlf.h>
#include <string.h>

void
eval ()
{
  dlnext ();

  const char *field = NULL;
  field = dlgets ();

  if (0 == strcmp (field, "print"))
    {
      field = dlgets ();
      fprintf (stderr,
              "%s:%d:F%d: %s\n",
              "<stdin>", dlf_ln (), dlf_fn (), field);
    }
  else
    {
      fprintf (stderr,
              "%s:%d:F%d: unrecognized '%s'\n",
              "<stdin>", dlf_ln (), dlf_fn (), field);
    }
}
