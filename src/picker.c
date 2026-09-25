#include <5x5.h>
#include <raylib.h>
#include <math.h>
#include <imath.h>
#include <draw_field.h>

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

static int leave_pressed = -1;
static int leaving = 0;

static int starting = 0;

void
picker_reset ()
{
  starting = 0;
  leaving = 0;
  leave_pressed = -1;
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
        whaton = 0;

      if (IsKeyDown (KEY_SPACE))
        leave_pressed = KEY_SPACE;

      if (IsKeyDown (KEY_KP_ADD))
        leave_pressed = KEY_KP_ADD;

      if (IsKeyDown (KEY_ENTER))
        leave_pressed = KEY_ENTER;

      if (leave_pressed != -1 && IsKeyUp (leave_pressed))
        {
          leave_pressed = 0;
          leaving = 1;
        }
    }

  /* controls for pattern cursor */
  else if (whaton == 0)
    {
      if (IsKeyPressed (KEY_D))
        ++player_x;

      if (IsKeyPressed (KEY_A))
        --player_x;

      if (IsKeyPressed (KEY_W))
        {
          if (player_y == 0)
            whaton = 1;

          --player_y;
        }

      if (IsKeyPressed (KEY_S))
        ++player_y;

      static int pressing = -1;

      if (IsKeyDown (KEY_SPACE))
        pressing = KEY_SPACE;

      if (IsKeyDown (KEY_KP_ADD))
        pressing = KEY_KP_ADD;

      if (IsKeyDown (KEY_ENTER))
        pressing = KEY_ENTER;

      if (pressing != -1)
      {
        if (IsKeyUp (pressing))
          {
            pressing = -1;

            if (player_x == 0 && player_y == 0)
              {
                _5x5_clear ();
                _5x5_startpattern ();
                _5x5_filldesired ();

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

                starting = 1;
              }
          }
      }

      if (IsKeyDown (KEY_SPACE)
          || IsKeyDown (KEY_KP_ADD)
          || IsKeyDown (KEY_ENTER))
        {
          pressing = 1;
        }

    }

  player_x = clamp (player_x, 0, 4);
  player_y = clamp (player_y, 0, 2);

  player_x_interp = lerp (player_x, player_x_interp, 0.9);
  player_y_interp = lerp (player_y, player_y_interp, 0.9);

  BeginDrawing ();

  DrawTexture (picker_texture, 0, 0, WHITE);

  if (leave_pressed != -1)
    DrawTexture (leave_pressed_texture, 2, 2, WHITE);
  else if (whaton == 1)
    DrawTexture (leave_hovered_texture, 2, 2, WHITE);
  else
    DrawTexture (leave_texture, 2, 2, WHITE);

  DrawField_flipall ();
  DrawField80 (56, 64);

  DrawTexture (completed_texture, 56 + 64, 64 + 64, WHITE);

  DrawField_flipall ();
  DrawField_interact (2, 1);
  DrawField_interact (2, 2);
  DrawField_interact (2, 3);
  DrawField80 (168, 64);

  if (whaton == 0)
    DrawCursor (56 + player_x_interp * 112, 64 + player_y_interp * 104, 80);

  EndDrawing ();
}
