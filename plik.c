#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

typedef struct{
    int u, v;
}Edge;

typedef struct{
    int numNodes, numEdges;
    Edge edges[MAX_NODES * MAX_NODES]; //Liczba krawędzi
}Graph;

Graph readFile (const char *input){
    Graph g;
    FILE *file = fopen(input, "r");
    if(file == NULL){
        perror("Nie można otworzyć pliku\n");
        return;
    }

    fprintf(file, "%d %d\n", g.numNodes, g.numEdges);
    for (int i = 0; i < g.numEdges; i++) {
        fprintf(file, "%d %d\n", g.edges[i].u, g.edges[i].v);
    }
    fclose(file);
}