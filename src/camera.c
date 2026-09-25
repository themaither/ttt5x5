static int world_offset_x = 0;
static int world_offset_y = 0;

int
x (int value)
{
  return value + world_offset_x;
}

int
y (int value)
{
  return value + world_offset_y;
}

void
setcamx (int value)
{
  world_offset_x = value;
}

void
setcamy (int value)
{
  world_offset_y = value;
}

void
centercamx (int value)
{
  setcamx ((640 - value) / 2);
}

void
centercamy (int value)
{
  setcamy ((400 - value) / 2);
}
