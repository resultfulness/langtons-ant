#ifndef _CONFIG_H
#define _CONFIG_H

#include <stdbool.h>
#include "langton.h"

/* FLAGS_SCHEMA - schemat argumentów wywołania dla biblioteki getopt.h */
#define FLAGS_SCHEMA "r:c:n:p:d:i:R:"

/* Config - konfiguracja programu
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
    bool loop_on_walls;
    char* output_prefix;
    char* input_file;
    double rnd_fill_ratio;
} Config;

/* config_errorcode - wartości błędów dla generowania konfiguracji */
enum config_errorcode {
    NO_ERROR,
    UNKNOWN_ARGUMENT,
    MISSING_ARGUMENT_VALUE,
    INCORRECT_ROW_VALUE,
    INCORRECT_COLUMN_VALUE,
    INCORRECT_ITERATION_VALUE,
    INCORRECT_DIRECTION_VALUE,
    INCORRECT_RANDOM_FILL_VALUE,
    MISSING_ROW_ARGUMENT,
    MISSING_COLUMN_ARGUMENT,
    MISSING_ITERATION_ARGUMENT,
    HELP_ARGUMENT_OUT_OF_CONTEXT
};

/* build_config - wypełnia konfigurację programu na podstawie argumentów
 * wywołania
 *
 * Argumenty:
 *   - Config* config: wskaźnik na konfigurację programu
 *   - int argc: ilość argumentów wywołania
 *   - char** argv: tablica argumentów wywołania
 *
 * Zwraca enum config_errorcodes:
 *   - kod błędu generowania konfiguracji
 */
enum config_errorcode build_config(Config* config, int argc, char** argv);

/* print_config_error - wyświetla błąd generowania konfiguracji na podstawie
 * kodu błędu
 *
 * Argumenty:
 *   - char* scriptname: nazwa wykonywanego skryptu
 *   - enum config_errorcode errorcode: kod błędu
 */
void print_config_error(char* scriptname, enum config_errorcode errorcode);

#endif
