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
    game->maze = maze_create(30, 30);

    /* Load from a template maze */
    /**/
    game->maze->grid = template_maze_arr_2;
    game->maze->width = 30;
    game->maze->height = 22;
    game->maze->exit_location.x = 28;
    game->maze->exit_location.y = 20;
    /**/
    
    // maze_generate_random(game->maze, 0.5);

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

    if (ch == 'q' || ch == 'Q' || ch == ESC_KEY) {
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
    game_display_status(game);

    refresh();
}

void game_draw_fixed_size(Game *game)
{
    clear();

    V2d _display_pos = {.x = DISPLAY_AREA_WIDTH / 2, .y = DISPLAY_AREA_HEIGHT / 2};
    V2d _from = V2d_sub(game->player->pos, _display_pos);
    maze_draw_fixed_size(game->maze, _from, DISPLAY_AREA_WIDTH, DISPLAY_AREA_HEIGHT);
    player_draw_fixed_size(game->player, _display_pos);
    game_display_status(game);

    refresh();
}

void game_draw_distance(Game *game)
{
    clear();

    maze_draw_distance(game->maze, game->player->pos, 10);
    player_draw(game->player);
    game_display_status(game);

    refresh();
}

void game_display_status(Game *game)
{
    switch (game->state) {
        case GAME_WON:
        mvprintw(STATUS_BAR_VERTICAL_OFFSET, HORIZONTAL_DISPLAY_OFFSET, "Congratulations! You won! Press ESC to return...");
        break;

        default: 
        // mvprintw(STATUS_BAR_VERTICAL_OFFSET, HORIZONTAL_DISPLAY_OFFSET, "Running...");
    }
}

void game_cleanup(Game *game)
{
    maze_destroy(game->maze);
    free(game->player);
    free(game);
}
