#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

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

char* strpush_i(char* s, int n) {
    /* alokacja:
     * - rozmiar napisu
     * - bit na znak podkreślnika `_`
     * - 21 znaków (pomieści liczby 64bit) LUB 12 znaków (pomieści liczby 32bit)
     * - NULL terminujący napis
     */
    char* result = malloc(strlen(s) + 1 + 21 /*12*/ + 1);
    if (result == NULL)
        return NULL;
    sprintf(result, "%s_%d", s, n);
    return result;
}

int open_outfile(FILE* out, char* outfile_prefix, int outfile_no) {
    char* filename = strpush_i(outfile_prefix, outfile_no);
    if (filename == NULL)
        return 1;
    char* path = malloc(strlen(filename) + strlen(OUT_DIR));
    if (path == NULL) {
        free(filename);
        return 1;
    }
    sprintf(path, "%s%s", OUT_DIR, filename);

    out = fopen(path, "w");
    if (out == NULL) {
        free(filename);
        free(path);
        return 2;
    }
    free(filename);
    free(path);
    return 0;
}

int write_state(Ant a, Board b, FILE* write_loc) {
    fprintf(write_loc, "%d:\n", a.iter_no);
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

int read_state(Ant* a, Board* b, FILE* read_loc) {


    return 0;
}
