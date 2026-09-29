#include <5x5.h>
#include <btn.h>
#include <stdio.h>
#include <raylib.h>
#include <math.h>
#include <imath.h>
#include <draw_field.h>
#include <completed.h>
#include <database.h>

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

/* used to store field info for drawing functions */
static int buffer_field;

void
picker_reset (void)
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
picker_leaving (void)
{
  return leaving;
}

int
picker_starting (void)
{
  return starting;
}

void
picker_init (void)
{
  picker_texture = LoadTexture (PKGDATADIR "/picker.png");
  leave_texture = LoadTexture (PKGDATADIR "/back.png");
  leave_hovered_texture = LoadTexture (PKGDATADIR "/back_hovered.png");
  leave_pressed_texture = LoadTexture (PKGDATADIR "/back_pressed.png");
  completed_texture = LoadTexture (PKGDATADIR "/completed.png");

  buffer_field = _5x5_open ();
}

void
picker_update (void)
{
  _5x5_select (0);
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
          if (player_x + 5 * player_y < levelcount ())
            {
              _5x5_select (0);
              _5x5_clear ();
              _5x5_startpattern ();

              _5x5_select (1);
              _5x5_clear ();
              loadlevel       (player_x % 5 + player_y * 5);
              completed_setid (player_x % 5 + player_y * 5);

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

  if (whaton == 1 && IsBtnDown ())
    DrawTexture (leave_pressed_texture, 2, 2, WHITE);
  else if (whaton == 1)
    DrawTexture (leave_hovered_texture, 2, 2, WHITE);
  else
    DrawTexture (leave_texture, 2, 2, WHITE);

  _5x5_select (3);

  for (int i = 0; i < 15; ++i)
    {
      if (i >= levelcount ())
        break;

      int x = i % 5;
      int y = i / 5;

      loadlevel (i);
      DrawField80_selected (56 + 112 * x, 64 + 104 * y);
      completed_setid (i);
      if (completed ())
        DrawTexture (completed_texture, 56 + 112 * x + 64, 64 + 104 * y + 64, WHITE);
    }

  if (whaton == 0)
    DrawCursor (56 + player_x_interp * 112, 64 + player_y_interp * 104, 80);

  EndDrawing ();
}
