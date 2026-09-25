#include <stddef.h>
#include <raylib.h>

static Texture2D black48_texture;
static Texture2D white48_texture;
static Texture2D dark_green48_texture;
static Texture2D light_green48_texture;
static Texture2D black16_texture;
static Texture2D white16_texture;

static int pattern[5 * 5];

void
DrawField_clear ()
{
  for (size_t i = 0; i < 5 * 5; ++i)
    pattern[i] = 0;
}

void
DrawField_init ()
{
  black48_texture = LoadTexture (PKGDATADIR "/black48.png");
  white48_texture = LoadTexture (PKGDATADIR "/white48.png");
  dark_green48_texture = LoadTexture (PKGDATADIR "/dark_green48.png");
  light_green48_texture = LoadTexture (PKGDATADIR "/light_green48.png");
  black16_texture = LoadTexture (PKGDATADIR "/black16.png");
  white16_texture = LoadTexture (PKGDATADIR "/white16.png");

  DrawField_clear ();
}

void
DrawField_flipat (int x, int y)
{
  if (x >= 5)
    return;

  if (y >= 5)
    return;

  if (x < 0)
    return;

  if (y < 0)
    return;

  pattern[x + y * 5] = !pattern[x + y * 5];
}

void
DrawField_interact (int x, int y)
{
  DrawField_flipat (x, y);
  DrawField_flipat (x + 1, y);
  DrawField_flipat (x - 1, y);
  DrawField_flipat (x, y + 1);
  DrawField_flipat (x, y - 1);
}

void
DrawField_flipall ()
{
  for (size_t i = 0; i < 5; ++i)
    for (size_t j = 0; j < 5; ++j)
      DrawField_flipat (j, i);
}

void
DrawField80 (int x, int y)
{
  for (size_t i = 0; i < 5; ++i)
    for (size_t j = 0; j < 5; ++j)
      if (pattern[j + i * 5] == 1)
        DrawTexture (black16_texture, x + j * 16, y + i * 16, WHITE);
      else
        DrawTexture (white16_texture, x + j * 16, y + i * 16, WHITE);

  DrawField_clear ();
}

void
DrawField240 (int x, int y)
{
  for (size_t i = 0; i < 5; ++i)
    for (size_t j = 0; j < 5; ++j)
      if (pattern[j + i * 5] == 1)
        DrawTexture (black48_texture, x + j * 48, y + i * 48, WHITE);
      else
        DrawTexture (white48_texture, x + j * 48, y + i * 48, WHITE);

  DrawField_clear ();
}

void
DrawField240_green (int x, int y)
{
  for (size_t i = 0; i < 5; ++i)
    for (size_t j = 0; j < 5; ++j)
      if (pattern[j + i * 5] == 1)
        DrawTexture (dark_green48_texture, x + j * 48, y + i * 48, WHITE);
      else
        DrawTexture (light_green48_texture, x + j * 48, y + i * 48, WHITE);

  DrawField_clear ();
}
