/* completed.h: database for completed levels
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef COMPLETED_H_INCLUDED
#define COMPLETED_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

void completed_init ();

/* chooses level by id */
void completed_setid (int);

int  completed ();
void complete  ();

#ifdef __cplusplus
}
#endif

#endif /* COMPLETED_H_INCLUDED */
