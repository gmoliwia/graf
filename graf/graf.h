#pragma once
typedef struct
{
    int liczbaWierszy;
    int liczbaKolumn;
    int liczbaWezlow;
    struct wezel* tablicaWezlow;
} Graf;

typedef struct
{
    int numer;
    struct wezel* lista;
} wezel;

Graf * wczytajGraf(const char* nazwaPliku);

