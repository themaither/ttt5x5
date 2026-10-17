#include <config.h>

#include <raylib.h>
#include <assets.h>

static Texture2D tl_texture;
static Texture2D tr_texture;
static Texture2D bl_texture;
static Texture2D br_texture;

static Texture2D
LoadTextureFromMemory (unsigned char *data, int length)
{
  Image image = LoadImageFromMemory(".png", data, length);
  Texture2D texture = LoadTextureFromImage (image);
  UnloadImage (image);
  return texture;
}

void
DrawCursor_init (void)
{
  tl_texture = LoadTextureFromMemory (assets_selection_tl, assets_selection_tl_len);
  tr_texture = LoadTextureFromMemory (assets_selection_tr, assets_selection_tr_len);
  bl_texture = LoadTextureFromMemory (assets_selection_bl, assets_selection_bl_len);
  br_texture = LoadTextureFromMemory (assets_selection_bl, assets_selection_br_len);
}

void
autodep_DrawCursor_init (void)
{
  static int imported = 0;

  if (imported)
    return;

  DrawCursor_init ();
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
