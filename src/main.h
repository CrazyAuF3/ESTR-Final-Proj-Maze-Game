#ifndef _MAIN_H
#define _MAIN_H

#include "game.h"

#define ENABLE_NAP (1)

void run_game_once(void);
void setup_ncurses(void);
void cleanup_ncurses(Game *game);
void try_resize_terminal(int r, int c);

#endif
