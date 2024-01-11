#ifndef _CONFIG_H
#define _CONFIG_H

#include <stdbool.h>
#include "langton.h"

#define FLAGS_SCHEMA "r:c:n:p:d:i:R:"

/* Config
 *
 * Pola:
 *   - row_cnt: liczba wierszy planszy (-r)
 *   - col_cnt: liczba kolumn planszy (-c)
 *   - iter_no: liczba iteracji (-n)
 *   - initial_dir: początkowy kierunek mrówki (-d)
 *   - output_prefix: opcjonalny przedrostek plików wynikowych (-p)
 *   - input_file: opcjonalna ścieżka do pliku wejściowego (-i)
 *   - rnd_fill_ratio: opcjonalne losowe początkowe wypełnienie planszy (-R)
 */
typedef struct {
    int row_cnt;
    int col_cnt;
    int iter_no;
    Direction initial_dir;
    char* output_prefix;
    char* input_file;
    double rnd_fill_ratio;
} Config;

int build_config(Config* config, int argc, char** argv);

#endif
