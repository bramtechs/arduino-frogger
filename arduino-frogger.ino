const int FPS = 10;
int huidigeFrame;

/*
/// PIN LAYOUT ///
DATA IN-pin, CLK-pin, LOAD(/CS)-pin : BI-color scherm
   2              3         4

SCL  SDA: LCD-tekst
 A5   A4

VRx  VRy  SW
 A2   A3   5

*/
#include "grafisch.h"
#include "lcd.h"
#include "kikker.h"
#include "obstakel.h"

const int RESPAWN_TIJD = 30; //3 sec
int respawn_timer;

void setup()
{
  Serial.begin(9600);
  
  led_setup();
  joy_setup();
  lcd_setup();
  lcd_print("Welkom!","");
  
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
