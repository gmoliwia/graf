#include <stddef.h>
#include "graf.h"


Graf* PodzielGraf(Graf* graf, Graf* PodzielonyGraf, int LiczbaPodzialow, int margines)
{
	if (graf && PodzielonyGraf)
	{

	} else printf("Nie podano niezbednych danych wejsiowych\n");
	return NULL;
}

bool czySpojny(Graf* graf) {
    if (!graf || graf->liczbaWezlow <= 0) return false;

    bool* odwiedzone = (bool*)calloc(graf->liczbaWezlow, sizeof(bool));
    if (!odwiedzone) {
        printf("Błąd alokacji pamięci.\n");
        return false;
    }

    int* kolejka = (int*)malloc(graf->liczbaWezlow * sizeof(int));
    int front = 0, tyl = 0;

    kolejka[tyl++] = 0;
    odwiedzone[0] = true;

    while (front < tyl) {
        int aktualny = kolejka[front++];

        for (int i = 0; i < graf->liczbaWierszy; i++) {
            int sasiad = -1;
            if (graf->tablicaWezlow[i].a == aktualny) {
                sasiad = graf->tablicaWezlow[i].b;
            } else if (graf->tablicaWezlow[i].b == aktualny) {
                sasiad = graf->tablicaWezlow[i].a;
            }

            if (sasiad != -1 && !odwiedzone[sasiad]) {
                odwiedzone[sasiad] = true;
                kolejka[tyl++] = sasiad;
            }
        }
    }

    bool spojny = true;
    for (int i = 0; i < graf->liczbaWezlow; i++) {
        if (!odwiedzone[i]) {
            spojny = false;
            break;
        }
    }

    free(odwiedzone);
    free(kolejka);
    return spojny;
