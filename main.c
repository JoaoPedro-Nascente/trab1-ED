#include <stdio.h>
#include <string.h>

#include "cidade.h"

int main()
{
    char caminho[100];
    char busca[10];
    int partida;
    int destino;
    scanf("%s\n", caminho);

    FILE *file = fopen(caminho, "r");

    fgets(busca, sizeof(busca), file);
    fscanf(file, "%d %d", &partida, &destino);

    if (strcmp(busca, "BFS") == 0)
        bfs_search(partida, destino, file);
    if (strcmp(busca, "DFS") == 0)
        dfs_search(partida, destino, file);
    if (strcmp(busca, "UCS") == 0)
        ucs_search(partida, destino, file);
    if (strcmp(busca, "A*") == 0)
        astar_search(partida, destino, file);

    fclose(file);
    return 0;
}