#ifndef _GAME_H
#define _GAME_H

#include "maze.h"
#include "player.h"

typedef enum {
    GAME_QUIT,
    GAME_RUN,
    GAME_WON,
} GameState;

typedef struct {
    Maze *maze;
    Player *player;
    GameState state;
} Game;

Game *game_init();
void game_handle_input(Game *game, int ch);
void game_update(Game *game);  // not implemented
void game_draw(Game *game);
void game_cleanup(Game *game);

#endif
