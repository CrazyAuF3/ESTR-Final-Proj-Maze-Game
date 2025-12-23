#include "maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "util.h"

char *template_maze_arr_1[15] = {
    "###############",
    "#             #",
    "# ########### #",
    "#     #     # #",
    "######## #### #",
    "#      # #    #",
    "#  #   # #  # #",
    "## ##### ## ###",
    "#  #      #   #",
    "#  # ###### # #",
    "#         # # #",
    "#### ###    # #",
    "#  # #    #####",
    "#      #     x#",
    "###############",
};

char *template_maze_arr_2[30] = {
    "##############################",
    "#                            #",
    "#   ###############          #",
    "#       #                    #",
    "#       #                    #",
    "#       #                    #",
    "#       #                    #",
    "#       #                    #",
    "#       #                    #",
    "#       ##############       #",
    "#            #               #",
    "#            #               #",
    "#            #################",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                           x#",
    "##############################",
};

static void maze_draw_cell(int s, int y, int x);
static void maze_draw_teleporter(Maze *maze);

Maze *maze_create(int width, int height)
{
    Maze *maze = (Maze*)malloc(sizeof(Maze));
    maze->width = width;
    maze->height = height;

    maze->grid = (char**)malloc(height * sizeof(char*));
    for (int i = 0; i < height; i++) {
        maze->grid[i] = (char*)malloc(width * sizeof(char));
    }

    maze->teleporter_count = 0;
    maze->teleporter_location = NULL;

    return maze;
}

void maze_destroy(Maze *maze) {
    if (maze->teleporter_location) free(maze->teleporter_location);

    for (int i = 0; i < maze->height; i++) {
        free(maze->grid[i]);
    }
    free(maze->grid);
    
    free(maze);
}

// TODO: implement maze_load_from_file

// TODO: implement maze_generate_random

void maze_draw(const Maze *maze)
{
    for (int y = 0; y < maze->height; y++) {
        for (int x = 0; x < maze->width; x++) {
            maze_draw_cell(maze->grid[y][x], y, x);
        }
    }
}

void maze_draw_distance(const Maze *maze, V2d player_pos, int d)
{
    for (int y = 0; y < maze->height; y++) {
        for (int x = 0; x < maze->width; x++) {
            if (USE_MANHATTAN) {
                V2d curr = {.x = x, .y = y};
                if (V2d_manhattan_distance(curr, player_pos) > d) {
                    continue;
                }
            } else {
                if (x > player_pos.x + 5 || x < player_pos.x - 5 || y > player_pos.y + 5 || y < player_pos.y - 5) {
                    continue;
                }
            }
            maze_draw_cell(maze->grid[y][x], y, x);
        }
    }
}

void maze_draw_fixed_size(const Maze *maze, V2d _from, const int _width, const int _height)
{
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            char display_char;

            // check if the display char is valid
            if (y+_from.y >= maze->height || y+_from.y < 0 ||
                x+_from.x >= maze->width || x+_from.x < 0) {
                display_char = VOID_CHAR;
            } else {
                display_char = maze->grid[y+_from.y][x+_from.x];
            }

            maze_draw_cell(display_char, y, x);
        }
    }
}

int maze_is_valid_move(Maze *maze, V2d pos)
{
    return (
        pos.x >= 0 && pos.x < maze->width &&
        pos.y >= 0 && pos.y < maze->height &&
        maze->grid[pos.y][pos.x] != WALL
    );
}

int maze_is_exit(Maze *maze, V2d pos)
{
    return (
        pos.x >= 0 && pos.x < maze->width &&
        pos.y >= 0 && pos.y < maze->height &&
        pos.x == maze->exit_location.x &&
        pos.y == maze->exit_location.y
    );
}

int maze_is_teleporter(Maze *maze, V2d pos)
{
    for (int i = 0; i < maze->teleporter_count; i++) {
        V2d t_pos = maze->teleporter_location[i];
        V2d diff = V2d_sub(t_pos, pos);
        if (diff.x == 0 && diff.y == 0) {
            return 1;
        }
    }
    return 0;
}

V2d maze_get_random_teleporter_pos(Maze *maze)
{
    return (maze->teleporter_location[rand() % maze->teleporter_count]);
}

void maze_place_teleporters(Maze *maze, const int count, double density)
{
    if (maze == NULL || count <= 0 || density <= 0.0) {
        return;
    }

    if (maze->teleporter_location) {
        free(maze->teleporter_location);
    }

    maze->teleporter_location = (V2d*)malloc(count * sizeof(V2d));
    maze->teleporter_count = 0;

    while (maze->teleporter_count < count) {
        for (int y = 0; y < maze->height; y++) {
            for (int x = 0; x < maze->width; x++) {
                if (maze->teleporter_count >= count) {
                        return;
                }

                if (maze->grid[y][x] == PATH) {
                    if ((double)rand() / RAND_MAX > density) {
                        continue;
                    }

                    V2d new_pos = {.x = x, .y = y};
                    maze->grid[y][x] = TELEPORT;
                    maze->teleporter_location[maze->teleporter_count] = new_pos;
                    maze->teleporter_count++;
                }
            }
        }
    }
}

static void maze_draw_cell(int s, int y, int x)
{
    switch (s) {
        case WALL:
        mvaddch(D_POS(y), D_POS(x), WALL);
        break;

        case VOID_CHAR:
        mvaddch(D_POS(y), D_POS(x), VOID_CHAR);
        break;

        case TELEPORT:
        mvaddch(D_POS(y), D_POS(x), TELEPORT);
        break;

        case EXIT:
        mvaddch(D_POS(y), D_POS(x), EXIT);
        break;

        default:
        mvaddch(D_POS(y), D_POS(x), PATH);
    }
}

static void maze_draw_teleporter(Maze *maze)
{
    for (int i = 0; i < maze->teleporter_count; i++) {
        V2d t_pos = maze->teleporter_location[i];
        mvaddch(D_POS(t_pos.y), D_POS(t_pos.x), TELEPORT);
    }
}
