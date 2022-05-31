#include <LedControl.h>
#include "./LiquidCrystal_I2C.h"

enum State{
  MENU_SETUP,
  MENU,
  SPEL_SETUP,
  SPEL,
  DOOD,
  WIN
};
State state = MENU;

const int FPS = 10;
int huidigeFrame;

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
  lc.setIntensity(0, 7);
  lc.shutdown(1,false); 
  lc.setIntensity(1, 7);
  
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
      huisjes_reset();
      lc.clearDisplay(0);
      levens = 3;
      state = MENU;
    case MENU:
      lcd_print_menu();
      teken_menu();
      if (!joy_is_deadzone()){ // menu verlaten door joystick te bewegen
        huidigeFrame = 0;
        state = SPEL;
      }
      break;
    case SPEL_SETUP: // per ronde
      kikker_reset();
      delay(500);
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
    case DOOD:
      // respawn wanneer dood
      teken_sterfte();
      if (levens > 0){
        state = SPEL_SETUP;
      }else{
        state = MENU_SETUP; //verloren!
      }
      break;
    case WIN:
      lcd_print_gewonnen();
      teken_gewonnen();
      state = MENU_SETUP; //gewonnen!
      break;
  }
  huidigeFrame++;
  delay(1000 / FPS);
}
