#include "util.h"

V2d V2d_add(V2d v1, V2d v2)
{
    V2d sum = {
        .x = v1.x + v2.x,
        .y = v1.y + v2.y,
    };

    return sum;
}

V2d V2d_sub(V2d v1, V2d v2)
{
    V2d diff = {
        .x = v1.x - v2.x,
        .y = v1.y - v2.y,
    };

    return diff;
}

int V2d_manhattan_distance(V2d v1, V2d v2)
{
    V2d diff = V2d_sub(v1, v2);
    return abs(diff.x) + abs(diff.y);
}

int abs(int num)
{
    return num > 0 ? num : -num;
}
