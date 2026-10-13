#include <config.h>

#include <stdio.h>
#include <string.h>

static FILE *source;
static FILE *sink;

static int fc = 0;
static char *line = NULL;
static size_t n = 0;
static int line_number = 0;
static int ifc = 0;

static char *saveptr = NULL;
static char *source_name = NULL;

void
dlf_init ()
{
  sink = stdout;
  source = stdin;
  source_name = strdup ("<stdin>");
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
dlf_setsink (FILE *f)
{
  sink = f;
  fc = 0;
}

void
dfl_setsourcename (const char *name)
{
  free (source_name);
  source_name = strdup (name);
}

FILE *
dlf_sink ()
{
  return sink;
}

void
dlputs (const char *s)
{
  fdlputs (sink, s);
}

void
dlputi (int n)
{
  fdlputi (sink, n);
}

void
dline ()
{
  fdline (sink);
}

void
dlf_setsource (FILE *f)
{
  source = f;
  int line_number = 0;
}

FILE *
dlf_source ()
{
  return source;
}

int
dlnext ()
{
  ifc = 0;
  int result = getline (&line, &n, source);
  if (result != -1)
    ++line_number;
  return result;
}

const char *
dlgets ()
{
  if (ifc++ == 0)
    return strtok_r (line, " \t\r\n", &saveptr);
  else
    return strtok_r (NULL, " \t\r\n", &saveptr);
}

int
dlf_ln ()
{
  return line_number;
}

int
dlf_fn ()
{
  return ifc;
}

void
dlf_errorf (const char *fmt, ...)
{
  va_list args;
  va_start (args, fmt);

  fprintf (stderr,
          "%s:%d:F%d: ",
          source_name, dlf_ln (), dlf_fn ());

  vfprintf (stderr, fmt, args);

  va_end (args);
}
