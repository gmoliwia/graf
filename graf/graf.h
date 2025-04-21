typedef struct Wezel
{
    int numer;
    int wiersz, kolumna;
    int liczbaWezlowPowiazanych;
    int* listaPowiazan;
} Wezel;

typedef struct
{
    int liczbaWezlow;
    struct Wezel* wezly;
    int liczbaWierszy;
    int liczbaKolumn;
    int* tablicaWezlow;
} Graf;


Graf * wczytajGraf(const char* nazwaPliku);

