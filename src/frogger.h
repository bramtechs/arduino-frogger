#pragma once

#define FPS (10)

#define RESPAWN_TIJD (30)

typedef enum {
    MENU,
    SPEL,
    DOOD,
    WIN
} State;

extern int respawn_timer;
extern int huidige_frame;
extern State state;

void frogger_setup(void);
void frogger_loop(void);

