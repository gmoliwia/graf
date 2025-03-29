#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 6000
#define MAX 1000000

int main(int argc, char** argv){

    FILE *file = fopen(input, "r");
    if(input == NULL){
        perror("Nie można otworzyć pliku\n");
    exit(1);
    }
    fclose(file);
}