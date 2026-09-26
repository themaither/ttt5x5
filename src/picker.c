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
#define interact(X, Y) _5x5_interact_desired (X, Y)
#define LEVEL_0
#include <levels.X.h>
#undef LEVEL_0
#undef interact
              completed_setid (0);

              starting = 1;
            }
          else if (player_x == 1 && player_y == 0)
            {
              _5x5_clear ();
              _5x5_startpattern ();
              _5x5_filldesired ();
#define interact(X, Y) _5x5_interact_desired (X, Y)
#define LEVEL_1
#include <levels.X.h>
#undef LEVEL_1
#undef interact
              completed_setid (1);

              starting = 1;
            }
          else if (player_x == 2 && player_y == 0)
            {
              _5x5_clear ();
              _5x5_startpattern ();
              _5x5_filldesired ();
#define interact(X, Y) _5x5_interact_desired (X, Y)
#define LEVEL_2
#include <levels.X.h>
#undef LEVEL_2
#undef interact
              completed_setid (2);

              starting = 1;
            }
          else if (player_x == 3 && player_y == 0)
            {
              _5x5_clear ();
              _5x5_startpattern ();
              _5x5_filldesired ();
#define interact(X, Y) _5x5_interact_desired (X, Y)
#define LEVEL_3
#include <levels.X.h>
#undef LEVEL_3
#undef interact
              completed_setid (3);

              starting = 1;
            }
          else if (player_x == 4 && player_y == 0)
            {
              _5x5_clear ();
              _5x5_startpattern ();
              _5x5_filldesired ();
#define interact(X, Y) _5x5_interact_desired (X, Y)
#define LEVEL_4
#include <levels.X.h>
#undef LEVEL_4
#undef interact
              completed_setid (4);

              starting = 1;
            }
          else if (player_x == 0 && player_y == 1)
            {
              _5x5_clear ();
              _5x5_startpattern ();
              _5x5_filldesired ();
#define interact(X, Y) _5x5_interact_desired (X, Y)
#define LEVEL_5
#include <levels.X.h>
#undef LEVEL_5
#undef interact
              completed_setid (5);

              starting = 1;
            }
          else if (player_x == 1 && player_y == 1)
            {
              _5x5_clear ();
              _5x5_startpattern ();
              _5x5_filldesired ();
#define interact(X, Y) _5x5_interact_desired (X, Y)
#define LEVEL_6
#include <levels.X.h>
#undef LEVEL_6
#undef interact
              completed_setid (6);

              starting = 1;
            }
          else if (player_x == 2 && player_y == 1)
            {
              _5x5_clear ();
              _5x5_startpattern ();
              _5x5_filldesired ();
#define interact(X, Y) _5x5_interact_desired (X, Y)
#define LEVEL_7
#include <levels.X.h>
#undef LEVEL_7
#undef interact
              completed_setid (7);

              starting = 1;
            }
          else if (player_x == 3 && player_y == 1)
            {
              _5x5_clear ();
              _5x5_startpattern ();
              _5x5_filldesired ();
#define interact(X, Y) _5x5_interact_desired (X, Y)
#define LEVEL_8
#include <levels.X.h>
#undef LEVEL_8
#undef interact
              completed_setid (8);

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

#define interact(X, Y) DrawField_interact (X, Y)
#define LEVEL_0
#include <levels.X.h>
#undef LEVEL_0
#undef interact
  DrawField80 (56, 64);
  completed_setid (0);
  if (completed ())
    DrawTexture (completed_texture, 56 + 64, 64 + 64, WHITE);

#define interact(X, Y) DrawField_interact (X, Y)
#define LEVEL_1
#include <levels.X.h>
#undef LEVEL_1
#undef interact
  DrawField80 (56 + 112, 64);
  completed_setid (1);
  if (completed ())
    DrawTexture (completed_texture, 56 + 112 + 64, 64 + 64, WHITE);

#define interact(X, Y) DrawField_interact (X, Y)
#define LEVEL_2
#include <levels.X.h>
#undef LEVEL_2
#undef interact
  DrawField80 (56 + 112 * 2, 64);
  completed_setid (2);
  if (completed ())
    DrawTexture (completed_texture, 56 + 112 * 2 + 64, 64 + 64, WHITE);

#define interact(X, Y) DrawField_interact (X, Y)
#define LEVEL_3
#include <levels.X.h>
#undef LEVEL_3
#undef interact
  DrawField80 (56 + 112 * 3, 64);
  completed_setid (3);
  if (completed ())
    DrawTexture (completed_texture, 56 + 112 * 3 + 64, 64 + 64, WHITE);

#define interact(X, Y) DrawField_interact (X, Y)
#define LEVEL_4
#include <levels.X.h>
#undef LEVEL_4
#undef interact
  DrawField80 (56 + 112 * 4, 64);
  completed_setid (4);
  if (completed ())
    DrawTexture (completed_texture, 56 + 112 * 4 + 64, 64 + 64, WHITE);

#define interact(X, Y) DrawField_interact (X, Y)
#define LEVEL_5
#include <levels.X.h>
#undef LEVEL_5
#undef interact
  DrawField80 (56 + 112 * 0, 64 + 104);
  completed_setid (5);
  if (completed ())
    DrawTexture (completed_texture, 56 + 112 * 0 + 64, 64 + 104 + 64, WHITE);

#define interact(X, Y) DrawField_interact (X, Y)
#define LEVEL_6
#include <levels.X.h>
#undef LEVEL_6
#undef interact
  DrawField80 (56 + 112 * 1, 64 + 104);
  completed_setid (6);
  if (completed ())
    DrawTexture (completed_texture, 56 + 112 * 1 + 64, 64 + 104 + 64, WHITE);

#define interact(X, Y) DrawField_interact (X, Y)
#define LEVEL_7
#include <levels.X.h>
#undef LEVEL_7
#undef interact
  DrawField80 (56 + 112 * 2, 64 + 104);
  completed_setid (7);
  if (completed ())
    DrawTexture (completed_texture, 56 + 112 * 2 + 64, 64 + 104 + 64, WHITE);

#define interact(X, Y) DrawField_interact (X, Y)
#define LEVEL_8
#include <levels.X.h>
#undef LEVEL_8
#undef interact
  DrawField80 (56 + 112 * 3, 64 + 104);
  completed_setid (8);
  if (completed ())
    DrawTexture (completed_texture, 56 + 112 * 3 + 64, 64 + 104 + 64, WHITE);

  if (whaton == 0)
    DrawCursor (56 + player_x_interp * 112, 64 + player_y_interp * 104, 80);

  EndDrawing ();
}
