#include <5x5.h>
#include <btn.h>
#include <stdio.h>
#include <raylib.h>
#include <math.h>
#include <imath.h>
#include <draw_field.h>
#include <completed.h>

static Texture2D picker_texture;
static Texture2D leave_texture;
static Texture2D leave_hovered_texture;
static Texture2D leave_pressed_texture;
static Texture2D completed_texture;

static int player_x = 0;
static int player_y = 0;

static float player_x_interp = 0.f;
static float player_y_interp = 0.f;

/* what cursor is on */
static int whaton = 0;

static int leaving = 0;

static int starting = 0;

void
picker_reset ()
{
  starting = 0;
  leaving = 0;
}

static void
DrawCursor (int _x, int _y, int size)
{
  DrawRectangle (_x - 4,            _y - 4,            8, 16, GREEN);
  DrawRectangle (_x - 4,            _y - 4,            16, 8, GREEN);

  DrawRectangle (_x - 4,            _y + size - 8 - 4, 8, 16, GREEN);
  DrawRectangle (_x - 4,            _y + size - 8 + 4, 16, 8, GREEN);

  DrawRectangle (_x + size - 8 + 4, _y - 4,            8, 16, GREEN);
  DrawRectangle (_x + size - 8 - 4, _y - 4,            16, 8, GREEN);

  DrawRectangle (_x + size - 8 + 4, _y + size - 8 - 4, 8, 16, GREEN);
  DrawRectangle (_x + size - 8 - 4, _y + size - 8 + 4, 16, 8, GREEN);
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
picker_leaving ()
{
  return leaving;
}

int
picker_starting ()
{
  return starting;
}

void
picker_init ()
{
  picker_texture = LoadTexture (PKGDATADIR "/picker.png");
  leave_texture = LoadTexture (PKGDATADIR "/back.png");
  leave_hovered_texture = LoadTexture (PKGDATADIR "/back_hovered.png");
  leave_pressed_texture = LoadTexture (PKGDATADIR "/back_pressed.png");
  completed_texture = LoadTexture (PKGDATADIR "/completed.png");
}

void
picker_update ()
{
  if (whaton == 1)
    {
      if (IsKeyPressed (KEY_S))
        {
          BtnAbort ();
          whaton = 0;
        }

      if (IsBtnPressed ())
        {
          leaving = 1;
        }
    }

  /* controls for pattern cursor */
  else if (whaton == 0)
    {
      if (IsKeyPressed (KEY_D))
        {
          BtnAbort ();
          ++player_x;
        }

      if (IsKeyPressed (KEY_A))
        {
          BtnAbort ();
          --player_x;
        }

      if (IsKeyPressed (KEY_W))
        {
          BtnAbort ();

          if (player_y == 0)
            whaton = 1;

          --player_y;
        }

      if (IsKeyPressed (KEY_S))
        {
          BtnAbort ();
          ++player_y;
        }

      if (IsBtnPressed ())
        {
          if (player_x == 0 && player_y == 0)
            {
              _5x5_clear ();
              _5x5_startpattern ();
              _5x5_filldesired ();
              completed_setid (0);

              starting = 1;
            }
          else if (player_x == 1 && player_y == 0)
            {
              _5x5_clear ();
              _5x5_startpattern ();
              _5x5_filldesired ();
              _5x5_interact_desired (2, 1);
              _5x5_interact_desired (2, 2);
              _5x5_interact_desired (2, 3);
              completed_setid (1);

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

  if (whaton == 1 && IsBtnDown ())
    DrawTexture (leave_pressed_texture, 2, 2, WHITE);
  else if (whaton == 1)
    DrawTexture (leave_hovered_texture, 2, 2, WHITE);
  else
    DrawTexture (leave_texture, 2, 2, WHITE);

  DrawField_flipall ();
  DrawField80 (56, 64);

  completed_setid (0);
  if (completed ())
    DrawTexture (completed_texture, 56 + 64, 64 + 64, WHITE);

  DrawField_flipall ();
  DrawField_interact (2, 1);
  DrawField_interact (2, 2);
  DrawField_interact (2, 3);
  DrawField80 (168, 64);

  completed_setid (1);
  if (completed ())
    DrawTexture (completed_texture, 168 + 64, 64 + 64, WHITE);

  if (whaton == 0)
    DrawCursor (56 + player_x_interp * 112, 64 + player_y_interp * 104, 80);

  EndDrawing ();
}
