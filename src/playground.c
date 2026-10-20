#include <config.h>

#include <dlf.h>

int
main (int argc, char **argv)
{
  dlf_init ();

  dlf_pushsource_manual ();

  dlf_feed ("first field");

  for (;;)
    {
      const char *field;

      if (dlnext () != DLNEXT_OK)
        {
          if (dlnext () == DLNEXT_NOTAVAIL)
            puts ("Not avail");

          if (dlnext () == DLNEXT_EOF)
            puts ("EOF");

          break;
        }

      if (!(field = dlgets ()))
        continue;

      printf ("%s\n", field);
    }
}
