#include <config.h>

#include <stdio.h>
#include <stdarg.h>

static const char *progname = "";

void
progmsg_setname (const char *name)
{
  progname = name;
}

void
progmsg (const char *fmt, ...)
{
  va_list args;
  va_start (args, fmt);

  fprintf (stderr, "%s: ", progname);
  vfprintf (stderr, fmt, args);
  fprintf (stderr, "\n");

  va_end (args);
}

void
vprogmsg (const char *fmt, va_list ap)
{
  fprintf (stderr, "%s: ", progname);
  vfprintf (stderr, fmt, ap);
  fprintf (stderr, "\n");

  va_end (ap);
}
