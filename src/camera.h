/* camera.h: camera manip and world coordinates
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

int x (int);
int y (int);

void setcamx    (int);
void setcamy    (int);
void centercamx (int);
void centercamy (int);

#ifdef __cplusplus
}
#endif

#endif /* CAMERA_H_INCLUDED */
