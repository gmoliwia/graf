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
            if (fscanf(plik, "%d\n", &graf->liczbaKolumn) == 1)
            {
                if (fgets(bufor, sizeof(bufor), plik) && fgets(bufor2, sizeof(bufor2), plik))
                {
                    graf->liczbaWezlow = PoliczElementy(bufor);
                    graf->wezly = calloc(graf->liczbaWezlow, sizeof(Wezel));
                    if (graf->wezly)
                    {
                        int cnt = 0;
                        int index = 0;
                        for (int i = 0; bufor[i] != '\0'; i++)
                        {
                            if (bufor[i] == ';' || bufor[i] == '\n')
                            {
                                workbuf[cnt] = '\0';
                                cnt = 0;
                                result = KonwertujElement(workbuf, &val);
                                graf->wezly[index++].kolumna = val;
                            } else
                            {
                                workbuf[cnt++] = bufor[i];
                            }
                        }

                        graf->liczbaWierszy = PoliczElementy(bufor2) - 1;
                        printf("wiersze: %d\n", graf->liczbaWierszy);
                        printf("kolumny: %d\n", graf->liczbaKolumn);
                        printf("wezly: %d\n", graf->liczbaWezlow);

                        graf->tablicaWezlow = malloc(graf->liczbaKolumn * graf->liczbaWierszy * sizeof(int));
                        if (graf->tablicaWezlow)
                        {
                            memset(graf->tablicaWezlow, -1, graf->liczbaKolumn * graf->liczbaWierszy * sizeof(int));
                            int firstLoop = 1;
                            int row = 0;
                            cnt = 0;

                            for (int i = 0; bufor2[i] != '\0'; i++)
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
                                } else
                                {
                                    workbuf[cnt++] = bufor2[i];
                                }
                            }

                            DumpTable(graf);
                            // wczytaj krawędzie
                            if (fgets(bufor, sizeof(bufor), plik) && fgets(bufor2, sizeof(bufor2), plik))
                            {
                                int edgesCount = PoliczElementy(bufor);
                                int* edges = calloc(edgesCount, sizeof(int));
                                if (edges)
                                {
                                    cnt = 0;
                                    index = 0;
                                    for (int i = 0; bufor[i] != '\0'; i++)
                                    {
                                        if (bufor[i] == ';' || bufor[i] == '\n')
                                        {
                                            workbuf[cnt] = '\0';
                                            cnt = 0;
                                            result = KonwertujElement(workbuf, &val);
                                            edges[index++] = val;
                                        } else
                                        {
                                            workbuf[cnt++] = bufor[i];
                                        }
                                    }

                                    workbuf[0] = '\0';
                                    int i = 0;
                                    cnt = 0;
                                    int firstLoop = 1;
                                    int edgeIndex = 0;
                                    Wezel* wezel;
                                    int fail = 0;
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
                                                printf("wezel %d, Wezly %d - %d\n", edges[a], a, b);
                                                wezel->liczbaWezlowPowiazanych = b - a - 1;
                                                wezel->listaPowiazan = malloc(wezel->liczbaWezlowPowiazanych * sizeof(int));
                                                if (wezel->listaPowiazan)
                                                {
                                                    a++;
                                                    edgeIndex = 0;
                                                    for (index = a; index < b; index++)
                                                    {
                                                        wezel->listaPowiazan[edgeIndex++] = edges[index];
                                                    }
                                                    a = b;
                                                } else
                                                {
                                                    printf("Blad: Nie udalo sie zaalokowac pamieci dla listy powiazan.\n");
                                                    fail = 1;
                                                    // TODO: dodac zwalnianie listypowiazan dla wszystkich wezlow
                                                    break;
                                                }
                                            }
                                        } else
                                        {
                                            workbuf[cnt++] = bufor2[i];
                                        }
                                    } while (bufor2[i++] != '\0');
                                    free(edges);
                                    if (!fail)
                                    {
                                        fclose(plik);
                                        return graf;
                                    }
                                } else printf("Blad: Nie udalo sie zaalokowac pamieci dla krawedzi.\n");
                            } else printf("Blad: Brak danych o krawedziach.\n");
                            free(graf->tablicaWezlow);
                        } else printf("Blad: Nie udalo sie zaalokowac pamieci dla tablicy wezlow.\n");
                        free(graf->wezly);
                    } else printf("Blad: Nie udalo sie zaalokowac pamieci dla wezlow.\n");
                } else printf("Blad: Nieprawidlowy format danych.\n");
            } else printf("Blad: Nieprawidlowy format pliku.\n");
            free(graf);
        } else printf("Blad: Nie udalo sie zaalokowac pamieci dla grafu.\n");
        fclose(plik);
    } else printf("Blad: Nie mozna otworzyc pliku %s\n", nazwaPliku);
    return NULL;
}



void zapiszGraf(const char* nazwaPliku, Graf* graf,  int liczbaPodzialow, int* przypisania)
{
    FILE* plik = fopen(nazwaPliku, "w");
    if (plik)
    {

  
        fprintf(plik, "%d\n", graf->liczbaKolumn);

        for (int i = 0; i < graf->liczbaWezlow; i++)
        {
            fprintf(plik, "%d", graf->wezly[i].kolumna);
            if (i < graf->liczbaWezlow - 1)
            {
                fprintf(plik, ";");
            }
        }
        fprintf(plik, "\n");

  
        int previousIndex = 0;
        int currentIndex = 0;
        for (int i = 0; i < graf->liczbaWierszy; i++)
        {
            for (int j = 0; j < graf->liczbaKolumn; j++)
            {
                int index = i * graf->liczbaKolumn + j;
                if (graf->tablicaWezlow[index] != -1)
                {
                    currentIndex = graf->tablicaWezlow[index] + 1;
                }
            }
            fprintf(plik, "%d;", previousIndex);
            previousIndex = currentIndex;
        }
        fprintf(plik, "%d\n", previousIndex);

   
        for (int i = 0; i < graf->liczbaWezlow; i++)
        {
            if (graf->wezly[i].liczbaWezlowPowiazanych>0)
                fprintf(plik, "%d;", i);
            for (int j = 0; j < graf->wezly[i].liczbaWezlowPowiazanych; j++)
            {
                fprintf(plik, "%d", graf->wezly[i].listaPowiazan[j]);

                {
                    fprintf(plik, ";");
                }
            }
        }
        fprintf(plik, "\n");

    
        if (przypisania)
        {
            for (int a = 0; a < liczbaPodzialow;a++)
            {
                int edgeIndex = 0;

                for (int i = 0; i < graf->liczbaWezlow; i++)
                {
                    if (przypisania[i] == a)
                    {
                        if (graf->wezly[i].listaPowiazan)
                        {
                            fprintf(plik, "%d;", edgeIndex);
                            edgeIndex += graf->wezly[i].liczbaWezlowPowiazanych + 1;
                        }
                    }
                }
                fprintf(plik, "%d\n", edgeIndex);
            }
        } else
        {
            int edgeIndex = 0;
            for (int i = 0; i < graf->liczbaWezlow; i++)
            {
                if (graf->wezly[i].listaPowiazan)
                {
                    fprintf(plik, "%d;", edgeIndex);
                    edgeIndex += graf->wezly[i].liczbaWezlowPowiazanych + 1;
                }
            }
            fprintf(plik, "%d\n", edgeIndex);
        }

        fclose(plik);
        printf("Graf zostal zapisany do pliku %s.\n", nazwaPliku);
    } else printf("Blad: Nie mozna otworzyc pliku %s do zapisu.\n", nazwaPliku);
}




void zapiszGrafBin(const char* nazwaPliku, Graf* graf, int liczbaPodzialow, int* przypisania)
{

}
