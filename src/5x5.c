#include <stddef.h>
#include <stdio.h>

static int current_pattern[5 * 5];
static int desired_pattern[5 * 5];

static int won = 0;
static int matches = 0;

int
_5x5_colorat (int x, int y)
{
  return current_pattern[x + y * 5];
}

static void
_5x5_flipat (int x, int y)
{
  if (x >= 5)
    return;

  if (y >= 5)
    return;

  if (x < 0)
    return;

  if (y < 0)
    return;

  current_pattern[x + y * 5] = !current_pattern[x + y * 5];
}

int
_5x5_colorat_desired (int x, int y)
{
  return desired_pattern[x + y * 5];
}

void
_5x5_flipat_desired (int x, int y)
{
  if (x >= 5)
    return;

  if (y >= 5)
    return;

  if (x < 0)
    return;

  if (y < 0)
    return;

  desired_pattern[x + y * 5] = !desired_pattern[x + y * 5];
}

void
_5x5_interact_desired (int x, int y)
{
  _5x5_flipat_desired (x, y);
  _5x5_flipat_desired (x + 1, y);
  _5x5_flipat_desired (x - 1, y);
  _5x5_flipat_desired (x, y + 1);
  _5x5_flipat_desired (x, y - 1);
}

void
_5x5_interact (int x, int y)
{
  _5x5_flipat (x, y);
  _5x5_flipat (x + 1, y);
  _5x5_flipat (x - 1, y);
  _5x5_flipat (x, y + 1);
  _5x5_flipat (x, y - 1);

  int good = 1;

  for (size_t i = 0; i < 5; ++i)
    for (size_t j = 0; j < 5; ++j)
      if (current_pattern[j + i * 5] != desired_pattern[j + i * 5])
        good = 0;

  matches = good;

  if (good)
    won = 1;
}

int
_5x5_won ()
{
  return won == 1;
}

int
_5x5_matches ()
{
  return matches == 1;
}

void
_5x5_clear ()
{
  for (size_t i = 0; i < 5 * 5; ++i)
    current_pattern[i] = 0;
}

void
_5x5_startpattern ()
{
  _5x5_clear ();
  _5x5_flipat (2, 2);
  _5x5_flipat (1, 2);
  _5x5_flipat (3, 2);
  _5x5_flipat (2, 1);
  _5x5_flipat (2, 3);
}

void
_5x5_filldesired ()
{
  for (size_t i = 0; i < 5 * 5; ++i)
    {
      desired_pattern[i] = 0;
    }
}
