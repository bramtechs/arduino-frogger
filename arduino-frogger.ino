#include "LedControl.h"

const int FPS = 10;
int huidigeFrame;
LedControl lc = LedControl(7, 6, 5, 1);

#include "grafisch.h"
#include "kikker.h"
#include "obstakel.h"

const int RESPAWN_TIJD = 30; //3 sec
int respawn_timer;

void setup()
{
  Serial.begin(9600);

  lc.shutdown(0, false);
  lc.setIntensity(0, 5);
  lc.clearDisplay(0);

  joy_setup();
  reset();
}

void reset()
{
  kikker_reset();
  respawn_timer = 0;
  Serial.println("nieuw level");
}

void loop()
{
  joy_print();

  lc.clearDisplay(0);

  if (levend)
  {
    kikker_update();
    autos_beweeg();
    //stammen_beweeg();

    // teken

    autos_teken();
    //stammen_teken();
    kikker_teken();
    Serial.println(huidigeFrame);
  }
  else if (respawn_timer < RESPAWN_TIJD)
  {
    // respawn wanneer dood
    respawn_timer++;
    teken_sterfte();
  }
  else
  {
    reset();
  }
  huidigeFrame++;
  delay(1000 / FPS);
}
