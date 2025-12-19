#include "game.h"
#include <ncurses.h>
#include <stdlib.h>
// #include <string.h>
#include "maze.h"
#include "player.h"
#include "util.h"

Game *game_init()
{
    Game *game = (Game*)malloc(sizeof(Game));
    game->maze = maze_create(15, 15);

    /* Load from a template maze */
    game->maze->grid = template_maze_arr;
    game->maze->width = 15;
    game->maze->height = 15;
    game->maze->exit_location.x = 11;
    game->maze->exit_location.y = 11;

    V2d start_pos = {.x = 1, .y = 1};

    game->player = player_create(start_pos);
    game->state = GAME_RUN;

    return game;
}

void game_handle_input(Game *game, int ch)
{
    V2d diff = {0};

    if (game->state == GAME_RUN) {
        switch (ch)
        {
            case 'W': case 'w': diff.y = -1; break;
            case 'S': case 's': diff.y = 1; break;
            case 'A': case 'a': diff.x = -1; break;
            case 'D': case 'd': diff.x = 1; break;
        }
    }

    if (ch == 'q' || ch == 'Q') {
        game->state = GAME_QUIT;
        return;
    }

    V2d new_pos = V2d_add(game->player->pos, diff);

    if (maze_is_valid_move(game->maze, new_pos)) {
        player_move(game->player, diff);
        if (maze_is_exit(game->maze, new_pos)) {
            game->state = GAME_WON;
        }
    }
}

void game_draw(Game *game)
{
    clear();

    maze_draw(game->maze);

    player_draw(game->player);

    switch (game->state) {
        case GAME_WON:
        mvprintw(18, 2, "You won!");
        break;
        default: mvprintw(18, 2, "Running...");
    }

    refresh();
}

void game_cleanup(Game *game)
{
    maze_destroy(game->maze);
    free(game->player);
    free(game);
}
