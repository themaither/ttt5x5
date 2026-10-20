#include <config.h>

#include <raylib.h>
#include <session.h>
#include <picker.h>
#include <title.h>
#include <locale.h>
#include <completed.h>
#include <draw_field.h>
#include <draw.h>
#include <database.h>
#include <btn.h>
#include <dlf.h>
#include <config.h>
#include <gamescript.h>
#include <assets.h>
#include <optbus.h>
#include <progmsg.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <5x5.h>

static Texture2D
LoadTextureFromMemory (unsigned char *data, int length)
{
  Image image = LoadImageFromMemory(".png", data, length);
  Texture2D texture = LoadTextureFromImage (image);
  UnloadImage (image);
  return texture;
}

static void
raylib_log (int level, const char *fmt, va_list ap)
{
  switch (level)
  {
    case LOG_DEBUG:
      break;
    case LOG_INFO:
      break;
    case LOG_WARNING:
      vprogmsg (fmt, ap);
      break;
    case LOG_ERROR:
      vprogmsg (fmt, ap);
      break;
  }
}

int
main (int argc, char **argv)
{
  srand (time (NULL));

  progmsg_setname (argv[0]);

  SetTraceLogCallback(raylib_log);

  setlocale (LC_ALL, "");

  autodep_optbus_init ();

  autodep_title_init   ();
  autodep_session_init ();
  autodep_picker_init  ();

  optbus_parse (argc, argv);

  SetTargetFPS (60);
  InitWindow (640, 400, PACKAGE_STRING);

  autodep_title_ginit   ();
  autodep_session_ginit ();
  autodep_picker_ginit  ();

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
          switch (title_status ())
            {
            case 1:
              whaton = 0;
              title_reset ();
              break;
            case 2:
              whaton = 3;
              _5x5_select (0);
              _5x5_startpattern ();
              _5x5_select (1);
              int level = rand () % levelcount ();
              loadlevel (level);
              completed_setid (level);
              title_reset ();
              break;
            case 3:
              CloseWindow ();
              break;
            }
          continue;
        case 3:
          session_update ();
          if (session_leaving ())
            {
              whaton = 2;
              session_reset ();
            }
          continue;
        }

      break;
    }
}
