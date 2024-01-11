#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "iteration.h"
#include "langton.h"
#include "langton_io.h"

int main(int argc, char** argv) {
    Config* config = malloc(sizeof(Config));
    build_config(config, argc, argv);

    Ant a = {
        .x = config->row_cnt / 2,
        .y = config->col_cnt / 2,
        .direction = config->initial_dir,
        .iter_cnt = 0
    };
    Board b = {
        .width = config->row_cnt,
        .height = config->col_cnt,
    };
    TileColor** tc = malloc(sizeof(TileColor*) * b.height);
    for(int i = 0; i < b.height; i++)
        tc[i] = calloc(sizeof(TileColor), b.width);
    b.tile_colors = tc;
    for(int i = 0; i < config->iter_no; i++) {
        iterate(&a, &b);
    }
    write_state(a, b, stdout);
    return 0;
}
