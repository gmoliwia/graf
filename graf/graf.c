#include <stddef.h>
#include <stdbool.h>
#include "graf.h"


Graf* PodzielGraf(Graf* graf, Graf* PodzielonyGraf, int LiczbaPodzialow, int margines)
{
	if (graf && PodzielonyGraf)
	{

	} else printf("Nie podano niezbednych danych wejsiowych\n");
	return NULL;
}

/*bool czySpojny(Graf* graf) {
    if (!graf || graf->liczbaWezlow <= 0) return false;

    bool* odwiedzone = (bool*)calloc(graf->liczbaWezlow, sizeof(bool));
    if (!odwiedzone)
    {
        printf("Błąd alokacji pamięci.\n");
        return false;
    }

    int* kolejka = (int*)malloc(graf->liczbaWezlow * sizeof(int));
    int front = 0, tyl = 0;

    kolejka[tyl++] = 0;
    odwiedzone[0] = true;

    while (front < tyl)
    {
        int aktualny = kolejka[front++];

        for (int i = 0; i < graf->liczbaWierszy; i++)
        {
            int sasiad = -1;
            if (Graf->tablicaWezlow[i].a == aktualny)
            {
                sasiad = Graf->tablicaWezlow[i].b;
            } else if (Graf->tablicaWezlow[i].b == aktualny)
            {
                sasiad = Graf->tablicaWezlow[i].a;
            }

            if (sasiad != -1 && !odwiedzone[sasiad])
            {
                odwiedzone[sasiad] = true;
                kolejka[tyl++] = sasiad;
            }
        }
    }

    bool spojny = true;
    for (int i = 0; i < graf->liczbaWezlow; i++)
    {
        if (!odwiedzone[i])
        {
            spojny = false;
            break;
        }
    }

    free(odwiedzone);
    free(kolejka);
    return spojny;
}
*/

    void podzielGrafBFSZaawansowany(Graf* graf, int liczbaCzesci, float marginesProcentowy, int* przypisania) {
    bool* odwiedzone = calloc(graf->liczbaWezlow, sizeof(bool));
    int* rozmiaryCzesci = calloc(liczbaCzesci, sizeof(int));
    int maksNaCzesc = ceil((1.0 + marginesProcentowy / 100.0) * graf->liczbaWezlow / liczbaCzesci);
    int minNaCzesc = floor((1.0 - marginesProcentowy / 100.0) * graf->liczbaWezlow / liczbaCzesci);

    for (int start = 0; start < graf->liczbaWezlow; start++) {
        if (!odwiedzone[start]) {
            // Kolejka do BFS
            int* kolejka = malloc(sizeof(int) * graf->liczbaWezlow);
            int przod = 0, tyl = 0;
            kolejka[tyl++] = start;

            while (przod < tyl) {
                int u = kolejka[przod++];
                if (odwiedzone[u]) continue;

                // Wybór najlepszej części dla danego węzła
                int najlepszaCzesc = -1;
                int maxSasiadowWTymSamym = -1;

                for (int cz = 0; cz < liczbaCzesci; cz++) {
                    if (rozmiaryCzesci[cz] >= maksNaCzesc) continue;

                    int sasiadow = 0;
                    for (int i = 0; i < graf->wezly[u].liczbaWezlowPowiazanych; i++) {
                        int v = graf->wezly[u].listaPowiazan[i];
                        if (odwiedzone[v] && przypisania[v] == cz) {
                            sasiadow++;
                        }
                    }
                    if (sasiadow > maxSasiadowWTymSamym || (sasiadow == maxSasiadowWTymSamym && najlepszaCzesc == -1)) {
                        najlepszaCzesc = cz;
                        maxSasiadowWTymSamym = sasiadow;
                    }
                }

                if (najlepszaCzesc == -1) {
                    // Brak miejsca – szukaj czegokolwiek poniżej maksimum
                    for (int cz = 0; cz < liczbaCzesci; cz++) {
                        if (rozmiaryCzesci[cz] < maksNaCzesc) {
                            najlepszaCzesc = cz;
                            break;
                        }
                    }
                }

                if (najlepszaCzesc == -1) najlepszaCzesc = 0; // awaryjnie

                przypisania[u] = najlepszaCzesc;
                odwiedzone[u] = true;
                rozmiaryCzesci[najlepszaCzesc]++;

                // Dodaj sąsiadów do kolejki
                for (int i = 0; i < graf->wezly[u].liczbaWezlowPowiazanych; i++) {
                    int v = graf->wezly[u].listaPowiazan[i];
                    if (!odwiedzone[v]) {
                        kolejka[tyl++] = v;
                    }
                }
            }

            free(kolejka);
        }
    }

    free(odwiedzone);
    free(rozmiaryCzesci);
}