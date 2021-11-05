#include "joystick.h"
struct Kikker{
  int x;
  int y;
};

// maak een kikker aan
Kikker kikker = {4,0};

void kikker_start(){
  // start de joystick op
  joy_setup();
}

void kikker_beweeg(int x, int y)
{
  kikker.x = max(0,min(kikker.x + x,7));
  kikker.y = max(0,min(kikker.y + y,7));
  
  //Serial.println("=========");
  //Serial.println(kikker.x);
  //Serial.println(kikker.y);
}

void kikker_teken(){
  // teken de kikker!
  if (huidigeFrame % 2 == 1){
    scherm[kikker.x][kikker.y] = true;
  }
}

void checkJoystick(){
  //joy_print();
  switch (joy_get_richting())
  {
    case 3:
      kikker_beweeg(0,-1);
      break;
    case 1:
      kikker_beweeg(0,1);
      break;
    case 2:
      kikker_beweeg(-1,0);
      break;
    case 4:
      kikker_beweeg(1,0);
      break;
    default:
      // beweeg niet
      break;
  }
}
