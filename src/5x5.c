#include <stddef.h>
#include <stdio.h>
#include <assert.h>

enum
{
  MAX_PATTERNS = 32
};

static int patterns[MAX_PATTERNS][5 * 5];
static size_t selection = 0;
static size_t last_selection = 1;
static int *desired_pattern = patterns[1];

static int won = 0;
static int matches = 0;

void
_5x5_select (int newsel)
{
  assert (newsel <= last_selection);
  assert (newsel < MAX_PATTERNS);
  selection = newsel;
}

int
_5x5_open ()
{
  ++last_selection;
  assert (last_selection < MAX_PATTERNS);
  return last_selection;
}

int
_5x5_colorat (int x, int y)
{
  return patterns[selection][x + y * 5];
}

void
_5x5_clear ()
{
  for (size_t i = 0; i < 5 * 5; ++i)
    patterns[selection][i] = 0;
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

  patterns[selection][x + y * 5] = !patterns[selection][x + y * 5];
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
_5x5_interact (int x, int y)
{
  _5x5_flipat (x, y);
  _5x5_flipat (x + 1, y);
  _5x5_flipat (x - 1, y);
  _5x5_flipat (x, y + 1);
  _5x5_flipat (x, y - 1);

  if (selection == 0)
  {
    int good = 1;

    for (size_t i = 0; i < 5; ++i)
      for (size_t j = 0; j < 5; ++j)
        if (patterns[selection][j + i * 5] != desired_pattern[j + i * 5])
          good = 0;

    matches = good;

    if (good)
      won = 1;
  }
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
_5x5_filldesired ()
{
  int back = selection;
  selection = 1;
  _5x5_clear ();
  selection = back;
}

int
_5x5_colorat_desired (int x, int y)
{
  int back = selection;
  selection = 1;
  int result =  _5x5_colorat (x, y);
  selection = back;
  return result;
}

void
_5x5_flipat_desired (int x, int y)
{
  int back = selection;
  selection = 1;
  _5x5_flipat (x, y);
  selection = back;
}

void
_5x5_interact_desired (int x, int y)
{
  int back = selection;
  selection = 1;
  _5x5_interact (x, y);
  selection = back;
}
