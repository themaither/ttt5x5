/* draw_field.h: drawing 5x5 field
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef DRAW_FIELD_H_INCLUDED
#define DRAW_FIELD_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

void DrawField_init     ();
void DrawField_clear    ();
void DrawField_flipall  ();
void DrawField_flipat   (int x, int y);
void DrawField_interact (int x, int y);

/* each draw call clears the internal field */
void DrawField80        (int x, int y);
void DrawField240       (int x, int y);
void DrawField240_green (int x, int y);

#ifdef __cplusplus
}
#endif

#endif /* DRAW_FIELD_H_INCLUDED */
