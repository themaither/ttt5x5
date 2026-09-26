#include <imath.h>
#include <5x5.h>
#include <camera.h>
#include <btn.h>
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <draw_field.h>

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

/* lerp with small alignment logic to work with animations */
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

static int player_x = 0;
static int player_y = 0;

static float player_x_interp = 0.f;
static float player_y_interp = 0.f;

static int press_x = 0;
static int press_y = 0;

static float press_animation = 0.f;
static float win_animation = 0.f;

static Texture2D session_texture;
static Texture2D black48_texture;
static Texture2D white48_texture;
static Texture2D dark_green48_texture;
static Texture2D light_green48_texture;
static Texture2D black16_texture;
static Texture2D white16_texture;
static Texture2D leave_texture;
static Texture2D leave_hovered_texture;
static Texture2D leave_pressed_texture;

/* what cursor is on */
static int whaton = 0;

static int leaving = 0;

void
session_reset ()
{
  leaving = 0;
  whaton = 0;
}

void
session_init ()
{
  session_texture = LoadTexture (PKGDATADIR "/session.png");
  black48_texture = LoadTexture (PKGDATADIR "/black48.png");
  white48_texture = LoadTexture (PKGDATADIR "/white48.png");
  dark_green48_texture = LoadTexture (PKGDATADIR "/dark_green48.png");
  light_green48_texture = LoadTexture (PKGDATADIR "/light_green48.png");
  black16_texture = LoadTexture (PKGDATADIR "/black16.png");
  white16_texture = LoadTexture (PKGDATADIR "/white16.png");
  leave_texture = LoadTexture (PKGDATADIR "/leave.png");
  leave_hovered_texture = LoadTexture (PKGDATADIR "/leave_hovered.png");
  leave_pressed_texture = LoadTexture (PKGDATADIR "/leave_pressed.png");
}

int
session_leaving ()
{
  return leaving;
}

void
session_update ()
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
        ++player_x;

      if (IsKeyPressed (KEY_A))
        --player_x;

      if (IsKeyPressed (KEY_W))
        {
          if (player_y == 0)
            {
              BtnAbort ();
              whaton = 1;
            }

          --player_y;
        }

      if (IsKeyPressed (KEY_S))
        ++player_y;

      if (IsBtnPressedRN ())
        {
          _5x5_interact (player_x, player_y);
          press_x = player_x;
          press_y = player_y;
          press_animation = 1.;
          if (_5x5_matches ())
            {
              win_animation = 1.;
            }
        }
    }

  press_animation = fmax (0.f, press_animation - GetFrameTime () * 2.f);
  win_animation   = fmax (0.f, win_animation   - GetFrameTime () * 2.f);

  player_x = clamp (player_x, 0, 4);
  player_y = clamp (player_y, 0, 4);

  player_x_interp = lerp (player_x, player_x_interp, 0.9);
  player_y_interp = lerp (player_y, player_y_interp, 0.9);

  BeginDrawing ();

  DrawTexture (session_texture, 0, 0, WHITE);


  for (size_t i = 0; i < 5; ++i)
    for (size_t j = 0; j < 5; ++j)
      if (_5x5_colorat (j, i) == 1)
        DrawField_flipat (j, i);

  if (win_animation > .8)
    DrawField240_green (200, 51);
  else if (win_animation > .4 && win_animation < .6)
    DrawField240_green (200, 51);
  else
    DrawField240 (200, 51);

  for (size_t i = 0; i < 5; ++i)
    for (size_t j = 0; j < 5; ++j)
      if (_5x5_colorat_desired (j, i) == 1)
        DrawField_flipat (j, i);

  DrawField80 (280, 306);

  setcamx (200);
  setcamy (51);
  DrawRectangle
    (x (press_x * 48) - 48 * (1.f - (press_animation * press_animation)),
     y (press_y * 48) - 48 * (1.f - (press_animation * press_animation)),
     48 + 48 * 2 * (1.f - (press_animation * press_animation)),
     48 + 48 * 2 * (1.f - (press_animation * press_animation)),
     ColorAlpha (WHITE, press_animation));

  if (whaton == 0)
    DrawCursor (x (player_x_interp * 48), y (player_y_interp * 48), 48);

  if (whaton == 1 && IsBtnDown ())
    DrawTexture (leave_pressed_texture, 2, 2, WHITE);
  else if (whaton == 1)
    DrawTexture (leave_hovered_texture, 2, 2, WHITE);
  else
    DrawTexture (leave_texture, 2, 2, WHITE);

  EndDrawing ();
}
