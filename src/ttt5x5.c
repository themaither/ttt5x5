#include <raylib.h>
#include <session.h>
#include <picker.h>
#include <draw_field.h>
#include <btn.h>

int
main (int argc, char **argv)
{
  SetTargetFPS (60);
  InitWindow (640, 400, "ttt5x5");

  int whaton = 0;

  DrawField_init ();
  session_init ();
  picker_init  ();

  while (!WindowShouldClose ())
    {
      BtnReadEvents ();

      if (whaton == 0)
        {
          picker_update ();
          if (picker_leaving ())
            {
              CloseWindow ();
              break;
            }
          if (picker_starting ())
            {
              whaton = 1;
              picker_reset ();
            }
        }
      else
        {
          session_update ();
          if (session_leaving ())
            {
              whaton = 0;
              session_reset ();
            }
        }
    }
}
