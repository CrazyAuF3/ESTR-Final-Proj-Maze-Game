#ifndef _MAIN_H
#define _MAIN_H

#include "game.h"

void setup_ncurses(void);
void cleanup_ncurses_game(Game *game);
void cleanup_ncurses_menu();

#endif
