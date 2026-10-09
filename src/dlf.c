#include <stdio.h>

static int fc = 0;

FILE *dlf_sink;

void
dlf_init ()
{
  dlf_sink = stdout;
}

void
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

void
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

void
fdline (FILE *f)
{
  fc = 0;
  fputc ('\n', f);
}

void
dlputs (const char *s)
{
  fdlputs (dlf_sink, s);
}

void
dlputi (int n)
{
  fdlputi (dlf_sink, n);
}

void
dline ()
{
  fdline (dlf_sink);
}
