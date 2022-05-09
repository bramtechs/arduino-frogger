#include <LedControl.h>
#include "./LiquidCrystal_I2C.h"

enum State{
  MENU_SETUP,
  MENU,
  SPEL_SETUP,
  SPEL,
  DOOD_SETUP,
  DOOD,
  WIN_SETUP,
  WIN
};
State state = MENU;

const int FPS = 10;
int huidigeFrame;

const int RESPAWN_TIJD = 30; //3 sec
int respawn_timer;

const int GREEN = 0;
const int RED = 1;

// DATA IN-pin, CLK-pin, LOAD(/CS)-pin, aantal schermen
LedControl lc = LedControl(2, 3, 4, 2);
LiquidCrystal_I2C lcd(0x27,16,2);

const int SW = 5;
const int VRx = A2; // joystick analoog X
const int VRy = A3; // joystick analoog Y

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
#include "joystick.h"
#include "kikker.h"
#include "lcd.h"
#include "obstakel.h"
#include "huisjes.h"

// === MAIN ===
void setup()
{
  Serial.begin(9600);

  // led setup
  lc.shutdown(0,false); 
  lc.setIntensity(0, 4);
  lc.shutdown(1,false); 
  lc.setIntensity(0, 4);
  
  // joystick setup
  pinMode(VRx, INPUT);       // VRx
  pinMode(VRy, INPUT);       // VRy
  pinMode(SW, INPUT_PULLUP); //SW

  //lcd setup
  lcd.init();
  lcd.backlight();
}

void loop()
{
  switch (state){
    case MENU_SETUP:
      lcd_print_menu();
      huisjes_reset();
      state = MENU;
    case MENU:
      teken_menu();
      if (!joy_is_deadzone()){ // menu verlaten door joystick te bewegen
        state = SPEL;
      }
      break;
    case SPEL_SETUP: // per ronde
      kikker_reset();
      state = SPEL;
    case SPEL:
      lc.clearDisplay(0);
      lc.clearDisplay(1);
      autos_update();
      stammen_update();
      huisjes_update();
      kikker_update();
      lcd_print_spel_status();
      break;
    case DOOD_SETUP:
      respawn_timer = RESPAWN_TIJD;
      state = DOOD;
    case DOOD:
      // respawn wanneer dood
      respawn_timer++;
      teken_sterfte();
      if (respawn_timer > 0){
        state = SPEL_SETUP;
        respawn_timer--;
      }
      break;
  }
  huidigeFrame++;
  delay(1000 / FPS);
}
