#pragma once

#include "stdbool.h"
#include "raylib.h"

#define COOLDOWN (2) // maakt de kikker makkelijker te besturen
#define TEST_MODE (false)

extern int levens;
extern bool levend;

extern int kikkerX;
extern int kikkerY;

void kikker_reset();
void kikker_sterf();
void kikker_beweeg();

void kikker_update();