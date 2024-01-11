#include <getopt.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

int build_config(Config* config, int argc, char** argv) {
    char c;

    while ((c = getopt(argc, argv, FLAGS_SCHEMA)) != -1) {
        switch (c) {
            case 'r':
                config->row_cnt = atoi(optarg);
                break;
            case 'c':
                config->col_cnt = atoi(optarg);
                break;
            case 'n':
                config->iter_no = atoi(optarg);
                break;
            case 'p':
                config->output_prefix = optarg;
                break;
            case 'd':
                if (strcmp(optarg, "N") == 0) {
                    config->initial_dir = NORTH;
                } else if (strcmp(optarg, "E") == 0) {
                    config->initial_dir = EAST;
                } else if (strcmp(optarg, "S") == 0) {
                    config->initial_dir = SOUTH;
                } else if (strcmp(optarg, "W") == 0) {
                    config->initial_dir = WEST;
                } else {
                    return 5;
                }
                break;
            case 'i':
                config->input_file = optarg;
                break;
            case 'R':
                config->rnd_fill_ratio = atof(optarg);
                break;
            default:
                return 8;
        }
    }
    return 0;
}
