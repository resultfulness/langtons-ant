#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "iteration.h"
#include "langton.h"
#include "langton_io.h"

int main(int argc, char** argv) {
    int result = 0;

    Config* config = calloc(1, sizeof(Config));
    if (config == NULL) {
        fprintf(stderr, "%s: błąd alokacji\n", argv[0]);
        result = 1;
        goto out_nofree;
    }

    if ((result = build_config(config, argc, argv)) != 0) {
        print_config_error(argv[0], result);
        result = 1;
        goto out_free_config;
    }

    FILE* out;
    if (config->output_prefix == NULL)
        out = stdout;

    Ant a = {
        .x = config->row_cnt / 2,
        .y = config->col_cnt / 2,
        .direction = config->initial_dir,
        .iter_no = 0
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
        if (out != stdout) {
            result = open_outfile(out, config->output_prefix, a.iter_no);
            if (result == 1) {
                fprintf(stderr, "%s: błąd alokacji\n", argv[0]);
                /* todo: goto out_free_FOO */
                return 1;
            } else if (result == 2) {
                fprintf(stderr,
                        "%s: nie można otworzyć pliku wyjściowego",
                        argv[0]);
                /* todo: goto out_free_FOO */
                return 1;
            }
        }
        write_state(a, b, out);
        if (out != stdout)
            fclose(out);
    }

out_free_config:
    free(config);

out_nofree:
    return result;
}
