#include "game.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"
#include "player.h"
#include "util.h"
#include "ui.h"

Game *game_init()
{
    /* Load from a template maze */

    int width = 30;
    int height = 22;

    Game *game = (Game*)malloc(sizeof(Game));
    game->maze = maze_create(width, height);

    /* load from the string literal array */
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            game->maze->grid[y][x] = template_maze_arr_2[y][x];
        }
    }

    game->maze->exit_location = (V2d){.x = width - 2, .y = height - 2};

    if (enabled_teleporters) {
        maze_add_component(game->maze, MAZE_COMPONENT_TYPE_TELEPORTER, 5);
        maze_place_teleporters(game->maze, 5, 0.02);
    }

    V2d start_pos = V2D_UNIT_VECTOR();

    game->player = player_create(start_pos, 200);
    game->state = GAME_RUN;

    return game;
}

void game_handle_input(Game *game, int ch)
{
    V2d diff = V2D_ZERO_VECTOR();

    if (game->state == GAME_RUN) {
        switch (ch)
        {
            case 'W': case 'w': diff.y = -1; break;
            case 'S': case 's': diff.y = 1; break;
            case 'A': case 'a': diff.x = -1; break;
            case 'D': case 'd': diff.x = 1; break;
        }

        V2d new_pos = V2d_add(game->player->pos, diff);

        if (maze_is_valid_move(game->maze, new_pos)) {
            if (enabled_energy) {
                player_move(game->player, diff, 1);
            } else {
                player_move(game->player, diff, 0);
            }

            if (!player_has_energy(game->player)) {
                game->state = GAME_LOSE;
            } else if (maze_is_exit(game->maze, new_pos)) {
                game->state = GAME_WON;
            } else if (maze_is_component(game->maze, new_pos, MAZE_COMPONENT_TYPE_TELEPORTER)) {
                diff = V2d_sub(maze_get_random_teleporter_pos(game->maze), new_pos);
                new_pos = V2d_add(new_pos, diff);
                player_move(game->player, diff, 1);
            }
        }
    }

    if (ch == 'q' || ch == 'Q' || ch == ESC_KEY) {
        game->state = GAME_QUIT;
        return;
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
    char status_clear[STATUS_BAR_BUFFER];
    memset(status_clear, ' ', STATUS_BAR_BUFFER - 1);
    status_clear[STATUS_BAR_BUFFER - 1] = '\0';

    int vertical_offset;

    if (enabled_fixed_size == 1) {
        vertical_offset = STATUS_BAR_VERTICAL_OFFSET;
    } else {
        vertical_offset = STATUS_BAR_VERTICAL_OFFSET_NF(game->maze->height);
    }

    mvprintw(vertical_offset, HORIZONTAL_DISPLAY_OFFSET, status_clear);

    switch (game->state) {
        case GAME_RUN:
        if (enabled_energy) {
            mvprintw(vertical_offset, HORIZONTAL_DISPLAY_OFFSET, "Current energy: %d", game->player->energy);
        }
        break;

        case GAME_WON:
        mvprintw(vertical_offset, HORIZONTAL_DISPLAY_OFFSET, "Congratulations! You won! Press ESC to return...");
        break;

        case GAME_LOSE:
        mvprintw(vertical_offset, HORIZONTAL_DISPLAY_OFFSET, "Oh no! You consumed all energy and lost! Press ESC to return...");
    }
}

void game_cleanup(Game *game)
{
    maze_destroy(game->maze);
    free(game->player);
    free(game);
}
