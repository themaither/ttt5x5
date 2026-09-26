#include <raylib.h>

static int press = -1;
static int pressed = 0;
static int abadoned = 0;

void
BtnReadEvents ()
{
  if (IsKeyDown (KEY_SPACE))
    {
      if (!abadoned)
        press = KEY_SPACE;
    }
  else if (IsKeyDown (KEY_KP_ADD))
    {
      if (!abadoned)
        press = KEY_KP_ADD;
    }
  else if (IsKeyDown (KEY_ENTER))
    {
      if (!abadoned)
        press = KEY_ENTER;
    }
  else
    abadoned = 0;

  if (pressed)
    pressed = 0;

  if (press != -1 && IsKeyUp (press) && !pressed && !abadoned)
    {
      pressed = 1;
      press = -1;
    }
}

int
IsBtnPressed ()
{
  return pressed;
}

int
IsBtnPressedRN ()
{
  return IsKeyPressed (KEY_SPACE)
      || IsKeyPressed (KEY_KP_ADD)
      || IsKeyPressed (KEY_ENTER);
}

int
IsBtnDown ()
{
  return press != -1;
}

void
BtnAbort ()
{
  press = -1;
  pressed = 0;
  abadoned = 1;
}
