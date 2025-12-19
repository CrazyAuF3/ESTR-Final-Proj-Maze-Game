#include "maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "util.h"

char *template_maze_arr[15] = {
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

Maze *maze_create(int width, int height)
{
    Maze *maze = (Maze*)malloc(sizeof(Maze));
    maze->width = width;
    maze->height = height;

    maze->grid = (char**)malloc(height * sizeof(char*));
    for (int i = 0; i < height; i++) {
        maze->grid[i] = (char*)malloc(width * sizeof(char));
    }

    return maze;
}

// TODO: implement maze_load_from_file

void maze_generate_random(Maze *maze, double density)
{
    srand(time(NULL));
    
    for (int i = 0; i < maze->height; i++) {
        for (int j = 0; j < maze->width; j++) {
            if (i == 0 || i == maze->height-1 || j == 0 || j == maze->width-1) {
                maze->grid[i][j] = WALL;
            } else {
                maze->grid[i][j] = ((double)rand() / RAND_MAX) < density ? WALL : PATH;
            }
        }
    }
    
    // ensure start (1,1) and exit are clear
    maze->grid[1][1] = PATH;
    maze->exit_location.x = maze->width - 2;
    maze->exit_location.y = maze->height - 2;
    maze->grid[maze->exit_location.y][maze->exit_location.x] = EXIT;
}

void maze_draw(const Maze *maze)
{
    for (int y = 0; y < maze->height; y++) {
        for (int x = 0; x < maze->width; x++) {
            switch (maze->grid[y][x]) {
                case WALL:
                mvaddch(D_POS(y), D_POS(x), WALL);
                break;

                default:
                mvaddch(D_POS(y), D_POS(x), PATH);
            }
        }
    }

    mvaddch(D_POS(maze->exit_location.x), D_POS(maze->exit_location.y), EXIT);
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

            switch (display_char) {
                case WALL:
                mvaddch(D_POS(y), D_POS(x), WALL);
                break;

                case VOID_CHAR:
                mvaddch(D_POS(y), D_POS(x), VOID_CHAR);
                break;

                case EXIT:
                mvaddch(D_POS(y), D_POS(x), EXIT);
                break;

                default:
                mvaddch(D_POS(y), D_POS(x), PATH);
            }
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

void maze_destroy(Maze *maze) {
    /*
    for (int i = 0; i < maze->height; i++) {
        free(maze->grid[i]);
    }
    
    free(maze->grid);
    
    free(maze);
    */
}
