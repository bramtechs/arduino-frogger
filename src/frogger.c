#include "frogger.h"
#include "kikker.h"
#include "lcd.h"

State state = SPEL;
int huidige_frame = 0;
int respawn_timer = 0;

void kikker_gestorven() {
    //lcd_print("DOOD", ":(");
    kikker_sterf();
}

// === MAIN ===
void frogger_setup() {
    kikker_reset();
}

void frogger_loop() {
    switch (state) {
        case MENU:
            lcd_print_menu();
            //teken_menu();
            break;
        case SPEL:
            //lc.clearDisplay(0);
            //lc.clearDisplay(1);
            //autos_update();
            //stammen_update();
            //huisjes_update();
            kikker_update();
            lcd_print_spel_status();
            break;
        case DOOD:
            // respawn wanneer dood
            respawn_timer++;
            //teken_sterfte();
            if (respawn_timer > RESPAWN_TIJD) {
                state = SPEL;
                respawn_timer = 0;
            }
            break;
        default:
            break;
    }
    huidige_frame++;
}
