#include <LedControl.h>
#include "LiquidCrystal_I2C.h"

enum State{
  MENU,
  SPEL,
  DOOD,
  WIN
};
State state = SPEL;

const int FPS = 10;
int huidigeFrame;

const int RESPAWN_TIJD = 30; //3 sec
int respawn_timer;

const int GREEN = 0;
const int RED = 1;

// DATA IN-pin, CLK-pin, LOAD(/CS)-pin, aantal schermen
LedControl lc = LedControl(2, 3, 4, 1);
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

// ==== GRAFISCH ====
void teken_pixel(int x, int y)
{
  if (x >= 0 && x < 8)
  {
    if (y >= 0 && y < 8)
    {
      lc.setLed(0, x, y, true);
    }
  }
}

void teken_leegte(int x, int y)
{
  if (x >= 0 && x < 8)
  {
    if (y >= 0 && y < 8)
    {
      lc.setLed(0, x, y, false);
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

// ==== Joystick ====
const int DEAD_ZONE = 50;

int vorigKwadrant;
int cooldownFrames;

// joystick in een richting vasthouden: matige snelheid
// joystick keer op keer "aanduwen": extra snelheid
int joy_get_kwadrant()
{
  float x = map(analogRead(VRx), 0, 1023, -512, 512);
  float y = map(analogRead(VRy), 0, 1023, -512, 512);

  //vrkwrtl(x^2+y^2)
  int joy_hoek = (int)(atan2(x, y) * RAD_TO_DEG) - 45;
  int hoek = (360 + joy_hoek) % 360;

  int kwadrant = hoek / (360 / 4) + 1;

  return kwadrant;
}

bool joy_is_deadzone(){
    float x = map(analogRead(VRx), 0, 1023, -512, 512);
    float y = map(analogRead(VRy), 0, 1023, -512, 512);
  
    //vrkwrtl(x^2+y^2)
    float afstand = sqrt(x*x+y*y);
    return afstand < DEAD_ZONE;
}

void joy_print()
{
  int xPosition = analogRead(VRx);
  int yPosition = analogRead(VRy);
  int mapX = map(xPosition, 0, 1023, -90, 90);
  int mapY = map(yPosition, 0, 1023, -90, 90);
  int kwadrant = joy_get_kwadrant();
  Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
  if (joy_is_deadzone()){
    Serial.print(" DEADZONE ");
  }
  Serial.print(" | Richting: ");
  Serial.println(kwadrant);

  delay(100);
}

// === Kikker ===
const int COOLDOWN = 2; // maakt de kikker makkelijker te besturen
const bool TEST_MODE = true;

int levens = 99;
int timer;

bool levend;

int kikkerX;
int kikkerY;

void kikker_reset(){
  kikkerX = 4;
  kikkerY = 6;
  levend = true;
  timer = 0;
  lcd_print("Kikkers ",String(levens));
}

void kikker_beweeg(int x, int y)
{
  kikkerX = max(0, min(kikkerX + x, 7));
  kikkerY = max(0, min(kikkerY + y, 7));
}

void kikker_sterf(){
  lcd_print("DOOD",":(");
  Serial.println("dood");
  levens--;
  levend = false;
}

void kikker_update()
{
  int kwadrant = joy_get_kwadrant();

  // kijk voor aanrijding
  if (obstakel_raakt(kikkerX,kikkerY) && !TEST_MODE){
    kikker_sterf();
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

struct Obstakel{
  int x;
  int y;
  int lengte;
  int richting;
};
int marge = 2;

// === VOERTUIGEN === //
Obstakel autos[] = {
  
  // achterste rij
  
  {5,3,3,1},
  
  {1,3,2,1},
  
  // middelste rij
  
  {4,2,2,-1},

  // voorste rij
  
  {2,1,2,1},

  {7,1,2,1},
};
int aantal_autos = sizeof(autos)/sizeof(autos[0]);

// === BOOMSTAMMEN === //
Obstakel stammen[] = {
  
  // achterste rij
  
  {5,7,3,1},
  
  {1,7,2,1},
  
  // middelste rij
  
  {4,6,2,1},

  // voorste rij
  
  {2,5,2,1},

  {7,5,2,1},

};
int aantal_stammen = sizeof(stammen)/sizeof(stammen[0]);

bool obstakel_raakt(int x, int y){
  // kijk voor aanrijding
  for (int i = 0; i < aantal_autos; i++)
  {
    int yy = autos[i].y;
    for (int j = 0; j < autos[i].lengte; j++) // rekening houden met lengte auto
    {
        int xx = autos[i].x+j;
        if (x == xx && y == yy){
          return true;
        }
    }
  }
  return false;
}

void stammen_update(){
  if (huidigeFrame % 10 == 0)
  {
    for (int i = 0; i < aantal_stammen; i++){
      int x = stammen[i].x;
      x += stammen[i].richting;

      if (x > 7+marge){
        x = -marge;
      }else if (x < -marge){
        x = 7+marge;
      }
      stammen[i].x = x;
    }
  }
}

void autos_update(){
  if (huidigeFrame % 4 == 0)
  {
    for (int i = 0; i < aantal_autos; i++){
      int x = autos[i].x;
      x += autos[i].richting;

      if (x > 7+marge){
        x = -marge;
      }else if (x < -marge){
        x = 7+marge;
      }
      autos[i].x = x;
    }
  }
  
  // teken de voertuigen
  for (int i = 0; i < aantal_autos; i++){
    // is het voertuig-onderdeel binnen het speelveld?
    for (int j = 0; j < autos[i].lengte; j++){
      int x = autos[i].x+j;
      if (x <= 7 and x >= 0){
        // voertuig in beeld tekenen
        teken_pixel(x,i);
      }
    }
  }
}

// ==== LCD ====
void lcd_print(String bovenaan, String onderaan){
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print(bovenaan);
  lcd.setCursor(1,1);
  lcd.print(onderaan);
}

String lcd_tijd(){
  int seconde = huidigeFrame/FPS % 60;
  int minuut = huidigeFrame/FPS / 60;
  String tijd = "";
  if (minuut < 10){
    tijd += "0";
  }
  tijd += String(minuut) + ":";

  if (seconde < 10){
    tijd += "0";
  }
  tijd+= String(seconde);
  return tijd;
}

void lcd_print_status(){
  if (huidigeFrame % FPS ==0){
    lcd_print("Kikkers " + String(levens),lcd_tijd());
  }
}

// === MAIN ===
void setup()
{
  Serial.begin(9600);

  // led setup
  lc.shutdown(0,false); 
  lc.setIntensity(0, 15);
  
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
  lc.clearDisplay(0);

  switch (state){
    case SPEL:
      kikker_update();
      autos_update();
      lcd_print_status();
      break;
    case DOOD:
      // respawn wanneer dood
      respawn_timer++;
      teken_sterfte();
      if (respawn_timer > RESPAWN_TIJD){
        state = SPEL;
        kikker_reset();
        respawn_timer = 0;
      }
      break;
  }
  huidigeFrame++;
  delay(1000 / FPS);
}
