#include "iteration.h"
#include "langton.h"
#include "langton_io.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv) {
    Ant a = {
        .x = 50,
        .y = 30,
        .direction = NORTH,
        .iter_cnt = 0
    };
    Board b = {
        .width = 100,
        .height = 60,
    };
    TileColor** tc = malloc(sizeof(TileColor*) * b.height);
    for(int i = 0; i < b.height; i++)
        tc[i] = calloc(sizeof(TileColor), b.width);
    b.tile_colors = tc;
    for(int i = 0; i < 12000; i++) {
        iterate(&a, &b);
    }
    write_state(a, b, stdout);
    return 0;
}
