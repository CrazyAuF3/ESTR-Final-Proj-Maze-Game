#ifndef _MAZE_H
#define _MAZE_H

#include "util.h"

#define WALL '#'
#define PATH ' '
#define EXIT 'x'
// TODO: spike, key, portal, ...

// TODO: color constants

extern char *template_maze_arr[15];

typedef struct {
    char **grid;
    int width;
    int height;
    V2d exit_location;
} Maze;

Maze *maze_create(int width, int height);
void maze_load_from_file(Maze *maze, const char *filename);  // not implemented
void maze_generate_random(Maze *maze);  // not implemented
void maze_draw(const Maze *maze);
void maze_destroy(Maze *maze);
int maze_is_valid_move(Maze *maze, V2d pos);
int maze_is_exit(Maze *maze, V2d pos);

#endif
