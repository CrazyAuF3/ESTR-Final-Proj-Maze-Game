#ifndef _UTIL_H
#define _UTIL_H

#define HORIZONTAL_DISPLAY_OFFSET (2)

#define D_POS(X) (X + HORIZONTAL_DISPLAY_OFFSET)

#define V2D_ZERO_VECTOR() (V2d){.x = 0, .y = 0}
#define V2D_UNIT_VECTOR() (V2d){.x = 1, .y = 1}
#define V2D_NEGATIVE_UNIT_VECTOR() (V2d){.x = -1, .y = -1}

typedef struct {
    int x;
    int y;
} V2d;

V2d V2d_add(V2d, V2d);
V2d V2d_sub(V2d, V2d);
int V2d_manhattan_distance(V2d, V2d);
int abs(int);

#endif
