#include <config.h>

#include <5x5.h>
#include <btn.h>
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>
#include <imath.h>
#include <draw_field.h>
#include <draw.h>
#include <completed.h>
#include <database.h>
#include <assets.h>

static Texture2D picker_texture;
static Texture2D leave_texture;
static Texture2D leave_hovered_texture;
static Texture2D leave_pressed_texture;
static Texture2D completed_texture;
static Texture2D prev_texture;
static Texture2D prev_hovered_texture;
static Texture2D prev_pressed_texture;
static Texture2D prev_disabled_texture;
static Texture2D prev_hovered_disabled_texture;
static Texture2D next_texture;
static Texture2D next_hovered_texture;
static Texture2D next_pressed_texture;
static Texture2D next_disabled_texture;
static Texture2D next_hovered_disabled_texture;

static int player_x = 0;
static int player_y = 0;
static int mouse = 0;

static float player_x_interp = 0.f;
static float player_y_interp = 0.f;

/* what cursor is on */
static int whaton = 0;

static int top_whaton = 0;

static int leaving = 0;

static int starting = 0;

/* used to store field info for drawing functions */
static int buffer_field;

static int page = 0;

void
picker_reset (void)
{
  starting = 0;
  leaving = 0;
}

static float
lerp (float lhs, float rhs, float c)
{
  if (fabs (lhs - rhs) < 0.01)
  {
    if (c > 0.5)
      return rhs;
    else
      return lhs;
  }

  return lhs * c + rhs * (1 - c);
}

int
picker_leaving (void)
{
  return leaving;
}

int
picker_starting (void)
{
  return starting;
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
picker_init (void)
{
  picker_texture = LoadTextureFromMemory (assets_picker, assets_picker_len);

  leave_texture = LoadTextureFromMemory (assets_leave, assets_leave_len);
  leave_hovered_texture = LoadTextureFromMemory (assets_leave_hovered, assets_leave_hovered_len);
  leave_pressed_texture = LoadTextureFromMemory (assets_leave_pressed, assets_leave_pressed_len);

  completed_texture = LoadTextureFromMemory (assets_completed, assets_completed_len);

  prev_texture = LoadTextureFromMemory (assets_prev, assets_prev_len);
  prev_hovered_texture = LoadTextureFromMemory (assets_prev_hovered, assets_prev_hovered_len);
  prev_pressed_texture = LoadTextureFromMemory (assets_prev_pressed, assets_prev_pressed_len);
  prev_disabled_texture = LoadTextureFromMemory (assets_prev_disabled, assets_prev_disabled_len);
  prev_hovered_disabled_texture = LoadTextureFromMemory (assets_prev_hovered_disabled, assets_prev_hovered_disabled_len);

  next_texture = LoadTextureFromMemory (assets_next, assets_next_len);
  next_hovered_texture = LoadTextureFromMemory (assets_next_hovered, assets_next_hovered_len);
  next_pressed_texture = LoadTextureFromMemory (assets_next_pressed, assets_next_pressed_len);
  next_disabled_texture = LoadTextureFromMemory (assets_next_disabled, assets_next_disabled_len);
  next_hovered_disabled_texture = LoadTextureFromMemory (assets_next_hovered_disabled, assets_next_hovered_disabled_len);

  buffer_field = _5x5_open ();
}

void
autodep_picker_init (void)
{
  static int imported = 0;

  if (imported)
    return;

  autodep_completed_init ();
  autodep_DrawField_init ();
  autodep_Draw_init ();

  picker_init ();
  imported = 1;
}

void
picker_update (void)
{
  {
    Vector2 delta = GetMouseDelta ();
    int x = GetMouseX ();
    int y = GetMouseY ();

    if (fabs (delta.x) > 0. && fabs (delta.y) > 0.)
      mouse = 1;

    if (mouse)
      {
        if (x >= 2 && x <= 66)
          if (y >= 2 && y<= 34)
            {
              whaton = 1;
              top_whaton = 0;
            }

        if (x >= 248 && x <= 280)
          if (y >= 2 && y<= 34)
            {
              whaton = 1;
              top_whaton = 1;
            }

        if (x >= 360 && x <= 392)
          if (y >= 2 && y<= 34)
            {
              whaton = 1;
              top_whaton = 2;
            }

        for (int i = 0; i < 15; ++i)
          {
            int x1 = i % 5;
            int y1 = i / 5;

            if (x >= 56 + 112 * x1 && x <= 56 + 112 * x1 + 80)
              if (y >= 64 + 104 * y1 && y <= 64 + 104 * y1 + 80)
                {
                  whaton = 0;
                  player_x = x1;
                  player_y = y1;
                }
          }
      }
  }

  _5x5_select (0);
  if (whaton == 1)
    {
      if (IsKeyPressed (KEY_S))
        {
          BtnAbort ();
          whaton = 0;
          mouse = 0;
        }

      if (IsBtnPressed () && top_whaton == 0)
        {
          leaving = 1;
        }

      if (IsBtnPressed () && top_whaton == 1)
        {
          if (page > 0)
            --page;
        }

      if (IsBtnPressed () && top_whaton == 2)
        {
          if ((1 + page) * 15 < levelcount ())
            ++page;
        }

      if (IsKeyPressed (KEY_A))
        {
          BtnAbort ();
          --top_whaton;
          mouse = 0;
        }

      if (IsKeyPressed (KEY_D))
        {
          BtnAbort ();
          ++top_whaton;
          mouse = 0;
        }

      top_whaton = clamp (0, 2, top_whaton);
    }

  /* controls for pattern cursor */
  else if (whaton == 0)
    {
      if (IsKeyPressed (KEY_D))
        {
          BtnAbort ();
          ++player_x;
          mouse = 0;
        }

      if (IsKeyPressed (KEY_A))
        {
          BtnAbort ();
          --player_x;
          mouse = 0;
        }

      if (IsKeyPressed (KEY_W))
        {
          BtnAbort ();

          if (player_y == 0)
            whaton = 1;

          --player_y;
          mouse = 0;
        }

      if (IsKeyPressed (KEY_S))
        {
          BtnAbort ();
          ++player_y;
          mouse = 0;
        }

      if (IsBtnPressed ())
        {
          if (player_x + 5 * player_y + page * 15 < levelcount ())
            {
              _5x5_select (0);
              _5x5_clear ();
              _5x5_startpattern ();

              _5x5_select (1);
              _5x5_clear ();
              loadlevel       (page * 15 + player_x % 5 + player_y * 5);
              completed_setid (page * 15 + player_x % 5 + player_y * 5);

              _5x5_select (0);
              starting = 1;
            }
          return;
        }
    }

  player_x = clamp (player_x, 0, 4);
  player_y = clamp (player_y, 0, 2);

  player_x_interp = lerp (player_x, player_x_interp, 0.9);
  player_y_interp = lerp (player_y, player_y_interp, 0.9);

  BeginDrawing ();

  DrawTexture (picker_texture, 0, 0, WHITE);

  if (whaton == 1 && top_whaton == 0 && IsBtnDown ())
    DrawButton (leave_texture, 2, 2, 80, 32, 2);
  else if (whaton == 1 && top_whaton == 0)
    DrawButton (leave_texture, 2, 2, 80, 32, 1);
  else
    DrawButton (leave_texture, 2, 2, 80, 32, 3);

  if (page == 0)
    {
      if (whaton == 1 && top_whaton == 1)
        DrawTexture (prev_hovered_disabled_texture, 248, 2, WHITE);
      else
        DrawTexture (prev_disabled_texture, 248, 2, WHITE);
    }
  else
    {
      if (whaton == 1 && top_whaton == 1 && IsBtnDown ())
        DrawTexture (prev_pressed_texture, 248, 2, WHITE);
      else if (whaton == 1 && top_whaton == 1)
        DrawTexture (prev_hovered_texture, 248, 2, WHITE);
      else
        DrawTexture (prev_texture, 248, 2, WHITE);
    }

  DrawNumber3 (page + 1, 282, 6);

  if ((levelcount () - 1) / 15 <= page)
    {
      if (whaton == 1 && top_whaton == 2)
        DrawTexture (next_hovered_disabled_texture, 360, 2, WHITE);
      else
        DrawTexture (next_disabled_texture, 360, 2, WHITE);
    }
  else
    {
      if (whaton == 1 && top_whaton == 2 && IsBtnDown ())
        DrawTexture (next_pressed_texture, 360, 2, WHITE);
      else if (whaton == 1 && top_whaton == 2)
        DrawTexture (next_hovered_texture, 360, 2, WHITE);
      else
        DrawTexture (next_texture, 360, 2, WHITE);
    }

  _5x5_select (3);

  for (int i = 0; i < 15; ++i)
    {
      if (page * 15 + i >= levelcount ())
        break;

      int x = i % 5;
      int y = i / 5;

      loadlevel (page * 15 + i);
      DrawField80_selected (56 + 112 * x, 64 + 104 * y);
    }

  if (whaton == 0)
    DrawCursor (56 + player_x_interp * 112, 64 + player_y_interp * 104, 80);

  for (int i = 0; i < 15; ++i)
    {
      if (page * 15 + i >= levelcount ())
        break;

      int x = i % 5;
      int y = i / 5;

      completed_setid (page * 15 + i);
      if (completed ())
        DrawTexture (completed_texture, 56 + 112 * x + 64, 64 + 104 * y + 64, WHITE);
    }

  EndDrawing ();
}
