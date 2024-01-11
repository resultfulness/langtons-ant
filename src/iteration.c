#include "iteration.h"

void iterate(Ant* a, Board* b) {
    if(a->x >= b->width || a->x < 0 || a->y < 0 || a->y >= b->height)
        return;
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
    a->iter_cnt++;
}
