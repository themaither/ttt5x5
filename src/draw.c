#include <config.h>

#include <raylib.h>
#include <assert.h>
#include <assets.h>
#include <stddef.h>

static Texture2D tl_texture;
static Texture2D tr_texture;
static Texture2D bl_texture;
static Texture2D br_texture;
static Font font;
static Texture2D button_hovered_texture;

static Texture2D digit_textures[10];

static Texture2D
LoadTextureFromMemory (unsigned char *data, int length)
{
  Image image = LoadImageFromMemory(".png", data, length);
  Texture2D texture = LoadTextureFromImage (image);
  UnloadImage (image);
  return texture;
}

static void
DrawTexture3x3 (Texture2D texture, int image_x, int image_y,
                int padding, int x, int y, int width, int height)
{
  Rectangle srcrect;
  Rectangle destrect;
  Vector2 origin;

  origin.x = 0.f;
  origin.y = 0.f;

  srcrect.width = padding;
  srcrect.height = padding;
  destrect.width = padding;
  destrect.height = padding;

  srcrect.x = 0;
  srcrect.y = 0;
  destrect.x = x;
  destrect.y = y;
  DrawTexturePro (texture, srcrect, destrect, origin, 0.f, WHITE);

  srcrect.x = image_x - padding;
  srcrect.y = 0;
  destrect.x = x + width - padding;
  destrect.y = y;
  DrawTexturePro (texture, srcrect, destrect, origin, 0.f, WHITE);

  srcrect.x = image_x - padding;
  srcrect.y = image_y - padding;
  destrect.x = x + width - padding;
  destrect.y = y + height - padding;
  DrawTexturePro (texture, srcrect, destrect, origin, 0.f, WHITE);

  srcrect.x = 0;
  srcrect.y = image_y - padding;
  destrect.x = x;
  destrect.y = y + height - padding;
  DrawTexturePro (texture, srcrect, destrect, origin, 0.f, WHITE);

  srcrect.x = padding;
  srcrect.y = 0;
  srcrect.width = image_x - padding * 2;
  srcrect.height = padding;

  destrect.x = x + padding;
  destrect.y = y;
  destrect.width = width - padding * 2;
  destrect.height = padding;
  DrawTexturePro (texture, srcrect, destrect, origin, 0.f, WHITE);

  srcrect.y = image_y - padding;
  destrect.y = y + height - padding;
  DrawTexturePro (texture, srcrect, destrect, origin, 0.f, WHITE);

  srcrect.x = 0;
  srcrect.y = padding;
  srcrect.width = padding;
  srcrect.height = image_y - padding * 2;

  destrect.x = x;
  destrect.y = y + padding;
  destrect.width = padding;
  destrect.height = height - padding * 2;
  DrawTexturePro (texture, srcrect, destrect, origin, 0.f, WHITE);

  srcrect.x = image_x - padding;
  destrect.x = x + width - padding;
  DrawTexturePro (texture, srcrect, destrect, origin, 0.f, WHITE);

  srcrect.x = padding;
  srcrect.y = padding;
  srcrect.width = image_x - padding * 2;
  srcrect.height = image_y - padding * 2;

  destrect.x = x + padding;
  destrect.y = y + padding;
  destrect.width = width - padding * 2;
  destrect.height = height - padding * 2;
  DrawTexturePro (texture, srcrect, destrect, origin, 0.f, WHITE);

}

void
Draw_init (void)
{
  tl_texture = LoadTextureFromMemory (assets_selection_tl, assets_selection_tl_len);
  tr_texture = LoadTextureFromMemory (assets_selection_tr, assets_selection_tr_len);
  bl_texture = LoadTextureFromMemory (assets_selection_bl, assets_selection_bl_len);
  br_texture = LoadTextureFromMemory (assets_selection_bl, assets_selection_br_len);

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

  font = LoadFontFromMemory (".ttf", assets_dejavusans,
                                  assets_dejavusans_len, 14, NULL, 0);

  button_hovered_texture = LoadTextureFromMemory (assets_button_hovered,
                                                  assets_button_hovered_len);
}

void
autodep_Draw_init (void)
{
  static int imported = 0;

  if (imported)
    return;

  Draw_init ();
  imported = 1;
}

void
DrawCursor (int _x, int _y, int size)
{
  DrawTexture (tl_texture, _x - 4, _y - 4, WHITE);
  DrawTexture (bl_texture, _x - 4, _y + size - 8 - 4, WHITE);
  DrawTexture (tr_texture, _x + size - 8 - 4, _y - 4, WHITE);
  DrawTexture (br_texture, _x + size - 8 - 4, _y + size - 8 - 4, WHITE);
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
