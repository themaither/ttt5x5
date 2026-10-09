/* draw_cursor.h: draws a bounding box with four angles
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef DRAW_CURSOR_H_INCLUDED
#define DRAW_CURSOR_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

void DrawCursor_init ();
void DrawCursor (int x, int y, int size);

#ifdef __cplusplus
}
#endif

#endif /* DRAW_CURSOR_H_INCLUDED */
