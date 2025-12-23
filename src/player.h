#ifndef _PLAYER_H
#define _PLAYER_H

#include "util.h"

#define PLAYER 'o'

typedef struct {
    char symbol;
    V2d pos;
    int energy;
} Player;

Player *player_create(V2d start_location, int start_energy);
void player_move(Player *player, V2d d, int consume_energy);
void player_draw(const Player *player);
void player_draw_fixed_size(const Player *player, V2d pos);
int player_has_energy(const Player *player);

#endif
