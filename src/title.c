#include <config.h>

#include <raylib.h>
#include <stdio.h>
#include <btn.h>
#include <imath.h>
#include <math.h>

static int level_select = 0;
static int leaving = 0;
static int whaton = 0;
static int mouse = 0;

static Texture2D title_texture;
static Texture2D level_select_texture;
static Texture2D level_select_hovered_texture;
static Texture2D level_select_pressed_texture;
static Texture2D quit_texture;
static Texture2D quit_hovered_texture;
static Texture2D quit_pressed_texture;

void
title_init (void)
{
  title_texture = LoadTexture (PKGDATADIR "/title.png");
  level_select_texture = LoadTexture (PKGDATADIR "/level_select.png");
  level_select_hovered_texture = LoadTexture (PKGDATADIR "/level_select_hovered.png");
  level_select_pressed_texture = LoadTexture (PKGDATADIR "/level_select_pressed.png");
  quit_texture = LoadTexture (PKGDATADIR "/quit.png");
  quit_hovered_texture = LoadTexture (PKGDATADIR "/quit_hovered.png");
  quit_pressed_texture = LoadTexture (PKGDATADIR "/quit_pressed.png");
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
    DrawTexture (level_select_pressed_texture, 214, 102, WHITE);
  else if (whaton == 0)
    DrawTexture (level_select_hovered_texture, 214, 102, WHITE);
  else
    DrawTexture (level_select_texture, 214, 102, WHITE);

  if (whaton == 1 && IsBtnDown ())
    DrawTexture (quit_pressed_texture, 214, 102 + 56, WHITE);
  else if (whaton == 1)
    DrawTexture (quit_hovered_texture, 214, 102 + 56, WHITE);
  else
    DrawTexture (quit_texture, 214, 102 + 56, WHITE);

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
