#include "main.h"
#include "raylib.h"
#include "frogger.h"

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    frogger_setup();

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(DARKGRAY);

        DrawFPS(10, 10);

        frogger_loop();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void teken_pixel(int x, int y, Color color) {
    DrawRectangle(x * CELL_SCALE, y * CELL_SCALE, CELL_SCALE, CELL_SCALE, color);
}