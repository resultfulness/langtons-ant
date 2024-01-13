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
    };
    Board b = {
        .width = config->row_cnt,
        .height = config->col_cnt,
    };
    TileColor** tc = malloc(sizeof(TileColor*) * b.height);
    for(int i = 0; i < b.height; i++)
        tc[i] = calloc(sizeof(TileColor), b.width);
    b.tile_colors = tc;
    if (config->input_file != NULL) {
        FILE* in = fopen(config->input_file, "r");
        if (in == NULL) {
            fprintf(stderr,
                    "%s: nie można otworzyć pliku wejściowego '%s'\n",
                    argv[0],
                    config->input_file);
            /* todo: goto out_free_FOO */
            return 1;
        }
        if(read_state(&a, &b, in)) {
            fprintf(stderr,
                    "%s: nieprawidłowy format pliku wejściowego '%s'\n",
                    argv[0],
                    config->input_file);
            /* todo: goto out_free_FOO */
            return 1;
        }
    }

    for(int i = 1; i <= config->iter_no; i++) {
        iterate(&a, &b);
        if (out != stdout) {
            char* path = get_outfilepath(config->output_prefix, i);
            if (path == NULL) {
                fprintf(stderr, "%s: błąd alokacji\n", argv[0]);
                /* todo: goto out_free_FOO */
                return 1;
            }
            out = fopen(path, "w");
            if (out == NULL) {
                fprintf(stderr,
                        "%s: nie można otworzyć pliku wyjściowego '%s'\n",
                        argv[0],
                        path);
                /* todo: goto out_free_FOO */
                return 1;
            }
        }
        if(out == stdout) {
            fprintf(out, "%d:\n", i);
            write_state(a, b, out);
        } else {
            write_state(a, b, out);
            fclose(out);
        }
    }

out_free_config:
    free(config);

out_nofree:
    return result;
}
