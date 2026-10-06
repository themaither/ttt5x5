#include <imath.h>
#include <5x5.h>
#include <camera.h>
#include <completed.h>
#include <btn.h>
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
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
static Texture2D moves_texture;

static Texture2D digit_textures[10];

/* what cursor is on */
static int whaton = 0;

static int leaving = 0;

static int moves = 0;

static void
DrawDigit (int digit, int x, int y)
{
  assert (digit >= 0);
  assert (digit <= 9);
  DrawTexture(digit_textures[digit], x, y, WHITE);
}

void
session_reset (void)
{
  leaving = 0;
  whaton = 0;
  moves = 0;
}

void
session_init (void)
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
  moves_texture = LoadTexture (PKGDATADIR "/moves.png");

  digit_textures[0] = LoadTexture (PKGDATADIR "/digit_0.png");
  digit_textures[1] = LoadTexture (PKGDATADIR "/digit_1.png");
  digit_textures[2] = LoadTexture (PKGDATADIR "/digit_2.png");
  digit_textures[3] = LoadTexture (PKGDATADIR "/digit_3.png");
  digit_textures[4] = LoadTexture (PKGDATADIR "/digit_4.png");
  digit_textures[5] = LoadTexture (PKGDATADIR "/digit_5.png");
  digit_textures[6] = LoadTexture (PKGDATADIR "/digit_6.png");
  digit_textures[7] = LoadTexture (PKGDATADIR "/digit_7.png");
  digit_textures[8] = LoadTexture (PKGDATADIR "/digit_8.png");
  digit_textures[9] = LoadTexture (PKGDATADIR "/digit_9.png");
}

int
session_leaving (void)
{
  return leaving;
}

void
session_update (void)
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
          _5x5_resetgame ();
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
          ++moves;

          press_x = player_x;
          press_y = player_y;
          press_animation = 1.;
          if (_5x5_matches ())
            win_animation = 1.;

          if (_5x5_won ())
            complete ();
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

  _5x5_select (0);
  if (win_animation > .8)
    DrawField240_green_selected (200, 51);
  else if (win_animation > .4 && win_animation < .6)
    DrawField240_green_selected (200, 51);
  else
    DrawField240_selected (200, 51);

  _5x5_select (1);
  DrawField80_selected (280, 306);

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

  DrawTexture (moves_texture, 336, 2, WHITE);
  DrawDigit (moves % 10 , 452, 6);
  DrawDigit ((moves / 10) % 10 , 426, 6);
  DrawDigit ((moves / 100) % 10 , 400, 6);

  EndDrawing ();
}
