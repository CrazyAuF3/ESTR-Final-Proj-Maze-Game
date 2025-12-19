#ifndef _PLAYER_H
#define _PLAYER_H

#include "util.h"

#define PLAYER 'o'

typedef struct {
    char symbol;
    V2d pos;
} Player;

Player *player_create(V2d start_location);
void player_move(Player *player, V2d d);
void player_draw(const Player *player);

#endif
