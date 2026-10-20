#include <config.h>

#include <dlf.h>
#include <dlf_getline.h>

int
main (int argc, char **argv)
{
  dlf_init ();

  dlf_pushsource_manual ();

  for (;;)
    {
      const char *field;

      dlf_getline_feed (stdin);

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

  dlf_popsource ();
}
