#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

int build_config(Config* config, int argc, char** argv) {
    char c;
    char* endptr = NULL;
    int non_numeric_found = 0;

    opterr = 0;

    while ((c = getopt(argc, argv, FLAGS_SCHEMA)) != -1) {
        endptr = NULL;
        switch (c) {
            case 'r':
                config->row_cnt = strtol(optarg, &endptr, 10);
                non_numeric_found = optarg && *endptr != 0;
                if (non_numeric_found || config->row_cnt <= 0)
                    return 3;
                break;
            case 'c':
                config->col_cnt = strtol(optarg, &endptr, 10);
                non_numeric_found = optarg && *endptr != 0;
                if (non_numeric_found || config->col_cnt <= 0)
                    return 4;
                break;
            case 'n':
                config->iter_no = strtol(optarg, &endptr, 10);
                non_numeric_found = optarg && *endptr != 0;
                if (non_numeric_found || config->iter_no <= 0)
                    return 5;
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
                } else if (strcmp(optarg, "") == 0) {
                    return 16;
                } else {
                    return 6;
                }
                break;
            case 'l':
                config->loop_on_walls = true;
                break;
            case 'i':
                config->input_file = optarg;
                break;
            case 'R':
                config->rnd_fill_ratio = strtol(optarg, &endptr, 10);
                non_numeric_found = optarg && *endptr != 0;
                if (non_numeric_found ||
                    config->rnd_fill_ratio < 0 ||
                    config->rnd_fill_ratio > 100)
                    return 7;
                config->rnd_fill_ratio /= 100;
                break;
            case '?':
                switch (optopt) {
                    case 'r':
                    case 'c':
                    case 'n':
                    case 'p':
                    case 'd':
                    case 'i':
                    case 'R':
                        return 2;
                    default:
                        return 1;
                }
                break;
            default:
                return 1;
        }
    }

    if (config->row_cnt <= 0)
        return 13;
    if (config->col_cnt <= 0)
        return 14;
    if (config->iter_no <= 0)
        return 15;

    return 0;
}

void print_config_error(char* scriptname, int errorcode) {
    switch (errorcode) {
        case 1:
            fprintf(stderr,
                    "%s: nieznany argument '-%c'\n",
                    scriptname,
                    optopt);
            break;
        case 2:
            fprintf(stderr,
                    "%s: brak wartości dla argumentu '-%c'\n",
                    scriptname,
                    optopt);
            break;
        case 3:
            fprintf(stderr,
                    "%s: nieprawidłowa wartość dla argumentu '-r'\n",
                    scriptname);
            break;
        case 4:
            fprintf(stderr,
                    "%s: nieprawidłowa wartość dla argumentu '-c'\n",
                    scriptname);
            break;
        case 5:
            fprintf(stderr,
                    "%s: nieprawidłowa wartość dla argumentu '-n'\n",
                    scriptname);
            break;
        case 6:
            fprintf(stderr,
                    "%s: nieprawidłowa wartość dla argumentu '-d'\n",
                    scriptname);
            break;
        case 7:
            fprintf(stderr,
                    "%s: Nieprawidłowa wartość dla argumentu '-R'\n",
                    scriptname);
            break;
        case 13:
            fprintf(stderr,
                    "%s: brak wymaganego argumentu '-r'\n",
                    scriptname);
            break;
        case 14:
            fprintf(stderr,
                    "%s: brak wymaganego argumentu '-c'\n",
                    scriptname);
            break;
        case 15:
            fprintf(stderr,
                    "%s: brak wymaganego argumentu '-n'\n",
                    scriptname);
            break;
        case 16:
            fprintf(stderr,
                    "%s: brak wymaganego argumentu '-d'\n",
                    scriptname);
            break;
    }
}
