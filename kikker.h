#ifndef KIKKER_H
#define KIKKER_H

#include "joystick.h"
#include "obstakel.h"

const int cooldown = 2; // maakt de kikker makkelijker te besturen

int levens = 5;

int timer;
bool levend;
int kikkerX;
int kikkerY;

void kikker_reset(){
  kikkerX = 4;
  kikkerY = 6;
  levend = true;
  timer = 0;
  lcd_print("Aantal kikkers ",String(levens));
}

void kikker_beweeg(int x, int y)
{
  kikkerX = max(0, min(kikkerX + x, 7));
  kikkerY = max(0, min(kikkerY + y, 7));
}

void kikker_sterf(){
  lcd_print("DOOD",":(");
  levens--;
  levend = false;
}

void kikker_update()
{
  int kwadrant = joy_get_kwadrant();

  // kijk voor aanrijding
  if (obstakel_raakt(kikkerX,kikkerY)){
    kikker_sterf();
    return;
  }

  if (joy_is_deadzone()){
    timer = 0;
  }
  else if (timer <= 0)
  {
    switch (kwadrant)
    {
    case 3:
      kikker_beweeg(0, -1);
      timer = cooldown;
      break;
    case 1:
      kikker_beweeg(0, 1);
      timer = cooldown;
      break;
    case 2:
      kikker_beweeg(-1, 0);
      timer = cooldown;
      break;
    case 4:
      kikker_beweeg(1, 0);
      timer = cooldown;
      break;
    default:
      // beweeg niet
      break;
    }
  }
  timer--;
}

void kikker_teken()
{
  // teken de kikker!
  if (huidigeFrame % 2 == 1)
  {
    teken_pixel(kikkerX, kikkerY,GREEN);
  }
}
#endif
