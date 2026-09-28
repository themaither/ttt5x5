/* btn.h: button clicking logic with proper abort mechanism
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef BTN_H_INCLUDED
#define BTN_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/* should be called every frame before IsBtnPressed and IsBtnDown */
void BtnReadEvents (void);

/* only registers if button was released after being pressed */
int  IsBtnPressed (void);

/* similar to Raylib IsKeyPressed and IsKeyDown */
int  IsBtnPressedRN (void);
int  IsBtnDown (void);

/* should be called when you move focus out of a thing you clicked */
void BtnAbort (void);

#ifdef __cplusplus
}
#endif

#endif /* BTN_H_INCLUDED */
