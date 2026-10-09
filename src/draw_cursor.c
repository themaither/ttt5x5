#include <raylib.h>

static Texture2D tl_texture;
static Texture2D tr_texture;
static Texture2D bl_texture;
static Texture2D br_texture;

void
DrawCursor_init ()
{
  tl_texture = LoadTexture (PKGDATADIR "/selection_tl.png");
  tr_texture = LoadTexture (PKGDATADIR "/selection_tr.png");
  bl_texture = LoadTexture (PKGDATADIR "/selection_bl.png");
  br_texture = LoadTexture (PKGDATADIR "/selection_br.png");
}

void
DrawCursor (int _x, int _y, int size)
{
  DrawTexture (tl_texture, _x - 4, _y - 4, WHITE);
  DrawTexture (bl_texture, _x - 4, _y + size - 8 - 4, WHITE);
  DrawTexture (tr_texture, _x + size - 8 - 4, _y - 4, WHITE);
  DrawTexture (br_texture, _x + size - 8 - 4, _y + size - 8 - 4, WHITE);
}
