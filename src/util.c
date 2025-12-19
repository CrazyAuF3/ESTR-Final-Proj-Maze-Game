#include "util.h"

V2d V2d_add(V2d v1, V2d v2)
{
    V2d sum = {
        .x = v1.x + v2.x,
        .y = v1.y + v2.y,
    };

    return sum;
}
