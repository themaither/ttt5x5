/* draw.h: various drawing
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

void Draw_init (void);
void autodep_Draw_init (void);

void autodep_DrawCursor_init (void);
void DrawCursor (int x, int y, int size);

void autodep_DrawDigit_init (void);
void DrawDigit (int digit, int x, int y);
void DrawNumber3 (int number, int x, int y);

#ifdef __cplusplus
}
#endif

#endif /* DRAW_H_INCLUDED */
