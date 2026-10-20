#include <config.h>

#ifndef TMLIB_USE_READLINE
#define TMLIB_USE_READLINE 1
#endif /* TMLIB_USE_READLINE */

#if TMLIB_USE_READLINE

#include <dlf.h>

#include <readline/readline.h>
#include <readline/history.h>

static char *line = NULL;

void
dlf_readline_feed (void)
{
  line = readline (PACKAGE_NAME "-" PACKAGE_VERSION "$ ");

  if (line)
    add_history (line);

  dlf_feed (line);

  free (line);
}

#endif /* TMLIB_USE_READLINE */
