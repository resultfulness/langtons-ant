# Mrówka Langtona - sposób korzystania z programu


## Kompilacja

Przed kompilacją, należy upewnić się, że w środowisku wykonywalnym znajdują się:
- kompilator `gcc`
- program `make`

W celu kompilacji programu należy wykonać polecenie `make` w głównym katalogu
programu.

```bash
make
```

Po kompilacji, w katalogu programu powinny pojawić się:
- program wykonywalny `langtons-ant`
- folder z plikami obiektowymi `build`
- folder na pliki wyjściowe `out`


## Wykonywanie

Program można wykonać uruchamiając plik `langtons-ant`, zgodnie ze stroną pomocy
przedstawioną poniżej:

```
Użycie: ./langtons-ant WYMAGANE_OPCJE [INNE_OPCJE]
Generuje kolejne iteracje mrówki Langtona.
WYMAGANE_OPCJE:
  -r    liczba wierszy planszy
  -c    liczba kolumn planszy
  -n    liczba iteracji do wygenerowania
Alternatywnie:
  -h    wyświetl tą pomoc
INNE_OPCJE:
  -d    początkowy kierunek mrówki, domyślnie N (północ); możliwe wartości:
        N, E, S, W
  -R    procent planszy do wypełnienia losowymi polami czarnymi, domyślnie 0
  -p    przedrostek pliku wyjściowego; brak argumentu powoduje wyświetlenie
        iteracji na standardowe wyjście
  -i    plik wejściowy, od którego rozpoczynane będzie generowanie; brak
        argumentu spowoduje wygenerowanie 'od zera'
```
