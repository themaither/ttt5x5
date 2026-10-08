#include <raylib.h>
#include <assert.h>

static Texture2D digit_textures[10];

void
DrawDigit_init ()
{
  digit_textures[0] = LoadTexture (PKGDATADIR "/digit_0.png");
  digit_textures[1] = LoadTexture (PKGDATADIR "/digit_1.png");
  digit_textures[2] = LoadTexture (PKGDATADIR "/digit_2.png");
  digit_textures[3] = LoadTexture (PKGDATADIR "/digit_3.png");
  digit_textures[4] = LoadTexture (PKGDATADIR "/digit_4.png");
  digit_textures[5] = LoadTexture (PKGDATADIR "/digit_5.png");
  digit_textures[6] = LoadTexture (PKGDATADIR "/digit_6.png");
  digit_textures[7] = LoadTexture (PKGDATADIR "/digit_7.png");
  digit_textures[8] = LoadTexture (PKGDATADIR "/digit_8.png");
  digit_textures[9] = LoadTexture (PKGDATADIR "/digit_9.png");
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
