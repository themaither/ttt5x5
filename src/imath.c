int
min (int lhs, int rhs)
{
  return lhs < rhs ? lhs : rhs;
}

int
max (int lhs, int rhs)
{
  return lhs > rhs ? lhs : rhs;
}

int
clamp (int x, int low, int high)
{
  return min (max (x, low), high);
}
