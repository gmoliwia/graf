#include <stdio.h>
#include <stdlib.h>

void readFile (const char *input, int isBinary){
    FILE *file = fopen(input, isBinary? "rb" : "r");
    if(file == NULL){
        perror("Nie można otworzyć pliku\n");
        return;
    }
    fclose(file);
}