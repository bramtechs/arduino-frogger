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

int kikker[] = {
  0b00000000,
  0b11100111,
  0b10100101,
  0b11011011,
  0b01000010,
  0b01100110,
  0b10100101,
  0b01100110
};

//https://codeforwin.org/2016/01/c-program-to-get-value-of-nth-bit-of-number.html
void teken_menu(){
  for (int y = 0; y < 8; y++){
    for (int x = 0; x < 8; x++){
        bool aan = (kikker[y] >> x) & 1 == 1;
        if (aan){
          teken_pixel(x,16-y);
        }
    }
  }     
}