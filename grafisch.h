#pragma once
// ==== GRAFISCH ====
void teken_pixel(int x, int y)
{
  if (x >= 0 && x < 8)
  {
    if (y >= 0 && y < 8)
    {
      lc.setLed(0, 7-y, x, true);
    }else if (y < 16){
      lc.setLed(1, y-8, 7-x, true);
    }
  }
}

void teken_leegte(int x, int y)
{
  if (x >= 0 && x < 8)
  {
    if (y >= 0 && y < 8)
    {
      lc.setLed(0, y, x, false);
    }else if (y < 16){
      lc.setLed(1, y-8, x, false);
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