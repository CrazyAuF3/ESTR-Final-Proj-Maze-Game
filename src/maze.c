#include "maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "util.h"

char *template_maze_arr[15] = {
    "###############",
    "#             #",
    "#             #",
    "#             #",
    "#             #",
    "#             #",
    "#             #",
    "#             #",
    "#             #",
    "#             #",
    "#             #",
    "#             #",
    "#             #",
    "#             #",
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

// TODO: implement maze_generate_random

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
    printf("freed grids");
    free(maze->grid);
    printf("freed grid");
    free(maze);
    printf("freed win");
    */
}
