#include "cidade.h"
#include "vector.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_TAM_NOME 64

typedef struct coordenadas
{
    int x;
    int y;
} Coordenadas;

struct cidade
{
    char *nome;
    Coordenadas coord;
    int nVizinhos;
    int index;
    int *vizinhos;
    int *distVizinhos;
    void *vizinhosDataStructure;
    void (*element_free)(void *);
};

Cidade *cidade_construct()
{
    int index;
    Coordenadas coord;
    int nVizinhos;
    char nome[MAX_TAM_NOME];

    scanf("%d %s %d %d %d", &index, nome, &coord.x, &coord.y, &nVizinhos);

    int vizinhos[nVizinhos];
    int distVizinhos[nVizinhos];
    for (int i = 0; i < nVizinhos; i++)
    {
        scanf("%d %d", &vizinhos[i], &distVizinhos[i]);
    }

    Cidade *cidade = (Cidade *)malloc(sizeof(Cidade));

    cidade->index = index;
    cidade->coord = coord;
    cidade->nVizinhos = nVizinhos;
    cidade->nome = (char *)malloc(sizeof(char) * MAX_TAM_NOME);
    strcpy(cidade->nome, nome);
    cidade->vizinhos = vizinhos;
    cidade->distVizinhos = distVizinhos;

    return cidade;
}

char *cidade_get_nome(Cidade *c)
{
    return c->nome;
}

int cidade_get_nVizinhos(Cidade *c)
{
    return c->nVizinhos;
}

void cidade_destroy(Cidade *c)
{
    free(c->nome);
    if (c->vizinhosDataStructure != NULL)
    {
        c->element_free(c->vizinhosDataStructure);
    }

    free(c);
}

void bfs_search(int partida, int destino)
{
    int nCidades;
    scanf("%d", &nCidades);

    for (int i = 0; i < nCidades; i++)
    {
    }
}

void dfs_search(int partida, int destino);
void ucs_search(int partida, int destino);
void astar_search(int partida, int destino);