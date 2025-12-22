#ifndef _GAME_H
#define _GAME_H

#include "maze.h"
#include "player.h"

#define ESC_KEY (27)
#define DISPLAY_AREA_WIDTH (20)
#define DISPLAY_AREA_HEIGHT (15)
#define STATUS_BAR_VERTICAL_OFFSET (DISPLAY_AREA_HEIGHT + 3)

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
void game_draw(Game *game);
void game_draw_fixed_size(Game *game);
void game_draw_distance(Game *game);
void game_display_status(Game *game);
void game_cleanup(Game *game);

typedef void (*game_draw_which)(Game *game);
extern game_draw_which game_drawer;

#endif
