#include "graf.h"
int main()
{
	wczytajGraf("graftestsigma.txt");
	Graf* g = wczytajGraf("graf.txt");

    if (czySpojny(g)) {
        printf("Graf jest spójny.\n");
    } else {
        printf("Graf NIE jest spójny.\n");
    }

    saveText("wynik.txt", g);
    saveBin("wynik.bin", g);

    // Zwolnij pamięć itp. jak chcesz
    free(g->tablicaWezlow);
    free(g);
    return 0;

}