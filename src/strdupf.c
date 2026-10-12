#include <config.h>

#include <lib/string-buffer.h>
#include <stdarg.h>

static struct string_buffer buffer;

char *
strdupf (const char *fmt, ...)
{
  va_list args;
  va_start (args, fmt);

  sb_init (&buffer);
  sb_appendvf (&buffer, fmt, args);

  va_end (args);

  return sb_dupfree_c (&buffer);
}
