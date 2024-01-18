#include "iteration.h"

int iterate(Ant* a, Board* b) {
    if (b->tile_colors[a->y][a->x] == WHITE)
        a->direction++;
    else
        a->direction--;

    b->tile_colors[a->y][a->x] = !b->tile_colors[a->y][a->x];

    switch (a->direction) {
        case NORTH:
            a->y--;
            break;
        case EAST:
            a->x++;
            break;
        case SOUTH:
            a->y++;
            break;
        case WEST:
            a->x--;
            break;
    }
    if(a->x >= b->width || a->x < 0 || a->y < 0 || a->y >= b->height)
        return 1;
    return 0;
}
