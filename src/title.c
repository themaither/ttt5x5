#include <config.h>

#include "title.h"

#include <raylib.h>
#include <stdio.h>
#include <btn.h>
#include <imath.h>
#include <math.h>
#include <assets.h>
#include <draw.h>

static int status;

enum
{
  STATUS_NONE,
  STATUS_LEVEL_SELECT,
  STATUS_RANDOM_LEVEL,
  STATUS_LEAVING
};

static int whaton = 0;
static int mouse = 0;

static Texture2D title_texture;
static Texture2D level_select_texture;
static Texture2D quit_texture;
static Texture2D random_level_texture;

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
  status = 0;
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

int
title_status (void)
{
  return status;
}

void
title_ginit (void)
{
  title_texture = LoadTextureFromMemory (assets_title, assets_title_len);
  level_select_texture = LoadTextureFromMemory (assets_level_select, assets_level_select_len);
  random_level_texture = LoadTextureFromMemory (assets_random_level, assets_random_level_len);
  quit_texture = LoadTextureFromMemory (assets_quit, assets_quit_len);
}

void
autodep_title_ginit (void)
{
  static int imported = 0;

  if (imported)
    return;

  title_ginit ();
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

        if (x >= 214 && x <= 214 + 212)
          if (y >= 102 + 56 * 2 && y <= 102 + 56 * 2 + 56)
            {
              whaton = 2;
            }
      }
  }

  if (IsBtnPressed ())
    {
      if (whaton == 0)
        status = STATUS_LEVEL_SELECT;

      if (whaton == 1)
        status = STATUS_RANDOM_LEVEL;

      if (whaton == 2)
        status = STATUS_LEAVING;
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

  whaton = clamp (whaton, 0, 2);

  BeginDrawing ();
  DrawTexture (title_texture, 0, 0, WHITE);

  if (whaton == 0 && IsBtnDown ())
    DrawButton (level_select_texture, 214, 102, 212, 56, 8);
  else if (whaton == 0)
    DrawButton (level_select_texture, 214, 102, 212, 56, 7);
  else
    DrawButton (level_select_texture, 214, 102, 212, 56, 6);

  if (whaton == 1 && IsBtnDown ())
    DrawButton (random_level_texture, 214, 102 + 56, 212, 56, 8);
  else if (whaton == 1)
    DrawButton (random_level_texture, 214, 102 + 56, 212, 56, 7);
  else
    DrawButton (random_level_texture, 214, 102 + 56, 212, 56, 6);

  if (whaton == 2 && IsBtnDown ())
    DrawButton (quit_texture, 214, 102 + 56 * 2, 212, 56, 8);
  else if (whaton == 2)
    DrawButton (quit_texture, 214, 102 + 56 * 2, 212, 56, 7);
  else
    DrawButton (quit_texture, 214, 102 + 56 * 2, 212, 56, 6);

  EndDrawing ();
}

void
title_reset (void)
{
  status = 0;
  whaton = 0;
}
