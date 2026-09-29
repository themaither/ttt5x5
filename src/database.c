#include <5x5.h>

void
loadlevel (int id)
{
  _5x5_clear ();

  switch (id)
    {
    case 0:
      break;

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
    }
}

int
levelcount ()
{
  return 13;
}
