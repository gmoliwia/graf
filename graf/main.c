#include "graf.h"
#include<stdio.h>
#include <stdlib.h>
#include<math.h>
int main()
{
    Graf* graf = wczytajGraf("graftestsigma.txt"); // <- przypisz graf do zmiennej
    if (!graf) {
        printf("Nie udało się wczytać grafu.\n");
        return 1;
    }

    int* przypisania = malloc(sizeof(int) * graf->liczbaWezlow); // <- zaalokuj przypisania
    if (!przypisania) {
        printf("Blad alokacji przypisan.\n");
        return 1;
    }
    for (int i = 0; i < graf->liczbaWezlow; i++) przypisania[i] = -1; // inicjalizuj

    podzielGrafBFSZaawansowany(graf, 2, 10.0, przypisania);  // <- wywołanie funkcji OK

    // wyświetlenie wyników
    for (int i = 0; i < graf->liczbaWezlow; i++) {
        printf("Wezel %d przypisany do czesci %d\n", i, przypisania[i]);
    }


    free(przypisania);
    for (int i = 0; i < graf->liczbaWezlow; i++) {
        free(graf->wezly[i].listaPowiazan);
    }
    free(graf->wezly);
    free(graf->tablicaWezlow);
    free(graf);

    return 0;
}