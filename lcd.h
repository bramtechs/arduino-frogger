#pragma once

#include <Wire.h>
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd(0x27,16,2);

void lcd_setup() {
  lcd.init();
  lcd.backlight();
}

void lcd_print(String bovenaan, String onderaan){
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print(bovenaan);
  lcd.setCursor(1,1);
  lcd.print(onderaan);
}
