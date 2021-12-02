#include "LedControl.h"
const int FPS = 10;
int huidigeFrame;
bool scherm[8][8];

#include "kikker.h"
#include "obstakel.h"

LedControl lc=LedControl(7,6,5,1);
// DIN, CLK and CS pins
// VCC voor stroom

void setup() {
  Serial.begin(9600);  
  
  lc.shutdown(0,false);
  lc.setIntensity(0,5);
  lc.clearDisplay(0);

  kikker_start();
}

void teken()
{  
  autos_teken();
  stammen_teken();
  kikker_teken();
  
  // matrix.clear();
  // overloop iedere pixel in de 2D scherm array
  // https://www.educba.com/2-d-arrays-in-c/
  lc.clearDisplay(0);
  for (int y = 0; y < 8; y++){
    for (int x = 0; x < 8; x++){
      lc.setLed(0,x,y,scherm[x][y]);
    }
  }
  // maak de 2d array weer leeg
  memset(scherm, 0, sizeof(scherm[0][0]) * 8 * 8);
}

void loop() {
  checkJoystick();
  autos_beweeg();
  stammen_beweeg();
  teken();

  //Serial.println(huidigeFrame);
  
  huidigeFrame++;
  delay(1000/FPS);
}
