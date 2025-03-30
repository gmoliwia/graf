#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "graf.h"


#define MAKS_ITERACJI 100




Graf* wczytajGraf(const char* nazwaPliku)
{
    char bufor[1000];
    char bufor2[1000];
    char bufor3[1000];
    char bufor4[1000];
    int a, b, indeks;
    int licznik = 0;

    FILE* plik = fopen(nazwaPliku, "r");
    if (!plik) {
        printf("Błąd: Nie można otworzyć pliku %s\n", nazwaPliku);
        exit(EXIT_FAILURE);
    }

    Graf* graf = (Graf*)malloc(sizeof(Graf));
    if (!graf) {
        printf("Błąd: Nie udało się zaalokować pamięci dla grafu.\n");
        fclose(plik);
        return NULL;
    }

    fscanf(plik, "%d\n", &graf->liczbaKolumn);
    fgets(bufor, sizeof(bufor), plik);
    fgets(bufor2, sizeof(bufor2), plik);
    fgets(bufor3, sizeof(bufor3), plik);
    fgets(bufor4, sizeof(bufor4), plik);

    char buf[10];
    int parm = 0;
    int cnt = 0;
    int val;
    for (int i = 0;bufor2[i] != NULL;i++)
    {
        if (bufor2[i] == ';' || bufor2[i] == '\n')
        {
            cnt = 0;
            sscanf(buf, "%d", &val);
            if (parm == 0)
            {
                a = val;
                parm = 1;
            }  else
            {
                b = val;
                licznik++;
                //printf("Para %d: %d, %d\n", licznik, a, b);

                a = b;
            }
        } else buf[cnt++] = bufor2[i];

    }
    graf->liczbaWierszy = licznik;

    graf->tablicaWezlow = (wezel*)malloc(graf->liczbaWezlow * sizeof(wezel));

    printf("%d", licznik);
}

void saveText(const char* nazwaPliku, const Graf* graf) {
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
