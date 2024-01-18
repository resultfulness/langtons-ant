#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#include "langton_io.h"
#include "langton.h"

wchar_t get_ant_ch(Ant a, TileColor clr) {
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

char* get_outfilepath(char* outfile_prefix, int outfile_no) {
    char* filename = strpush_i(outfile_prefix, outfile_no);
    if (filename == NULL)
        return NULL;
    char* path = malloc(strlen(filename) + strlen(OUT_DIR));
    if (path == NULL) {
        free(filename);
        return NULL;
    }
    sprintf(path, "%s%s", OUT_DIR, filename);
    free(filename);
    return path;
}

int write_state(Ant a, Board b, FILE* write_loc) {
    fprintf(write_loc, "%lc", WALL_NORTHWEST_CORNER);
    for (int i = 0; i < b.width; i++) {
        fprintf(write_loc, "%lc", WALL_HORIZONTAL);
    }
    fprintf(write_loc, "%lc\n", WALL_NORTHEAST_CORNER);
    for (int i = 0; i < b.height; i++) {
        fprintf(write_loc, "%lc", WALL_VERTICAL);
        for (int j = 0; j < b.width; j++) {
            if (a.y == i && a.x == j) {
                fprintf(write_loc, "%lc", get_ant_ch(a, b.tile_colors[i][j]));
            } else if (b.tile_colors[i][j] == BLACK) {
                fprintf(write_loc, "%lc", TILE_BLACK);
            } else {
                fprintf(write_loc, "%lc", TILE_WHITE);
            }
        }
        fprintf(write_loc, "%lc\n", WALL_VERTICAL);
    }
    fprintf(write_loc, "%lc", WALL_SOUTHWEST_CORNER);
    for (int i = 0; i < b.width; i++) {
        fprintf(write_loc, "%lc", WALL_HORIZONTAL);
    }
    fprintf(write_loc, "%lc\n", WALL_SOUTHEAST_CORNER);
    return 0;
}

int read_state(Ant* a, Board* b, FILE* read_loc) {
    for(int j = 0; j < b->height + 2; j++) {
        for(int i = 0; i < b->width + 3; i++) {
            wchar_t wc = getwc(read_loc);
            if(wc == WEOF) return 1;

            /* pominięcie 'ściany' planszy */
            if(j == 0 || i == 0 || j > b->height || i > b->width) {
                if (i == 0 && j == 0 && wc == WALL_NORTHWEST_CORNER) continue;
                else if (i == 0 && j == b->height + 1 && wc == WALL_SOUTHWEST_CORNER) continue;
                else if (i == b->width + 1 && j == b->height + 1 && wc == WALL_SOUTHEAST_CORNER) continue;
                else if (i == b->width + 1 && j == 0 && wc == WALL_NORTHEAST_CORNER) continue;
                else if ((i == b->width + 1 || i == 0) && wc == WALL_VERTICAL) continue;
                else if ((j == b->height + 1 || j == 0) && wc == WALL_HORIZONTAL) continue;
                else if (i == b->width + 2 && wc == '\n') continue;
                return 1;
            }

            switch (wc) {
                case TILE_BLACK:
                    b->tile_colors[j - 1][i - 1] = BLACK;
                    break;
                case TILE_WHITE:
                    b->tile_colors[j - 1][i - 1] = WHITE;
                    break;
                case ANT_NORTH_BLACK:
                    b->tile_colors[j - 1][i - 1] = BLACK;
                    a->x = i - 1;
                    a->y = j - 1;
                    a->direction = NORTH;
                    break;
                case ANT_NORTH_WHITE:
                    b->tile_colors[j - 1][i - 1] = WHITE;
                    a->x = i - 1;
                    a->y = j - 1;
                    a->direction = NORTH;
                    break;
                case ANT_EAST_BLACK:
                    b->tile_colors[j - 1][i - 1] = BLACK;
                    a->x = i - 1;
                    a->y = j - 1;
                    a->direction = EAST;
                    break;
                case ANT_EAST_WHITE:
                    b->tile_colors[j - 1][i - 1] = WHITE;
                    a->x = i - 1;
                    a->y = j - 1;
                    a->direction = EAST;
                    break;
                case ANT_SOUTH_BLACK:
                    b->tile_colors[j - 1][i - 1] = BLACK;
                    a->x = i - 1;
                    a->y = j - 1;
                    a->direction = SOUTH;
                    break;
                case ANT_SOUTH_WHITE:
                    b->tile_colors[j - 1][i - 1] = WHITE;
                    a->x = i - 1;
                    a->y = j - 1;
                    a->direction = SOUTH;
                    break;
                case ANT_WEST_BLACK:
                    b->tile_colors[j - 1][i - 1] = BLACK;
                    a->x = i - 1;
                    a->y = j - 1;
                    a->direction = WEST;
                    break;
                case ANT_WEST_WHITE:
                    b->tile_colors[j - 1][i - 1] = WHITE;
                    a->x = i - 1;
                    a->y = j - 1;
                    a->direction = WEST;
                    break;
                default:
                    return 1;
            }
        }
    }
    if(getwc(read_loc) != WEOF) return 1;
    return 0;
}
