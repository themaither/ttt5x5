#include <5x5.h>

void
loadlevel (int id)
{
  _5x5_clear ();

  switch (id) {
    case 0:
      break;

    case 1:
      _5x5_interact (0, 0);
      _5x5_interact (4, 0);
      _5x5_interact (4, 4);
      _5x5_interact (0, 4);
      break;

    case 2:
      _5x5_interact (0, 2);
      _5x5_interact (4, 2);
      break;

    case 3:
      _5x5_interact (1, 2);
      _5x5_interact (3, 2);
      break;

    case 4:
      _5x5_interact (2, 1);
      _5x5_interact (2, 3);
      break;

    case 5:
      _5x5_interact (1, 2);
      _5x5_interact (3, 2);
      _5x5_interact (2, 1);
      _5x5_interact (2, 3);
      break;

    case 6:
      _5x5_interact (1, 1);
      _5x5_interact (3, 1);
      _5x5_interact (3, 3);
      _5x5_interact (1, 3);
      break;

    case 7:
      _5x5_interact (1, 1);
      _5x5_interact (3, 1);
      _5x5_interact (3, 3);
      _5x5_interact (1, 3);
      _5x5_interact (2, 2);
      break;

    case 8:
      _5x5_interact (2, 1);
      _5x5_interact (2, 2);
      _5x5_interact (2, 3);
      break;

    case 9:
      _5x5_interact (2, 1);
      _5x5_interact (2, 2);
      _5x5_interact (2, 3);
      _5x5_interact (1, 2);
      _5x5_interact (3, 2);
      break;

    case 10:
      _5x5_interact (2, 1);
      _5x5_interact (2, 2);
      _5x5_interact (2, 3);
      _5x5_interact (1, 2);
      _5x5_interact (3, 2);
      _5x5_interact (4, 0);
      _5x5_interact (4, 4);
      _5x5_interact (0, 4);
      _5x5_interact (0, 0);
      break;

    case 11:
      _5x5_interact (2, 0);
      _5x5_interact (0, 2);
      _5x5_interact (2, 4);
      _5x5_interact (4, 2);
      _5x5_interact (3, 1);
      _5x5_interact (1, 1);
      _5x5_interact (1, 3);
      _5x5_interact (3, 3);
      break;

    case 12:
      _5x5_interact (2, 0);
      _5x5_interact (0, 2);
      _5x5_interact (2, 4);
      _5x5_interact (4, 2);
      _5x5_interact (3, 1);
      _5x5_interact (1, 1);
      _5x5_interact (1, 3);
      _5x5_interact (3, 3);
      _5x5_interact (2, 2);
      break;

    case 13:
      _5x5_interact (0, 0);
      _5x5_interact (4, 0);
      _5x5_interact (4, 4);
      _5x5_interact (0, 4);
      _5x5_interact (2, 1);
      _5x5_interact (1, 2);
      _5x5_interact (2, 3);
      _5x5_interact (3, 2);
      break;

    case 14:
      _5x5_interact (0, 0);
      _5x5_interact (4, 0);
      _5x5_interact (4, 4);
      _5x5_interact (0, 4);
      _5x5_interact (2, 1);
      _5x5_interact (1, 2);
      _5x5_interact (2, 3);
      _5x5_interact (3, 2);
      _5x5_interact (2, 0);
      _5x5_interact (4, 2);
      _5x5_interact (2, 4);
      _5x5_interact (0, 2);
      break;

    case 15:
      _5x5_interact (0, 0);
      _5x5_interact (0, 2);
      _5x5_interact (0, 4);
      _5x5_interact (2, 4);
      _5x5_interact (4, 4);
      _5x5_interact (4, 2);
      _5x5_interact (4, 0);
      _5x5_interact (2, 0);
      _5x5_interact (2, 1);
      _5x5_interact (1, 2);
      _5x5_interact (2, 3);
      _5x5_interact (3, 2);
      _5x5_interact (2, 1);
      _5x5_interact (2, 2);
      _5x5_interact (2, 3);
      _5x5_interact (1, 2);
      _5x5_interact (3, 2);
      break;

    case 16:
      _5x5_interact (0, 3);
      _5x5_interact (0, 1);
      _5x5_interact (4, 1);
      _5x5_interact (4, 3);
      break;

    case 17:
      _5x5_interact (1, 0);
      _5x5_interact (3, 0);
      _5x5_interact (3, 4);
      _5x5_interact (1, 4);
      break;

    case 18:
      _5x5_interact (1, 0);
      _5x5_interact (0, 1);
      _5x5_interact (0, 3);
      _5x5_interact (1, 4);
      _5x5_interact (3, 4);
      _5x5_interact (4, 3);
      _5x5_interact (4, 1);
      _5x5_interact (3, 0);
      break;

    case 19:
      _5x5_interact (1, 0);
      _5x5_interact (0, 1);
      _5x5_interact (0, 3);
      _5x5_interact (1, 4);
      _5x5_interact (3, 4);
      _5x5_interact (4, 3);
      _5x5_interact (4, 1);
      _5x5_interact (3, 0);
      _5x5_interact (2, 2);
      break;

    case 20:
      _5x5_interact (2, 0);
      _5x5_interact (1, 1);
      _5x5_interact (0, 2);
      _5x5_interact (1, 3);
      _5x5_interact (2, 4);
      _5x5_interact (3, 3);
      _5x5_interact (4, 2);
      _5x5_interact (3, 1);
      _5x5_interact (0, 0);
      _5x5_interact (0, 4);
      _5x5_interact (4, 4);
      _5x5_interact (4, 0);
      break;

    case 21:
      _5x5_interact (1, 2);
      _5x5_interact (3, 2);
      _5x5_interact (0, 2);
      _5x5_interact (1, 1);
      _5x5_interact (2, 0);
      _5x5_interact (3, 1);
      _5x5_interact (4, 2);
      _5x5_interact (3, 3);
      _5x5_interact (2, 4);
      _5x5_interact (1, 3);
      _5x5_interact (0, 0);
      _5x5_interact (4, 0);
      _5x5_interact (4, 4);
      _5x5_interact (0, 4);
      break;

    case 22:
      _5x5_interact (2, 1);
      _5x5_interact (2, 2);
      _5x5_interact (2, 3);
      _5x5_interact (2, 0);
      _5x5_interact (1, 1);
      _5x5_interact (0, 2);
      _5x5_interact (1, 3);
      _5x5_interact (2, 4);
      _5x5_interact (3, 3);
      _5x5_interact (4, 2);
      _5x5_interact (3, 1);
      _5x5_interact (0, 0);
      _5x5_interact (0, 4);
      _5x5_interact (4, 4);
      _5x5_interact (4, 0);
      break;

    case 23:
      _5x5_interact (1, 2);
      _5x5_interact (3, 2);
      _5x5_interact (1, 0);
      _5x5_interact (1, 1);
      _5x5_interact (0, 1);
      _5x5_interact (0, 3);
      _5x5_interact (1, 3);
      _5x5_interact (1, 4);
      _5x5_interact (3, 4);
      _5x5_interact (3, 3);
      _5x5_interact (4, 3);
      _5x5_interact (4, 1);
      _5x5_interact (3, 1);
      _5x5_interact (3, 0);
      _5x5_interact (2, 0);
      _5x5_interact (1, 1);
      _5x5_interact (0, 2);
      _5x5_interact (1, 3);
      _5x5_interact (2, 4);
      _5x5_interact (3, 3);
      _5x5_interact (4, 2);
      _5x5_interact (3, 1);
      _5x5_interact (4, 0);
      _5x5_interact (0, 0);
      _5x5_interact (0, 4);
      _5x5_interact (4, 4);
      break;

    case 24:
      _5x5_interact (2, 1);
      _5x5_interact (2, 3);
      _5x5_interact (1, 0);
      _5x5_interact (1, 1);
      _5x5_interact (0, 1);
      _5x5_interact (0, 3);
      _5x5_interact (1, 3);
      _5x5_interact (1, 4);
      _5x5_interact (3, 4);
      _5x5_interact (3, 3);
      _5x5_interact (4, 3);
      _5x5_interact (4, 1);
      _5x5_interact (3, 1);
      _5x5_interact (3, 0);
      _5x5_interact (2, 0);
      _5x5_interact (1, 1);
      _5x5_interact (0, 2);
      _5x5_interact (1, 3);
      _5x5_interact (2, 4);
      _5x5_interact (3, 3);
      _5x5_interact (4, 2);
      _5x5_interact (3, 1);
      _5x5_interact (4, 0);
      _5x5_interact (0, 0);
      _5x5_interact (0, 4);
      _5x5_interact (4, 4);
      break;

    case 25:
      _5x5_interact (2, 0);
      _5x5_interact (3, 1);
      _5x5_interact (4, 2);
      _5x5_interact (3, 3);
      _5x5_interact (2, 4);
      _5x5_interact (1, 3);
      _5x5_interact (0, 2);
      _5x5_interact (1, 1);
      _5x5_interact (2, 1);
      _5x5_interact (1, 2);
      _5x5_interact (2, 3);
      _5x5_interact (3, 2);
      _5x5_interact (2, 2);
      break;

    case 26:
      _5x5_interact (0, 0);
      _5x5_interact (1, 0);
      _5x5_interact (2, 0);
      _5x5_interact (3, 0);
      _5x5_interact (4, 0);
      _5x5_interact (4, 1);
      _5x5_interact (3, 1);
      _5x5_interact (2, 1);
      _5x5_interact (1, 1);
      _5x5_interact (0, 1);
      _5x5_interact (0, 2);
      _5x5_interact (1, 2);
      _5x5_interact (2, 2);
      _5x5_interact (3, 2);
      _5x5_interact (4, 2);
      _5x5_interact (4, 3);
      _5x5_interact (3, 3);
      _5x5_interact (2, 3);
      _5x5_interact (1, 3);
      _5x5_interact (0, 3);
      _5x5_interact (0, 4);
      _5x5_interact (1, 4);
      _5x5_interact (2, 4);
      _5x5_interact (3, 4);
      _5x5_interact (4, 4);
      break;

    case 27:
      _5x5_interact (2, 0);
      _5x5_interact (2, 1);
      _5x5_interact (2, 2);
      _5x5_interact (2, 3);
      _5x5_interact (2, 4);
      break;

    case 28:
      _5x5_interact (0, 1);
      _5x5_interact (1, 1);
      _5x5_interact (2, 1);
      _5x5_interact (3, 1);
      _5x5_interact (4, 1);
      _5x5_interact (4, 3);
      _5x5_interact (3, 3);
      _5x5_interact (2, 3);
      _5x5_interact (1, 3);
      _5x5_interact (0, 3);
      break;

    case 29:
      _5x5_interact (2, 0);
      _5x5_interact (2, 1);
      _5x5_interact (2, 2);
      _5x5_interact (2, 3);
      _5x5_interact (2, 4);
      _5x5_interact (0, 1);
      _5x5_interact (1, 1);
      _5x5_interact (2, 1);
      _5x5_interact (3, 1);
      _5x5_interact (4, 1);
      _5x5_interact (4, 3);
      _5x5_interact (3, 3);
      _5x5_interact (2, 3);
      _5x5_interact (1, 3);
      _5x5_interact (0, 3);
      break;

    case 30:
      _5x5_interact (1, 0);
      _5x5_interact (1, 1);
      _5x5_interact (1, 2);
      _5x5_interact (1, 3);
      _5x5_interact (1, 4);
      _5x5_interact (3, 4);
      _5x5_interact (3, 3);
      _5x5_interact (3, 2);
      _5x5_interact (3, 1);
      _5x5_interact (3, 0);
      _5x5_interact (2, 0);
      _5x5_interact (1, 1);
      _5x5_interact (0, 2);
      _5x5_interact (1, 3);
      _5x5_interact (2, 4);
      _5x5_interact (3, 3);
      _5x5_interact (4, 2);
      _5x5_interact (3, 1);
      break;

    case 31:
      _5x5_interact (4, 0);
      _5x5_interact (4, 1);
      _5x5_interact (4, 2);
      _5x5_interact (4, 3);
      _5x5_interact (4, 4);
      _5x5_interact (2, 4);
      _5x5_interact (2, 3);
      _5x5_interact (2, 2);
      _5x5_interact (2, 1);
      _5x5_interact (2, 0);
      _5x5_interact (0, 0);
      _5x5_interact (0, 1);
      _5x5_interact (0, 2);
      _5x5_interact (0, 3);
      _5x5_interact (0, 4);
      break;

    case 32:
      _5x5_interact (4, 0);
      _5x5_interact (4, 1);
      _5x5_interact (4, 2);
      _5x5_interact (4, 3);
      _5x5_interact (4, 4);
      _5x5_interact (2, 4);
      _5x5_interact (2, 3);
      _5x5_interact (2, 2);
      _5x5_interact (2, 1);
      _5x5_interact (2, 0);
      _5x5_interact (0, 0);
      _5x5_interact (0, 1);
      _5x5_interact (0, 2);
      _5x5_interact (0, 3);
      _5x5_interact (0, 4);
      _5x5_interact (0, 1);
      _5x5_interact (1, 1);
      _5x5_interact (2, 1);
      _5x5_interact (3, 1);
      _5x5_interact (4, 1);
      _5x5_interact (4, 3);
      _5x5_interact (3, 3);
      _5x5_interact (2, 3);
      _5x5_interact (1, 3);
      _5x5_interact (0, 3);
      break;

    case 33:
      _5x5_interact (3, 1);
      _5x5_interact (4, 1);
      _5x5_interact (4, 3);
      _5x5_interact (3, 3);
      _5x5_interact (1, 3);
      _5x5_interact (0, 3);
      _5x5_interact (0, 1);
      _5x5_interact (1, 1);
      _5x5_interact (2, 2);
      break;

    case 34:
      _5x5_interact (1, 0);
      _5x5_interact (1, 1);
      _5x5_interact (0, 1);
      _5x5_interact (0, 0);
      _5x5_interact (3, 4);
      _5x5_interact (3, 3);
      _5x5_interact (4, 3);
      _5x5_interact (4, 4);
      break;

    case 35:
      _5x5_interact (3, 1);
      _5x5_interact (3, 0);
      _5x5_interact (1, 3);
      _5x5_interact (1, 4);
      break;

    case 36:
      _5x5_interact (1, 1);
      _5x5_interact (2, 2);
      _5x5_interact (3, 3);
      break;

    case 37:
      _5x5_interact (0, 0);
      _5x5_interact (1, 1);
      _5x5_interact (2, 2);
      _5x5_interact (3, 3);
      _5x5_interact (4, 4);
      break;

    case 38:
      _5x5_interact (2, 3);
      _5x5_interact (2, 4);
      _5x5_interact (1, 4);
      _5x5_interact (1, 3);
      _5x5_interact (3, 2);
      _5x5_interact (3, 1);
      _5x5_interact (4, 1);
      _5x5_interact (4, 2);
      break;

    case 39:
      _5x5_interact (2, 3);
      _5x5_interact (2, 4);
      _5x5_interact (1, 4);
      _5x5_interact (1, 3);
      _5x5_interact (3, 2);
      _5x5_interact (3, 1);
      _5x5_interact (4, 1);
      _5x5_interact (4, 2);
      _5x5_interact (4, 4);
      _5x5_interact (3, 3);
      _5x5_interact (2, 2);
      break;

    case 40:
      _5x5_interact (2, 3);
      _5x5_interact (2, 4);
      _5x5_interact (1, 4);
      _5x5_interact (1, 3);
      _5x5_interact (3, 2);
      _5x5_interact (3, 1);
      _5x5_interact (4, 1);
      _5x5_interact (4, 2);
      _5x5_interact (4, 4);
      _5x5_interact (3, 3);
      _5x5_interact (2, 2);
      _5x5_interact (1, 1);
      _5x5_interact (1, 0);
      _5x5_interact (0, 0);
      _5x5_interact (0, 1);
      break;

    case 41:
      _5x5_interact (2, 3);
      _5x5_interact (2, 4);
      _5x5_interact (1, 4);
      _5x5_interact (1, 3);
      _5x5_interact (3, 2);
      _5x5_interact (3, 1);
      _5x5_interact (4, 1);
      _5x5_interact (4, 2);
      _5x5_interact (4, 4);
      _5x5_interact (3, 3);
      _5x5_interact (2, 2);
      _5x5_interact (1, 1);
      _5x5_interact (1, 0);
      _5x5_interact (0, 0);
      _5x5_interact (0, 1);
      _5x5_interact (2, 2);
      break;

    case 42:
      _5x5_interact (2, 3);
      _5x5_interact (2, 4);
      _5x5_interact (1, 4);
      _5x5_interact (1, 3);
      _5x5_interact (3, 2);
      _5x5_interact (3, 1);
      _5x5_interact (4, 1);
      _5x5_interact (4, 2);
      _5x5_interact (4, 4);
      _5x5_interact (3, 3);
      _5x5_interact (2, 2);
      _5x5_interact (1, 1);
      _5x5_interact (1, 0);
      _5x5_interact (0, 0);
      _5x5_interact (0, 1);
      _5x5_interact (2, 0);
      _5x5_interact (1, 1);
      _5x5_interact (0, 2);
      _5x5_interact (1, 3);
      _5x5_interact (2, 4);
      _5x5_interact (3, 3);
      _5x5_interact (4, 2);
      _5x5_interact (4, 2);
      _5x5_interact (4, 2);
      _5x5_interact (3, 1);
      _5x5_interact (0, 0);
      _5x5_interact (0, 4);
      _5x5_interact (4, 4);
      _5x5_interact (4, 0);
      break;


/*
    case 1:
      _5x5_interact (2, 1);
      _5x5_interact (2, 2);
      _5x5_interact (2, 3);
      break;

    case 2:
      _5x5_interact (1, 0);
      _5x5_interact (3, 0);
      _5x5_interact (0, 1);
      _5x5_interact (1, 1);
      _5x5_interact (3, 1);
      _5x5_interact (4, 1);
      _5x5_interact (0, 3);
      _5x5_interact (1, 3);
      _5x5_interact (3, 3);
      _5x5_interact (4, 3);
      _5x5_interact (1, 4);
      _5x5_interact (3, 4);
      break;

    case 3:
      _5x5_interact (0, 0);
      _5x5_interact (2, 0);
      _5x5_interact (4, 0);
      _5x5_interact (1, 1);
      _5x5_interact (3, 1);
      _5x5_interact (0, 2);
      _5x5_interact (4, 2);
      _5x5_interact (1, 3);
      _5x5_interact (3, 3);
      _5x5_interact (0, 4);
      _5x5_interact (2, 4);
      _5x5_interact (4, 4);
      break;

    case 4:
      _5x5_interact (1, 0);
      _5x5_interact (2, 0);
      _5x5_interact (3, 0);
      _5x5_interact (4, 1);
      _5x5_interact (4, 2);
      _5x5_interact (4, 3);
      _5x5_interact (3, 4);
      _5x5_interact (2, 4);
      _5x5_interact (1, 4);
      _5x5_interact (0, 3);
      _5x5_interact (0, 2);
      _5x5_interact (0, 1);
      break;

    case 5:
      _5x5_interact (2, 2);
      _5x5_interact (1, 1);
      _5x5_interact (3, 1);
      _5x5_interact (3, 3);
      _5x5_interact (1, 3);
      break;

    case 6:
      _5x5_interact (2, 2);
      _5x5_interact (0, 0);
      _5x5_interact (2, 0);
      _5x5_interact (4, 0);
      _5x5_interact (3, 1);
      _5x5_interact (1, 1);
      _5x5_interact (0, 2);
      _5x5_interact (2, 2);
      _5x5_interact (4, 2);
      _5x5_interact (3, 3);
      _5x5_interact (1, 3);
      _5x5_interact (0, 4);
      _5x5_interact (2, 4);
      _5x5_interact (4, 4);
      _5x5_interact (2, 1);
      _5x5_interact (2, 2);
      _5x5_interact (2, 3);
      break;

    case 7:
      _5x5_interact (1, 1);
      _5x5_interact (1, 0);
      _5x5_interact (0, 0);
      _5x5_interact (0, 1);
      _5x5_interact (2, 2);
      _5x5_interact (3, 3);
      _5x5_interact (4, 4);
      _5x5_interact (2, 4);
      _5x5_interact (2, 3);
      _5x5_interact (1, 3);
      _5x5_interact (1, 4);
      _5x5_interact (3, 2);
      _5x5_interact (3, 1);
      _5x5_interact (4, 1);
      _5x5_interact (4, 2);
      break;

    case 8:
      _5x5_interact (0, 4);
      _5x5_interact (1, 3);
      _5x5_interact (3, 1);
      _5x5_interact (4, 0);
      _5x5_interact (3, 3);
      _5x5_interact (1, 1);
      _5x5_interact (4, 2);
      _5x5_interact (0, 2);
      break;

    case 9:
      _5x5_interact (1, 0);
      _5x5_interact (0, 1);
      _5x5_interact (0, 3);
      _5x5_interact (1, 4);
      _5x5_interact (3, 4);
      _5x5_interact (4, 3);
      _5x5_interact (4, 1);
      _5x5_interact (3, 0);
      _5x5_interact (2, 3);
      _5x5_interact (3, 4);
      _5x5_interact (1, 4);
      _5x5_interact (2, 0);
      _5x5_interact (3, 1);
      _5x5_interact (1, 1);
      break;

    case 10:
      _5x5_interact (3, 0);
      _5x5_interact (4, 1);
      _5x5_interact (3, 1);
      _5x5_interact (0, 4);
      _5x5_interact (1, 1);
      _5x5_interact (1, 0);
      _5x5_interact (3, 3);
      _5x5_interact (4, 3);
      _5x5_interact (2, 2);
      break;

    case 11:
      _5x5_interact (3, 0);
      _5x5_interact (3, 1);
      _5x5_interact (1, 3);
      _5x5_interact (1, 4);
      _5x5_interact (0, 0);
      _5x5_interact (4, 4);
      _5x5_interact (2, 2);
      break;

    case 12:
      _5x5_interact (1, 0);
      _5x5_interact (1, 1);
      _5x5_interact (0, 1);
      _5x5_interact (3, 0);
      _5x5_interact (3, 1);
      _5x5_interact (4, 1);
      _5x5_interact (4, 3);
      _5x5_interact (3, 3);
      _5x5_interact (3, 4);
      _5x5_interact (0, 3);
      _5x5_interact (1, 3);
      _5x5_interact (1, 4);
      _5x5_interact (1, 4);
      _5x5_interact (3, 4);
      _5x5_interact (2, 3);
      _5x5_interact (2, 3);
      _5x5_interact (0, 4);
      _5x5_interact (4, 4);
      _5x5_interact (2, 4);
      _5x5_interact (2, 3);
      _5x5_interact (2, 0);
      break;
      */
    }
}

int
levelcount ()
{
  return 43;
}
