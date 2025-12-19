#include "player.h"
#include <ncurses.h>
#include <stdlib.h>
#include "util.h"

Player *player_create(V2d start_pos)
{
    Player *player = (Player*)malloc(sizeof(Player));
    player->pos.x = start_pos.x;
    player->pos.y = start_pos.y;
    player->symbol = PLAYER;
    return player;
}

void player_move(Player *player, V2d d)
{
    player->pos = V2d_add(player->pos, d);
}

void player_draw(const Player *player)
{
    mvaddch(D_POS(player->pos.y), D_POS(player->pos.x), PLAYER);
}
