/* draw_field.h: drawing 5x5 field
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef DRAW_FIELD_H_INCLUDED
#define DRAW_FIELD_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

void DrawField_init     (void);
void DrawField_clear    (void);
void DrawField_flipall  (void);
void DrawField_flipat   (int x, int y);
void DrawField_interact (int x, int y);

/* each draw call clears the internal field */
void DrawField80        (int x, int y);
void DrawField240       (int x, int y);
void DrawField240_green (int x, int y);

/* drawing directly from selected field */
void DrawField80_selected        (int x, int y);
void DrawField240_selected       (int x, int y);
void DrawField240_green_selected (int x, int y);

#ifdef __cplusplus
}
#endif

#endif /* DRAW_FIELD_H_INCLUDED */
