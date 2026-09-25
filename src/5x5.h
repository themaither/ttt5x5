/* 5x5.h: reimplementation of 5x5 game from emacs
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef _5X5_H_INCLUDED
#define _5X5_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/* OVERALL GAME LOGIC */


/* checks if primary and desired patterns were matching atleast once */
int  _5x5_won             ();

/* checks if primary and desired patterns are matching right now */
int  _5x5_matches         ();


/* WORKING WITH PRIMARY PATTERN */


/* sets all primary pattern cells to zero */
void _5x5_clear ();

/* clears primary pattern and adds a cross at the center */
void _5x5_startpattern ();

/* interacts with the cell in primary pattern
   if primary pattern and desired pattern matched runs logic for winning */
void _5x5_interact (int x, int y);

/* get color of cell in primary pattern */
int  _5x5_colorat (int x, int y);


/* WORKING WITH DESIRED PATTERN */


/* fills desired pattern with ones */
void _5x5_filldesired ();

/* flips one cell in desired pattern */
void _5x5_flipat_desired (int x, int y);

/* flips cross in desired pattern, does not affect winning state */
void _5x5_interact_desired (int x, int y);

/* get color of cell in desired pattern */
int  _5x5_colorat_desired (int x, int y);

#ifdef __cplusplus
}
#endif

#endif /* _5X5_H_INCLUDED */
