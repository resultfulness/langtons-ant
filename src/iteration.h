#ifndef _ITERATION_H
#define _ITERATION_H

#include "langton.h"

/* iterate - generuje następną iterację mrówki Langtona
 *
 * Argumenty:
 *   - Ant* a: wskaźnik na mrówkę wykorzystaną w generowaniu
 *   - Board* b: wskaźnik na planszę wykorzystaną w generowaniu
 *
 * Zwraca int:
 *   - 1, jeśli mrówka znalazła się poza planszą po wygenerowaniu iteracji
 *   - 0, jeśli iterację wygenerowano poprawnie
 */
int iterate(Ant* a, Board* b);

#endif
