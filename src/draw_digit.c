#include <config.h>

#include <raylib.h>
#include <assert.h>
#include <assets.h>

static Texture2D digit_textures[10];

static Texture2D
LoadTextureFromMemory (unsigned char *data, int length)
{
  Image image = LoadImageFromMemory(".png", data, length);
  Texture2D texture = LoadTextureFromImage (image);
  UnloadImage (image);
  return texture;
}

void
DrawDigit_init (void)
{
  digit_textures[0] = LoadTextureFromMemory(assets_digit_0, assets_digit_0_len);
  digit_textures[1] = LoadTextureFromMemory(assets_digit_1, assets_digit_1_len);
  digit_textures[2] = LoadTextureFromMemory(assets_digit_2, assets_digit_2_len);
  digit_textures[3] = LoadTextureFromMemory(assets_digit_3, assets_digit_3_len);
  digit_textures[4] = LoadTextureFromMemory(assets_digit_4, assets_digit_4_len);
  digit_textures[5] = LoadTextureFromMemory(assets_digit_5, assets_digit_5_len);
  digit_textures[6] = LoadTextureFromMemory(assets_digit_6, assets_digit_6_len);
  digit_textures[7] = LoadTextureFromMemory(assets_digit_7, assets_digit_7_len);
  digit_textures[8] = LoadTextureFromMemory(assets_digit_8, assets_digit_8_len);
  digit_textures[9] = LoadTextureFromMemory(assets_digit_9, assets_digit_9_len);
}

void
autodep_DrawDigit_init (void)
{
  static int imported = 0;

  if (imported)
    return;

  DrawDigit_init ();
  imported = 1;
}

void
DrawDigit (int digit, int x, int y)
{
  assert (digit >= 0);
  assert (digit <= 9);
  DrawTexture(digit_textures[digit], x, y, WHITE);
}

void
DrawNumber3 (int number, int x, int y)
{
  DrawDigit (number % 10 , x + 52, y);
  DrawDigit ((number / 10) % 10 , x + 26, y);
  DrawDigit ((number / 100) % 10 , x, y);
}
