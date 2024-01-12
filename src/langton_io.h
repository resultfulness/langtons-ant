#ifndef _LANGTON_IO_H
#define _LANGTON_IO_H

#include "langton.h"
#include <stdio.h>

#define WALL_VERTICAL "│"
#define WALL_HORIZONTAL "─"
#define WALL_NORTHWEST_CORNER "┌"
#define WALL_NORTHEAST_CORNER "┐"
#define WALL_SOUTHWEST_CORNER "└"
#define WALL_SOUTHEAST_CORNER "┘"
#define TILE_WHITE " "
#define TILE_BLACK "█"
#define ANT_NORTH_WHITE "△"
#define ANT_NORTH_BLACK "▲"
#define ANT_EAST_WHITE "▷"
#define ANT_EAST_BLACK "▶"
#define ANT_SOUTH_WHITE "▽"
#define ANT_SOUTH_BLACK "▼"
#define ANT_WEST_WHITE "◁"
#define ANT_WEST_BLACK "◀"

#define OUT_DIR "out/"

char* get_ant_ch(Ant a, TileColor clr);
int open_outfile(FILE* out, char* outfile_prefix, int outfile_no);
int write_state(Ant a, Board b, FILE* write_loc);
int read_state(Ant* a, Board* b, FILE* read_loc);

#endif
