#ifndef _MAZE_H
#define _MAZE_H

#include "util.h"

#define WALL '#'
#define PATH ' '
#define EXIT 'x'
#define VOID_CHAR 'V'
#define TELEPORT '*'
// TODO: spike, key, portal, ...

#define USE_MANHATTAN (0)

// TODO: color constants

extern char *template_maze_arr_1[15];
extern char *template_maze_arr_2[30];

typedef enum {
    MAZE_COMPONENT_TYPE_TELEPORTER,
} MazeComponentType;

typedef struct {
    MazeComponentType component_type;
    int count;
    V2d *location;
} MazeComponent;

typedef struct {
    char **grid;
    int width;
    int height;
    V2d exit_location;  // HAVE TO MAKE SURE THAT THE 'x' IN THE GRID CORRESPONDES WITH exit_location

    MazeComponent *components;
    int component_count;
    // int teleporter_count;
    // V2d *teleporter_location;
} Maze;

Maze *maze_create(int width, int height);
void maze_load_from_file(Maze *maze, const char *filename);  // not implemented
void maze_generate_random(Maze *maze);  // not implemented
void maze_draw(const Maze *maze);
void maze_draw_distance(const Maze *maze, const V2d player_pos, int distance);
void maze_draw_fixed_size(const Maze *maze, V2d _from, const int _width, const int _height);
void maze_destroy(Maze *maze);
int maze_is_valid_move(Maze *maze, V2d pos);
int maze_is_exit(Maze *maze, V2d pos);
int maze_is_component(Maze *maze, V2d pos, MazeComponentType type);
void maze_add_component(Maze *maze, MazeComponentType type, int count);
V2d maze_get_random_teleporter_pos(Maze *maze);
void maze_place_teleporters(Maze *maze, const int count, double density);
int maze_get_specific_component(Maze *maze, MazeComponentType type);

#endif
