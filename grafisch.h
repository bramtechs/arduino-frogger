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

int letters[5][8] = {
  { // F
    0b00000000,
    0b00111100,
    0b00100000,
    0b00111100,
    0b00100000,
    0b00100000,
    0b00100000,
    0b00000000
  },
  { // R
    0b00000000,
    0b00111100,
    0b00100100,
    0b00101100,
    0b00110000,
    0b00101000,
    0b00100100,
    0b00000000
  },
  { // O
    0b00000000,
    0b00011000,
    0b00100100,
    0b00100100,
    0b00100100,
    0b00100100,
    0b00011000,
    0b00000000
  },
  { // G
    0b00000000,
    0b00111100,
    0b00100000,
    0b00100000,
    0b00101100,
    0b00100100,
    0b00111100,
    0b00000000
  },
  { // E
    0b00000000,
    0b00111100,
    0b00100000,
    0b00111100,
    0b00100000,
    0b00100000,
    0b00111100,
    0b00000000
  }
};

const int FRAMES_PER_LETTER = 5;

int huidige_letter(){
  return (huidigeFrame % 35) / FRAMES_PER_LETTER;
}

//https://codeforwin.org/2016/01/c-program-to-get-value-of-nth-bit-of-number.html
void teken_menu(){
  for (int y = 0; y < 8; y++){
    for (int x = 0; x < 8; x++){
        // teken kikker op bovenste scherm
        bool aan = (kikker[y] >> x) & 1 == 1;
        if (aan){
          teken_pixel(x,16-y);
        }

        if (huidigeFrame % FRAMES_PER_LETTER == 0){
          lc.clearDisplay(0); // scherm verversen iedere letter
        }

        // teken letter op onderste scherm
        int l = huidige_letter();
        aan = (letters[l][y] >> x) & 1 == 1;
        if (aan){
          teken_pixel(x,y);
        } 
    }
  }
}