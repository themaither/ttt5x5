#include <config.h>

#include <stddef.h>
#include <5x5.h>
#include <raylib.h>
#include <assets.h>

static Texture2D black48_texture;
static Texture2D white48_texture;
static Texture2D dark_green48_texture;
static Texture2D light_green48_texture;
static Texture2D black16_texture;
static Texture2D white16_texture;

static int pattern_i;

void
DrawField_clear (void)
{
  int old = _5x5_selection ();
  _5x5_select (pattern_i);
  _5x5_clear ();
  _5x5_select (old);
}

static Texture2D
LoadTextureFromMemory (unsigned char *data, int length)
{
  Image image = LoadImageFromMemory(".png", data, length);
  Texture2D texture = LoadTextureFromImage (image);
  UnloadImage (image);
  return texture;
}

void
DrawField_init (void)
{
  black48_texture = LoadTextureFromMemory (assets_black48, assets_black48_len);
  white48_texture = LoadTextureFromMemory (assets_white48, assets_white48_len);
  black16_texture = LoadTextureFromMemory (assets_black16, assets_black16_len);
  white16_texture = LoadTextureFromMemory (assets_white16, assets_white16_len);
  dark_green48_texture = LoadTextureFromMemory (assets_dark_green48, assets_dark_green48_len);
  light_green48_texture = LoadTextureFromMemory (assets_light_green48, assets_light_green48_len);

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
DrawField_flipall (void)
{
  int old = _5x5_selection ();
  _5x5_select (pattern_i);
  for (size_t i = 0; i < 5; ++i)
    for (size_t j = 0; j < 5; ++j)
      DrawField_flipat (j, i);
  _5x5_select (old);
}

void
DrawField80_selected (int x, int y)
{
  for (size_t i = 0; i < 5; ++i)
    for (size_t j = 0; j < 5; ++j)
      if (_5x5_colorat(j, i) == 1)
        DrawTexture (black16_texture, x + j * 16, y + i * 16, WHITE);
      else
        DrawTexture (white16_texture, x + j * 16, y + i * 16, WHITE);
}

void
DrawField80 (int x, int y)
{
  int old = _5x5_intsel (pattern_i);

  DrawField80_selected (x, y);
  DrawField_clear ();

  _5x5_retsel (old);
}

void
DrawField240_selected (int x, int y)
{
  for (size_t i = 0; i < 5; ++i)
    for (size_t j = 0; j < 5; ++j)
      if (_5x5_colorat(j, i) == 1)
        DrawTexture (black48_texture, x + j * 48, y + i * 48, WHITE);
      else
        DrawTexture (white48_texture, x + j * 48, y + i * 48, WHITE);
}

void
DrawField240 (int x, int y)
{
  int old = _5x5_intsel (pattern_i);

  DrawField240_selected (x, y);
  DrawField_clear ();

  _5x5_retsel (old);
}

void
DrawField240_green_selected (int x, int y)
{
  for (size_t i = 0; i < 5; ++i)
    for (size_t j = 0; j < 5; ++j)
      if (_5x5_colorat(j, i) == 1)
        DrawTexture (dark_green48_texture, x + j * 48, y + i * 48, WHITE);
      else
        DrawTexture (light_green48_texture, x + j * 48, y + i * 48, WHITE);
}

void
DrawField240_green (int x, int y)
{
  int old = _5x5_intsel (pattern_i);

  DrawField240_green_selected (x, y);
  DrawField_clear ();

  _5x5_retsel (old);
}
