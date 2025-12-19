#ifndef _MAIN_H
#define _MAIN_H

#include "game.h"

void run_game_once(void);
void setup_ncurses(void);
void cleanup_ncurses(Game *game);

#endif
