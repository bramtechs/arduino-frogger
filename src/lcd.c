#include "lcd.h"
#include "frogger.h"
#include "raylib.h"
#include "kikker.h"

// ==== LCD ====
void lcd_print(const char *bovenaan, const char *onderaan) {
    DrawText(bovenaan, 10, 50, 12, YELLOW);
    DrawText(onderaan, 10, 64, 12, YELLOW);
}

void lcd_print_spel_status(void) {
    // lcd tijd
    int seconde = huidige_frame / FPS % 60;
    int minuut = huidige_frame / FPS / 60;
    const char *tijd = TextFormat("%02d:%02d", minuut, seconde);
    const char *bovenaan = TextFormat("Kikkers %d", levens);
    lcd_print(bovenaan, tijd);
}

void lcd_print_menu(void) {
    lcd_print("Welkom bij", "Arduino Frogger!");
}

