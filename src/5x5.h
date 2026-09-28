/* 5x5.h: reimplementation of 5x5 game from emacs
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef _5X5_H_INCLUDED
#define _5X5_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/* primary pattern is at index 0 */
/* desired pattern is at index 1 */


/* OVERALL GAME LOGIC */

/* checks if primary and desired patterns were matching atleast once */
int  _5x5_won             (void);

/* checks if primary and desired patterns are matching right now */
int  _5x5_matches         (void);


/* SELECTION MANAGEMENT */

/* opens a new game field. DOES NOT automatically selects it. there is an
   implementation defined limit to amount of opened fields */
int _5x5_open (void);

/* changes the current selection */
void _5x5_select (int);

/* returns current selection */
int _5x5_selection (void);


/* WORKING WITH SELECTED PATTERN */

/* get color of cell in selected pattern */
int  _5x5_colorat (int x, int y);

/* sets all selected pattern cells to zero */
void _5x5_clear (void);

/* flips one cell in selected pattern */
void _5x5_flipat (int x, int y);

/* clears selected pattern and adds a cross at the center */
void _5x5_startpattern (void);

/* interacts with the cell in selected pattern.
   if primary pattern and desired pattern matched
   runs logic for winning */
void _5x5_interact (int x, int y);


#ifdef __cplusplus
}
#endif

#endif /* _5X5_H_INCLUDED */
