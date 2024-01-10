#include <stdio.h>

#include "langton_io.h"

char* get_ant_ch(Ant a, TileColor clr) {
    switch (a.direction) {
        case NORTH:
            return clr == BLACK ? ANT_NORTH_BLACK : ANT_NORTH_WHITE;
        case EAST:
            return clr == BLACK ? ANT_EAST_BLACK  : ANT_EAST_WHITE;
        case SOUTH:
            return clr == BLACK ? ANT_SOUTH_BLACK : ANT_SOUTH_WHITE;
        case WEST:
            return clr == BLACK ? ANT_WEST_BLACK  : ANT_WEST_WHITE;
    }
}

int write_state(Ant a, Board b, FILE* write_loc) {
    fprintf(write_loc, "%d:\n", a.iter_cnt);
    fputs(WALL_NORTHWEST_CORNER, write_loc);
    for (int i = 0; i < b.width; i++) {
        fputs(WALL_HORIZONTAL, write_loc);
    }
    fputs(WALL_NORTHEAST_CORNER, write_loc);
    fputc('\n', write_loc);
    for (int i = 0; i < b.height; i++) {
        fputs(WALL_VERTICAL, write_loc);
        for (int j = 0; j < b.width; j++) {
            if (a.y == i && a.x == j) {
                fputs(get_ant_ch(a, b.tile_colors[i][j]), write_loc);
            } else if (b.tile_colors[i][j] == BLACK) {
                fputs(TILE_BLACK, write_loc);
            } else {
                fputs(TILE_WHITE, write_loc);
            }
        }
        fputs(WALL_VERTICAL, write_loc);
        fputc('\n', write_loc);
    }
    fputs(WALL_SOUTHWEST_CORNER, write_loc);
    for (int i = 0; i < b.width; i++) {
        fputs(WALL_HORIZONTAL, write_loc);
    }
    fputs(WALL_SOUTHEAST_CORNER, write_loc);
    fputc('\n', write_loc);
    return 0;
}


