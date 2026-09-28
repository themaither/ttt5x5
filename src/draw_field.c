#include <stddef.h>
#include <5x5.h>
#include <raylib.h>

static Texture2D black48_texture;
static Texture2D white48_texture;
static Texture2D dark_green48_texture;
static Texture2D light_green48_texture;
static Texture2D black16_texture;
static Texture2D white16_texture;

static int pattern_i;

void
DrawField_clear ()
{
  int old = _5x5_selection ();
  _5x5_select (pattern_i);
  _5x5_clear ();
  _5x5_select (old);
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

  pattern_i = _5x5_open ();

  DrawField_clear ();
}

void
DrawField_flipat (int x, int y)
{
  int old = _5x5_selection ();
  _5x5_select (pattern_i);
  _5x5_flipat (x, y);
  _5x5_select (old);
}

void
DrawField_interact (int x, int y)
{
  int old = _5x5_selection ();
  _5x5_select (pattern_i);
  _5x5_interact (x, y);
  _5x5_select (old);
}

void
DrawField_flipall ()
{
  int old = _5x5_selection ();
  _5x5_select (pattern_i);
  for (size_t i = 0; i < 5; ++i)
    for (size_t j = 0; j < 5; ++j)
      DrawField_flipat (j, i);
  _5x5_select (old);
}

void
DrawField80 (int x, int y)
{
  int old = _5x5_selection ();
  _5x5_select (pattern_i);
  for (size_t i = 0; i < 5; ++i)
    for (size_t j = 0; j < 5; ++j)
      if (_5x5_colorat(j, i) == 1)
        DrawTexture (black16_texture, x + j * 16, y + i * 16, WHITE);
      else
        DrawTexture (white16_texture, x + j * 16, y + i * 16, WHITE);

  DrawField_clear ();
  _5x5_select (old);
}

void
DrawField240 (int x, int y)
{
  int old = _5x5_selection ();
  _5x5_select (pattern_i);
  for (size_t i = 0; i < 5; ++i)
    for (size_t j = 0; j < 5; ++j)
      if (_5x5_colorat(j, i) == 1)
        DrawTexture (black48_texture, x + j * 48, y + i * 48, WHITE);
      else
        DrawTexture (white48_texture, x + j * 48, y + i * 48, WHITE);

  DrawField_clear ();
  _5x5_select (old);
}

void
DrawField240_green (int x, int y)
{
  int old = _5x5_selection ();
  _5x5_select (pattern_i);
  for (size_t i = 0; i < 5; ++i)
    for (size_t j = 0; j < 5; ++j)
      if (_5x5_colorat(j, i) == 1)
        DrawTexture (dark_green48_texture, x + j * 48, y + i * 48, WHITE);
      else
        DrawTexture (light_green48_texture, x + j * 48, y + i * 48, WHITE);

  DrawField_clear ();
  _5x5_select (old);
}
