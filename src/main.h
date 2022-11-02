#pragma once

#include "raylib.h"

#define CELLS_X (8)
#define CELLS_Y (16)
#define CELL_SCALE (32)

#define SCREEN_WIDTH (CELLS_X*CELL_SCALE)
#define SCREEN_HEIGHT (CELLS_Y*CELL_SCALE)

#define WINDOW_TITLE "Window title"

int main(void);

void teken_pixel(int x, int y, Color color);
