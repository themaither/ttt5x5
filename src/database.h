/* database.h: essentialy a trash bin
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

/* gets a level from an id and loads it into selected 5x5 field */
void loadlevel (int id);

int levelcount ();

#ifdef __cplusplus
}
#endif

#endif /* DATABASE_H_INCLUDED */
