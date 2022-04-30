#pragma once
// === Kikker ===
const int COOLDOWN = 2; // maakt de kikker makkelijker te besturen
const bool TEST_MODE = false;

int levens = 5;
int timer;

bool levend;

int kikkerX;
int kikkerY;

void kikker_reset(){
  kikkerX = 4;
  kikkerY = 0;
  levend = true;
  timer = 0;
}

void kikker_beweeg(int x, int y)
{
  kikkerX = max(0, min(kikkerX + x, 7));
  kikkerY = max(0, min(kikkerY + y, 15));
}

void kikker_sterf(){
  Serial.println("dood");
  levens--;
  levend = false;
  kikker_reset();
}

void kikker_update()
{
  int kwadrant = joy_get_kwadrant();

  if (joy_is_deadzone()){
    timer = 0;
  }
  else if (timer <= 0)
  {
    switch (kwadrant)
    {
    case 3:
      kikker_beweeg(0, -1);
      timer = COOLDOWN;
      break;
    case 1:
      kikker_beweeg(0, 1);
      timer = COOLDOWN;
      break;
    case 2:
      kikker_beweeg(-1, 0);
      timer = COOLDOWN;
      break;
    case 4:
      kikker_beweeg(1, 0);
      timer = COOLDOWN;
      break;
    default:
      // beweeg niet
      break;
    }
  }
  timer--;

  // teken de kikker!
  if (huidigeFrame % 2 == 1)
  {
    teken_pixel(kikkerX, kikkerY);
  }
}
