#include "kikker.h"
#include "stdbool.h"
#include "utils.h"
#include "frogger.h"
#include "main.h"

int levens = 5;
bool levend = false;
int kikkerX = 0;
int kikkerY = 0;

void kikker_reset(void){
    kikkerX = 4;
    kikkerY = 0;
    levend = true;
}

void kikker_beweeg(int x, int y)
{
    kikkerX = max(0, min(kikkerX + x, 7));
    kikkerY = max(0, min(kikkerY + y, 15));
}

void kikker_sterf() {
    TraceLog(LOG_INFO, "dood");
    levens--;
    levend = false;
    kikker_reset();
}

void kikker_update() {
    if (IsKeyDown(KEY_UP)){
        kikker_beweeg(0, -1);
    }
    if (IsKeyDown(KEY_DOWN)){
        kikker_beweeg(0, 1);
    }
    if (IsKeyDown(KEY_LEFT)){
        kikker_beweeg(-1, 0);
    }
    if (IsKeyDown(KEY_RIGHT)){
        kikker_beweeg(1, 0);
    }

    // teken de kikker!
    if (huidige_frame % 2 == 1) {
        teken_pixel(kikkerX, kikkerY,GREEN);
    }
}
