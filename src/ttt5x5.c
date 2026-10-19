#include <config.h>

#include <raylib.h>
#include <session.h>
#include <picker.h>
#include <title.h>
#include <locale.h>
#include <completed.h>
#include <draw_field.h>
#include <draw.h>
#include <btn.h>
#include <dlf.h>
#include <config.h>
#include <gamescript.h>
#include <assets.h>
#include <optbus.h>

static Texture2D
LoadTextureFromMemory (unsigned char *data, int length)
{
  Image image = LoadImageFromMemory(".png", data, length);
  Texture2D texture = LoadTextureFromImage (image);
  UnloadImage (image);
  return texture;
}

int
main (int argc, char **argv)
{
  setlocale (LC_ALL, "");

  autodep_optbus_init ();

  autodep_title_init   ();
  autodep_session_init ();
  autodep_picker_init  ();

  SetTargetFPS (60);
  InitWindow (640, 400, PACKAGE_STRING);

  autodep_title_ginit   ();
  autodep_session_ginit ();
  autodep_picker_ginit  ();

  optbus_parse (argc, argv);

  int whaton = 0;

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
              session_update ();
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
