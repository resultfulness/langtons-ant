#ifndef _LANGTON_H
#define _LANGTON_H

typedef enum {
    NORTH,
    EAST,
    SOUTH,
    WEST
} Direction;

typedef enum {
    WHITE,
    BLACK
} TileColor;

typedef struct {
    int x;
    int y;
    Direction direction : 2;
} Ant;

typedef struct {
    int width;
    int height;
    TileColor** tile_colors;
} Board;

#endif
