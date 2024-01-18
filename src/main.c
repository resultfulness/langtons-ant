#include <getopt.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "config.h"
#include "iteration.h"
#include "help.h"
#include "langton.h"
#include "langton_io.h"

int main(int argc, char** argv) {
    setlocale(LC_ALL, "C.UTF-8");
    srand(time(NULL));
    int result = 0;

    if (argc > 1 && strcmp(argv[1], "-h") == 0) {
        print_help(argv[0]);
        goto out_nofree;
    }

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

    Ant ant = {
        .x = config->col_cnt / 2,
        .y = config->row_cnt / 2,
        .direction = config->initial_dir
    };
    Board board = {
        .width = config->col_cnt,
        .height = config->row_cnt
    };

    TileColor** tcs = malloc(sizeof(TileColor*) * board.height);
    if (tcs == NULL) {
        fprintf(stderr, "%s: błąd alokacji\n", argv[0]);
        result = 1;
        goto out_free_config;
    }
    for(int i = 0; i < board.height; i++) {
        tcs[i] = calloc(sizeof(TileColor), board.width);
        if (config->rnd_fill_ratio > 0) {
            for (int j = 0; j < board.width; j++) {
                double rnd = (double) rand() / RAND_MAX;
                tcs[i][j] = rnd < config->rnd_fill_ratio;
            }
        }
    }
    board.tile_colors = tcs;

    if (config->input_file != NULL) {
        FILE* in = fopen(config->input_file, "r");
        if (in == NULL) {
            fprintf(stderr,
                    "%s: nie można otworzyć pliku wejściowego '%s'\n",
                    argv[0],
                    config->input_file);
            result = 1;
            goto out_free_tilecolours;
        }
        if(read_state(&ant, &board, in) != 0) {
            fprintf(stderr,
                    "%s: nieprawidłowy format pliku wejściowego '%s'\n",
                    argv[0],
                    config->input_file);
            fclose(in);
            result = 1;
            goto out_free_tilecolours;
        } else {
            fclose(in);
        }
    }

    for(int i = 1; i <= config->iter_no; i++) {
        if (iterate(&ant, &board) != 0) {
            fprintf(stderr, "%s: mrówka dotarła do krańca planszy\n", argv[0]);
            break;
        }
        if (out != stdout) {
            char* path = get_outfilepath(config->output_prefix, i);
            if (path == NULL) {
                fprintf(stderr, "%s: błąd alokacji\n", argv[0]);
                result = 1;
                goto out_free_tilecolours;
            }
            out = fopen(path, "w");
            if (out == NULL) {
                fprintf(stderr,
                        "%s: nie można otworzyć pliku wyjściowego '%s'\n",
                        argv[0],
                        path);
                result = 1;
                goto out_free_tilecolours;
            }
        }
        if(out == stdout) {
            fprintf(out, "%d:\n", i);
            write_state(ant, board, out);
        } else {
            write_state(ant, board, out);
            fclose(out);
        }
    }

out_free_tilecolours:
    for(int i = 0; i < board.height; i++) {
        free(board.tile_colors[i]);
    }
    free(board.tile_colors);

out_free_config:
    free(config);

out_nofree:
    return result;
}
