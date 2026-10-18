#include <config.h>

#include <raylib.h>
#include <stdio.h>
#include <btn.h>
#include <imath.h>
#include <math.h>
#include <assets.h>
#include <draw.h>

static int level_select = 0;
static int leaving = 0;
static int whaton = 0;
static int mouse = 0;

static Texture2D title_texture;
static Texture2D level_select_texture;
static Texture2D quit_texture;

static Texture2D
LoadTextureFromMemory (unsigned char *data, int length)
{
  Image image = LoadImageFromMemory(".png", data, length);
  Texture2D texture = LoadTextureFromImage (image);
  UnloadImage (image);
  return texture;
}

void
title_init (void)
{
  title_texture = LoadTextureFromMemory (assets_title, assets_title_len);
  level_select_texture = LoadTextureFromMemory (assets_level_select, assets_level_select_len);
  quit_texture = LoadTextureFromMemory (assets_quit, assets_quit_len);
}

void
autodep_title_init (void)
{
  static int imported = 0;

  if (imported)
    return;

  title_init ();
  imported = 1;
}

void
title_update (void)
{
  {
    Vector2 delta = GetMouseDelta ();
    int x = GetMouseX ();
    int y = GetMouseY ();

    if (fabs (delta.x) > 0. && fabs (delta.y) > 0.)
      mouse = 1;

    if (mouse)
      {
        if (x >= 214 && x <= 214 + 212)
          if (y >= 102 && y <= 102 + 56)
            {
              whaton = 0;
            }

        if (x >= 214 && x <= 214 + 212)
          if (y >= 102 + 56 && y <= 102 + 56 + 56)
            {
              whaton = 1;
            }
      }
  }

  if (IsBtnPressed ())
    {
      if (whaton == 0)
        level_select = 1;

      if (whaton == 1)
        leaving = 1;
    }

  if (IsKeyPressed (KEY_S))
    {
      BtnAbort ();
      mouse = 0;
      ++whaton;
    }

  if (IsKeyPressed (KEY_W))
    {
      BtnAbort ();
      mouse = 0;
      --whaton;
    }

  whaton = clamp (whaton, 0, 1);

  BeginDrawing ();
  DrawTexture (title_texture, 0, 0, WHITE);

  if (whaton == 0 && IsBtnDown ())
    DrawButton (level_select_texture, 214, 102, 212, 56, 8);
  else if (whaton == 0)
    DrawButton (level_select_texture, 214, 102, 212, 56, 7);
  else
    DrawButton (level_select_texture, 214, 102, 212, 56, 6);

  if (whaton == 1 && IsBtnDown ())
    DrawButton (quit_texture, 214, 102 + 56, 212, 56, 8);
  else if (whaton == 1)
    DrawButton (quit_texture, 214, 102 + 56, 212, 56, 7);
  else
    DrawButton (quit_texture, 214, 102 + 56, 212, 56, 6);

  EndDrawing ();
}

void
title_reset (void)
{
  level_select = 0;
  leaving = 0;
  whaton = 0;
}

int
title_level_select (void)
{
  return level_select;
}

int
title_leaving (void)
{
  return leaving;
}
