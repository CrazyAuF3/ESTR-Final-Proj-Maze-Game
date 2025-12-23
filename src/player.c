#include "player.h"
#include <ncurses.h>
#include <stdlib.h>
#include "util.h"

Player *player_create(V2d start_pos, int start_energy)
{
    Player *player = (Player*)malloc(sizeof(Player));
    player->pos.x = start_pos.x;
    player->pos.y = start_pos.y;
    player->symbol = PLAYER;
    player->energy = start_energy;
    return player;
}

void player_move(Player *player, V2d d, int consume_energy)
{
    player->pos = V2d_add(player->pos, d);
    if (player->energy - consume_energy >= 0) {
        player->energy -= consume_energy;
    } else {
        player->energy = 0;
    }
}

void player_draw(const Player *player)
{
    mvaddch(D_POS(player->pos.y), D_POS(player->pos.x), player->symbol);
}

void player_draw_fixed_size(const Player *player, V2d _pos)
{
    mvaddch(D_POS(_pos.y), D_POS(_pos.x), player->symbol);
}

int player_has_energy(const Player *player)
{
    return player->energy > 0;
}
