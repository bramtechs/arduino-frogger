#ifndef GRAFISCH_H
#define GRAFISCH_H

void teken_pixel(int x, int y)
{
  if (x >= 0 && x < 8)
  {
    if (y >= 0 && y < 8)
    {
      lc.setLed(0, x, y, true);
    }
  }
}

void teken_leegte(int x, int y)
{
  if (x >= 0 && x < 8)
  {
    if (y >= 0 && y < 8)
    {
      lc.setLed(0, x, y, false);
    }
  }
}

void teken_sterfte()
{
  // teken een X op het scherm
  if (huidigeFrame % 2 == 1)
  {
    for (int i = 0; i < 8; i++)
    {
      teken_pixel(i, i);
      teken_pixel(7 - i, i);
    }
  }
}

#endif
