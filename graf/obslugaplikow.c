#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "graf.h"


#define MAKS_ITERACJI 100

int PoliczElementy(char* bufor)
{
    int licznik = 0;
    for (int i = 0; bufor[i] != '\0'; i++)
    {
        if (bufor[i] == ';' || bufor[i] == '\n')
            licznik++;
    }
    return licznik;
}

int KonwertujElement(char* bufor, int* element)
{
    int val, result = 0;
    if (element)
    {

        result = sscanf(bufor, "%d", &val);
        if (result == 1)
        {
            *element = val;
        }
    }
    return result;
}

void DumpTable(Graf* graf)
{
    for (int y = 0; y < graf->liczbaWierszy; y++)
    {
        for (int x = 0; x < graf->liczbaKolumn; x++)
        {
/*            if (graf->tablicaWezlow[y * x] != NULL)
                printf("1");
            else printf("0");
 */
            if (graf->tablicaWezlow[y*graf->liczbaKolumn + x]==-1)
                printf("0");
            else printf("1");
        }
          printf("\n");
    }

}

Graf* wczytajGraf(const char* nazwaPliku)
{
    char bufor[1000];
    char bufor2[1000];
    char workbuf[10];
    int a, b, val;
    int result;

    FILE* plik = fopen(nazwaPliku, "r");
    if (plik)
    {

        Graf* graf = (Graf*)malloc(sizeof(Graf));
        if (graf)
        {

            fscanf(plik, "%d\n", &graf->liczbaKolumn);
            fgets(bufor, sizeof(bufor), plik);
            fgets(bufor2, sizeof(bufor2), plik);

            graf->liczbaWezlow = PoliczElementy(bufor);
            graf->wezly = calloc(1, graf->liczbaWezlow * sizeof(Wezel));
            if (graf->wezly)
            {
                int cnt = 0;
                int index = 0;

                for (int i = 0;bufor[i] != '\0';i++)
                {
                    if (bufor[i] == ';' || bufor[i] == '\n')
                    {
                        workbuf[cnt] = '\0';
                        cnt = 0;
                        result = KonwertujElement(workbuf, &val);
                        graf->wezly[index++].kolumna = val;
                    } else workbuf[cnt++] = bufor[i];
                }

                graf->liczbaWierszy = PoliczElementy(bufor2) - 1;
                printf("wiersze: %d\n", graf->liczbaWierszy);
                printf("kolumny: %d\n", graf->liczbaKolumn);
                printf("wezly: %d\n", graf->liczbaWezlow);

                graf->tablicaWezlow = malloc(graf->liczbaKolumn * graf->liczbaWierszy * sizeof(int));
                if (graf->tablicaWezlow)
                {
                    int firstLoop = 1;
                    int row = 0;
                    cnt = 0;
                    memset(graf->tablicaWezlow, -1, graf->liczbaKolumn * graf->liczbaWierszy * sizeof(int));
                    for (int i = 0;bufor2[i] != '\0';i++)
                    {
                        if (bufor2[i] == ';' || bufor2[i] == '\n')
                        {
                            workbuf[cnt] = '\0';
                            cnt = 0;
                            if (firstLoop)
                            {
                                result = KonwertujElement(workbuf, &a);
                                firstLoop = 0;
                            } else
                            {
                                result = KonwertujElement(workbuf, &b);
                                printf("wiersz %d, Wezly %d - %d\n", row, a, b);
                                for (index = a; index < b; index++)
                                {
                                    graf->wezly[index].wiersz = row;
                                    graf->tablicaWezlow[graf->wezly[index].wiersz * graf->liczbaKolumn + graf->wezly[index].kolumna] = index;
                                    printf("wiersz %d, kolumna: %d, index: %d\n", graf->wezly[index].wiersz, graf->wezly[index].kolumna, index);
                                }
                                a = b;
                                row++;
                            }
                        } else workbuf[cnt++] = bufor2[i];
                    }
                    DumpTable(graf);
                    fgets(bufor, sizeof(bufor), plik);
                    fgets(bufor2, sizeof(bufor2), plik);
                    int edgesCount = PoliczElementy(bufor);
                    int* edges = calloc(1, edgesCount * sizeof(int));
                    if (edges)
                    {
                        int cnt = 0;
                        int index = 0;
                        int firstLoop = 1;
                        int edgeIndex = 0;
                        Wezel* wezel;

                        for (int i = 0; bufor[i] != '\0'; i++)
                        {
                            if (bufor[i] == ';' || bufor[i] == '\n')
                            {
                                workbuf[cnt] = '\0';
                                cnt = 0;
                                result = KonwertujElement(workbuf, &val);
                                edges[index++] = val;
                            } else workbuf[cnt++] = bufor[i];
                        }
                        workbuf[0] = '\0';
                        int i = 0;
                        do 
                        {
                            if (bufor2[i] == ';' || bufor2[i] == '\0')
                            {
                                workbuf[cnt] = '\0';
                                cnt = 0;
                                if (firstLoop)
                                {
                                    result = KonwertujElement(workbuf, &a);
                                    firstLoop = 0;
                                } else
                                {
                                    result = KonwertujElement(workbuf, &b);
                                    wezel = &graf->wezly[edges[a]];
                                    printf(" wezel %d, Wezly %d - %d\n", edges[a], a, b);
                                    wezel->listaPowiazan = malloc((b - a - 1) * sizeof(int));
                                    a++;
                                    edgeIndex = 0;
                                    for (index = a; index < b; index++)
                                    {
                                        wezel->listaPowiazan[edgeIndex++] = edges[index];
                                    }
                                    a = b;
                                }
                            } else workbuf[cnt++] = bufor2[i];
                        } while (bufor2[i++] != '\0');
                        free(edges);
                        return graf;
                    } else printf("Blad: Nie udalo sie zaalokowac pamieci dla grafu.\n");
                    free(graf->tablicaWezlow);
                } else printf("Blad: Nie udalo sie zaalokowac pamieci dla tablicy wezlow.\n");
                free(graf->wezly);
            } else printf("Blad: Nie udalo sie zaalokowac pamieci dla wezlow.\n");
            free(graf);
        } else printf("Blad: Nie udalo sie zaalokowac pamieci dla grafu.\n");
        fclose(plik);
    } else printf("Blad: Nie mozna otworzyc pliku %s\n", nazwaPliku);
    return NULL;
}



void zapiszGraf(const char* nazwaPliku, Graf* graf) {
    FILE* plik = fopen(nazwaPliku, "w");
    if (!plik) {
        printf("Blad: Nie mozna otworzyc pliku %s do zapisu.\n", nazwaPliku);
        return;
    }

    // Zapis maksymalnej liczby węzłów w wierszu
    fprintf(plik, "%d\n", graf->liczbaKolumn);

    

    fclose(plik);
    printf("Graf zostal zapisany do pliku %s.\n", nazwaPliku);
}
    /*void saveText(const char* nazwaPliku, const Graf* graf) {
    FILE* plik = fopen(nazwaPliku, "w");
    if (!plik) {
        printf("Błąd: Nie można otworzyć pliku do zapisu %s\n", nazwaPliku);
        return;
    }

    // Zapis liczby kolumn i wierszy
    fprintf(plik, "%d\n", graf->liczbaKolumn);
    fprintf(plik, "%d\n", graf->liczbaWierszy);

    // Zapis połączeń między węzłami
    for (int i = 0; i < graf->liczbaWierszy; i++) {
        fprintf(plik, "%d %d\n", graf->tablicaWezlow[i].a, graf->tablicaWezlow[i].b);
    }

    fclose(plik);
    printf("Graf został zapisany do pliku tekstowego: %s\n", nazwaPliku);
}

void saveBin(const char* nazwaPliku, const Graf* graf) {
    FILE* plik = fopen(nazwaPliku, "wb");
    if (!plik) {
        printf("Błąd: Nie można otworzyć pliku binarnego do zapisu %s\n", nazwaPliku);
        return;
    }

    fwrite(&graf->liczbaKolumn, sizeof(int), 1, plik);
    fwrite(&graf->liczbaWierszy, sizeof(int), 1, plik);
    fwrite(graf->tablicaWezlow, sizeof(wezel), graf->liczbaWierszy, plik);

    fclose(plik);
    printf("Graf został zapisany do pliku binarnego: %s\n", nazwaPliku);
}
}
*/




