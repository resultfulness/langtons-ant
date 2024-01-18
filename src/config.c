#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

enum config_errorcode build_config(Config* config, int argc, char** argv) {
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
                    return INCORRECT_ROW_VALUE;
                break;
            case 'c':
                config->col_cnt = strtol(optarg, &endptr, 10);
                non_numeric_found = optarg && *endptr != 0;
                if (non_numeric_found || config->col_cnt <= 0)
                    return INCORRECT_COLUMN_VALUE;
                break;
            case 'n':
                config->iter_no = strtol(optarg, &endptr, 10);
                non_numeric_found = optarg && *endptr != 0;
                if (non_numeric_found || config->iter_no <= 0)
                    return INCORRECT_ITERATION_VALUE;
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
                    return INCORRECT_DIRECTION_VALUE;
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
                    return INCORRECT_RANDOM_FILL_VALUE;
                config->rnd_fill_ratio /= 100;
                break;
            case 'h':
                return HELP_ARGUMENT_OUT_OF_CONTEXT;
            case '?':
                switch (optopt) {
                    case 'r':
                    case 'c':
                    case 'n':
                    case 'p':
                    case 'd':
                    case 'i':
                    case 'R':
                        return MISSING_ARGUMENT_VALUE;
                    case 'h':
                        return HELP_ARGUMENT_OUT_OF_CONTEXT;
                    default:
                        return UNKNOWN_ARGUMENT;
                }
                break;
            default:
                return UNKNOWN_ARGUMENT;
        }
    }

    if (config->row_cnt <= 0)
        return MISSING_ROW_ARGUMENT;
    if (config->col_cnt <= 0)
        return MISSING_COLUMN_ARGUMENT;
    if (config->iter_no <= 0)
        return MISSING_ITERATION_ARGUMENT;

    return NO_ERROR;
}

void print_config_error(char* scriptname, enum config_errorcode errorcode) {
    switch (errorcode) {
        case NO_ERROR:
            return;
        case UNKNOWN_ARGUMENT:
            fprintf(stderr,
                    "%s: nieznany argument '-%c'\n",
                    scriptname,
                    optopt);
            break;
        case MISSING_ARGUMENT_VALUE:
            fprintf(stderr,
                    "%s: brak wartości dla argumentu '-%c'\n",
                    scriptname,
                    optopt);
            break;
        case INCORRECT_ROW_VALUE:
            fprintf(stderr,
                    "%s: nieprawidłowa wartość dla argumentu '-r'\n",
                    scriptname);
            break;
        case INCORRECT_COLUMN_VALUE:
            fprintf(stderr,
                    "%s: nieprawidłowa wartość dla argumentu '-c'\n",
                    scriptname);
            break;
        case INCORRECT_ITERATION_VALUE:
            fprintf(stderr,
                    "%s: nieprawidłowa wartość dla argumentu '-n'\n",
                    scriptname);
            break;
        case INCORRECT_DIRECTION_VALUE:
            fprintf(stderr,
                    "%s: nieprawidłowa wartość dla argumentu '-d'\n",
                    scriptname);
            break;
        case INCORRECT_RANDOM_FILL_VALUE:
            fprintf(stderr,
                    "%s: Nieprawidłowa wartość dla argumentu '-R'\n",
                    scriptname);
            break;
        case MISSING_ROW_ARGUMENT:
            fprintf(stderr,
                    "%s: brak wymaganego argumentu '-r'\n",
                    scriptname);
            break;
        case MISSING_COLUMN_ARGUMENT:
            fprintf(stderr,
                    "%s: brak wymaganego argumentu '-c'\n",
                    scriptname);
            break;
        case MISSING_ITERATION_ARGUMENT:
            fprintf(stderr,
                    "%s: brak wymaganego argumentu '-n'\n",
                    scriptname);
            break;
        case HELP_ARGUMENT_OUT_OF_CONTEXT:
            fprintf(stderr,
                    "%s: argument '-h' nie jest dozwolony w tym kontekście\n",
                    scriptname);
            break;
        default:
            fprintf(stderr, "%s: nieznany błąd\n", scriptname);
    }
    fprintf(stderr, "więcej informacji: '%s -h'\n", scriptname);
}
