#include <config.h>

#include <dlf.h>
#include <stdio.h>

/* Line, used to get fields by 'dlgets'. */
static char *line = NULL;

static size_t n = 0;

void
dlf_getline_feed (FILE *file)
{
  int result = getline (&line, &n, file);

  if (result != -1)
    dlf_feed (line);
  else
    dlf_feed (NULL);
}
