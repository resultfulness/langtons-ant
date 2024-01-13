#ifndef _LANGTON_IO_H
#define _LANGTON_IO_H

#include "langton.h"
#include <stdio.h>

#define WALL_VERTICAL L'│'
#define WALL_HORIZONTAL L'─'
#define WALL_NORTHWEST_CORNER L'┌'
#define WALL_NORTHEAST_CORNER L'┐'
#define WALL_SOUTHWEST_CORNER L'└'
#define WALL_SOUTHEAST_CORNER L'┘'
#define TILE_WHITE L' '
#define TILE_BLACK L'█'
#define ANT_NORTH_WHITE L'△'
#define ANT_NORTH_BLACK L'▲'
#define ANT_EAST_WHITE L'▷'
#define ANT_EAST_BLACK L'▶'
#define ANT_SOUTH_WHITE L'▽'
#define ANT_SOUTH_BLACK L'▼'
#define ANT_WEST_WHITE L'◁'
#define ANT_WEST_BLACK L'◀'

#define OUT_DIR "out/"

wchar_t get_ant_ch(Ant a, TileColor clr);
char* get_outfilepath(char* outfile_prefix, int outfile_no);
int write_state(Ant a, Board b, FILE* write_loc);
int read_state(Ant* a, Board* b, FILE* read_loc);

#endif
