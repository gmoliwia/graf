#include <stdio.h>
#include <stdlib.h>
#include "graf.h"
#include<stdio.h>
#include <stdlib.h>
#include<math.h>

int main(int argc, char * argv[])
{
    char* nazwa_pliku;
    int liczbaPodzialow = 2;
    double margines = 10.0;
    int typ_zapisu = 0;

    if (argc < 2)
    {
        printf("Nieprawidłowa liczba argumentów wywołania. Spróbuj ponownie: <nazwa_pliku>  <format_pliku_zapisu> <ilośc_podziałów> <margines> \n ");
        return 1;
    }
    nazwa_pliku = argv[1];

    if (argc > 2)
    {
        typ_zapisu = atoi(argv[2]);
        if (typ_zapisu != 0 && typ_zapisu != 1)
        {
            printf("Nieprawidłowy typ pliku. Spróbuj ponownie 0 - plik tekstowy, 1 - plik binarny\n");
            return 1;
        }
    }
    if (argc > 3)
    {
        liczbaPodzialow = atoi(argv[3]);
        if (liczbaPodzialow < 0)
        {
            printf("Nieprawidłowa liczba podziałów\n");
            return 1;
        }
    }
    if (argc > 4)
    {
        margines = atof(argv[4]);
        if (margines < 0.0 || margines>100.0)
        {
            printf("Nieprawidłowa wartość marginesu. Spróbuj wpisać liczbę między 0 a 100\n");
            return 1;
        }
    }

    Graf* graf = wczytajGraf(nazwa_pliku); 
    if (!graf) {
        printf("Nie udało się wczytać grafu.\n");
        return 1;
    }
     if (liczbaPodzialow > graf->liczbaWezlow)
    {
        printf("Nieprawidłowa liczba podziałów\n");
        return 1;
    }
     //zapiszGraf("podzielony2.txt", graf, 1, NULL);

    int* przypisania = malloc(sizeof(int) * graf->liczbaWezlow); 
    if (!przypisania) {
        printf("Blad alokacji przypisan.\n");
        return 1;
    }
    for (int i = 0; i < graf->liczbaWezlow; i++) przypisania[i] = -1; 

    podzielGrafBFSZaawansowany(graf, liczbaPodzialow, margines, przypisania);  

   
    for (int i = 0; i < graf->liczbaWezlow; i++) {
        printf("Wezel %d przypisany do czesci %d\n", i, przypisania[i]);
    }
    if (typ_zapisu == 0)
    {
        zapiszGraf("podzielonygraf.txt", graf, liczbaPodzialow, przypisania);
    }
    else
    {
        zapiszGrafBin("podzielonygraf.bin", graf, liczbaPodzialow, przypisania);
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