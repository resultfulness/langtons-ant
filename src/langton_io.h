#ifndef _LANGTON_IO_H
#define _LANGTON_IO_H

#include <stdio.h>

#include "langton.h"

/* znaki wykorzystywane do wyświetlania stanu algorytmu */
#define WALL_VERTICAL L'│'
#define WALL_HORIZONTAL L'─'
#define WALL_NORTHWEST_CORNER L'┌'
#define WALL_NORTHEAST_CORNER L'┐'
#define WALL_SOUTHWEST_CORNER L'└'
#define WALL_SOUTHEAST_CORNER L'┘'
#define TILE_WHITE L' '
#define TILE_BLACK L'█'
#define ANT_NORTH_WHITE L'△'
#define ANT_NORTH_BLACK L'▲'
#define ANT_EAST_WHITE L'▷'
#define ANT_EAST_BLACK L'▶'
#define ANT_SOUTH_WHITE L'▽'
#define ANT_SOUTH_BLACK L'▼'
#define ANT_WEST_WHITE L'◁'
#define ANT_WEST_BLACK L'◀'

/* OUT_DIR - folder docelowy plików wyjściowych, tworzony w trakcie
 * kompilacji
 */
#define OUT_DIR "out/"

/* get_ant_ch - znak mrówki na polu o danym kolorze
 *
 * Argumenty:
 *   - Ant a: mrówka
 *   - TileColor clr: kolor pola na którym znajduje się mrówka
 *
 * Zwraca wchar_t:
 *   - znak reprezentujący mrówkę
 */
wchar_t get_ant_ch(Ant a, TileColor clr);

/* get_outfilepath - generuje ścieżkę pliku wyjściowego w OUT_DIR łączac
 * pierwszy i drugi argument podkreślnikiem '_'. Po wykorzystaniu zwróconego
 * napisu należy uwolnić go do pamięci
 *
 * Argumenty:
 *   - char* outfile_prefix: przedrostek pliku wyjściowego
 *   - int outfile_no: przyrostek pliku wyjściowego
 *
 * Zwraca char*:
 *   - napis będący ścieżką do pliku wyjściowego
 */
char* get_outfilepath(char* outfile_prefix, int outfile_no);

/* write_state - wypisuje obecny stan programu do pliku
 *
 * Argumenty:
 *   - Ant a: mrówka
 *   - Board b: plansza
 *   - FILE* write_loc: plik, do którego zapisany będzie stan programu
 *
 * Zwraca int:
 *   - 0, jeśli wypisanie udało się
 */
int write_state(Ant a, Board b, FILE* write_loc);

/* read_state - wczytuje stan programu z pliku
 *
 * Argumenty:
 *   - Ant* a: wskaźnik na mrówkę, do której zapisany będzie stan
 *   - Board* b: wskaźnik na planszę, do której zapisany będzie stan
 *   - FILE* read_loc: plik, z którego wczytany będzie stan programu
 *
 * Zwraca int:
 *   - 1, jeśli format pliku wejściowego jest niepoprawny
 *   - 0, jeśli poprawnie odczytano stan programu
 * */
int read_state(Ant* a, Board* b, FILE* read_loc);

#endif
