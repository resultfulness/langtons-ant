#include <stdio.h>

#include "help.h"

void print_help(char *scriptname) {
    printf("Użycie: %s WYMAGANE_OPCJE [INNE_OPCJE]\n", scriptname);

    fputs("\
Generuje kolejne iteracje mrówki Langtona.\n\
WYMAGANE_OPCJE:\n\
  -r    liczba wierszy planszy\n\
  -c    liczba kolumn planszy\n\
  -n    liczba iteracji do wygenerowania\n\
Alternatywnie:\n\
  -h    wyświetl tą pomoc\n\
INNE_OPCJE:\n\
  -d    początkowy kierunek mrówki, domyślnie N (północ); możliwe wartości:\n\
        N, E, S, W\n\
  -R    procent planszy do wypełnienia losowymi polami czarnymi, domyślnie 0\n\
  -p    przedrostek pliku wyjściowego; brak argumentu powoduje wyświetlenie\n\
        iteracji na standardowe wyjście\n\
  -i    plik wejściowy, od którego rozpoczynane będzie generowanie; brak\n\
        argumentu spowoduje wygenerowanie 'od zera'\n\
", stdout);
}
