/* draw_digit.h: drawing digits and numbers
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef DRAW_DIGIT_H_INCLUDED
#define DRAW_DIGIT_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

void DrawDigit_init ();
void DrawDigit (int digit, int x, int y);
void DrawNumber3 (int number, int x, int y);

#ifdef __cplusplus
}
#endif

#endif /* DRAW_DIGIT_H_INCLUDED */
