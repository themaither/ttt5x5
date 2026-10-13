#include <config.h>

#include <raylib.h>
#include <session.h>
#include <picker.h>
#include <title.h>
#include <completed.h>
#include <draw_field.h>
#include <draw_digit.h>
#include <draw_cursor.h>
#include <btn.h>
#include <dlf.h>
#include <config.h>
#include <gamescript.h>

int
main (int argc, char **argv)
{
  dlf_init ();
  completed_init ();
  SetTargetFPS (60);
  InitWindow (640, 400, PACKAGE_STRING);
  DrawField_init ();
  DrawDigit_init ();
  DrawCursor_init ();
  title_init ();
  session_init ();
  picker_init  ();

  int whaton = 2;

  while (!WindowShouldClose ())
    {
      BtnReadEvents ();

      switch (whaton)
        {
        case 0:
          picker_update ();
          if (picker_leaving ())
            {
              whaton = 2;
              picker_reset ();
            }
          if (picker_starting ())
            {
              whaton = 1;
              picker_reset ();
            }
          continue;
        case 1:
          session_update ();
          if (session_leaving ())
            {
              whaton = 0;
              session_reset ();
            }
          continue;
        case 2:
          title_update ();
          if (title_level_select ())
            {
              whaton = 0;
              title_reset ();
            }
          if (title_leaving ())
            {
              CloseWindow ();
              break;
            }
          continue;
        }

      break;
    }
}
