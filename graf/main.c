#include <stdio.h>
#include <stdlib.h>
#include "graf.h"
int main(int argc, char*argv[])
{

   
	Graf* graf = wczytajGraf("graftestsigma.txt");

    printf("Wczytano graf z pliku\n");

 

    // Parametry podziału
    int LiczbaPodzialow = 3; // Podział na 3 części
    int margines = 10;       // Margines 10%

    // Podział grafu

    // Zapis grafu do pliku
    zapiszGraf("podzielony_graf.txt", podzielonyGraf);
    printf("Podzielony graf zostal zapisany do pliku: %s\n", "podzielony_graf.txt");

     zapiszGraf("test1.txt", graf);

    // Czyszczenie pamięci
    free(graf->wezly);
    free(graf);
    free(podzielonyGraf->wezly);
    free(podzielonyGraf);

  
    

    return 0;
}


