#pragma once
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

void lcd_print_spel_status(){
  if (huidigeFrame % FPS == 0){
    lcd_print("Kikkers " + String(levens),lcd_tijd());
  }
}

void lcd_print_gewonnen(){
  lcd_print("Gewonnen!",lcd_tijd());
}

void lcd_print_menu(){
    lcd_print("Welkom bij","Arduino Frogger!");
}