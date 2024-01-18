#ifndef _LANGTON_H
#define _LANGTON_H

/* Direction - reprezentuje kierunki, w które zwrócona może być mrówka */
typedef enum {
    NORTH,
    EAST,
    SOUTH,
    WEST
} Direction;

/* TileColor - kolor komórki planszy */
typedef enum {
    WHITE,
    BLACK
} TileColor;

/* Ant - reprezentacja mrówki
 *
 * Pola:
 *   - int x: pozycja pozioma mrówki
 *   - int y: pozycja pionowa mrówki
 *   - Direction direction : 2: kierunek, w którym zwrócona jest mrówka
 */
typedef struct {
    int x;
    int y;
    Direction direction : 2;
} Ant;

/* Board - reprezentacja planszy
 *
 * Pola:
 *   - int width: szerokość planszy
 *   - int height: wysokość planszy
 *   - TileColor** tile_colors: dwuwymiarowa tablica przechowująca kolory
 *   komórek planszy
 */
typedef struct {
    int width;
    int height;
    TileColor** tile_colors;
} Board;

#endif
