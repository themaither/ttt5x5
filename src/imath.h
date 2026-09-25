/* imath.h: max min and clamp over integers
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef IMATH_H_INCLUDED
#define IMATH_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

int min   (int, int);
int max   (int, int);
int clamp (int, int lbound, int ubound);

#ifdef __cplusplus
}
#endif

#endif /* IMATH_H_INCLUDED */
