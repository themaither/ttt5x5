/* draw.h: various drawing
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

void Draw_init (void);
void autodep_Draw_init (void);

void DrawCursor (int x, int y, int size);

void DrawDigit (int digit, int x, int y);
void DrawNumber3 (int number, int x, int y);

void DrawButton (Texture2D text, int x, int y, int width, int height, int mode);

#ifdef __cplusplus
}
#endif

#endif /* DRAW_H_INCLUDED */
