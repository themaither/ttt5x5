#include <stddef.h>

static int db[128];
static int id;

void
completed_init (void)
{
  for (size_t i = 0; i < 128; ++i)
    db[i] = 0;
}

void
completed_setid (int x)
{
  id = x;
}

int
completed (void)
{
  return db[id];
}

void
complete (void)
{
  db[id] = 1;
}
