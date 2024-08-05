#include "cidade.h"
#include "vector.h"
#include "circular_array.h"
#include "min_heap.h"
#include "queue.h"
#include "stack.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

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
    float *distVizinhos;
    void *vizinhosDataStructure;
    void (*element_free)(void *);
};

Cidade *cidade_construct(FILE *fp)
{
    int index;
    Coordenadas coord;
    int nVizinhos;
    char nome[MAX_TAM_NOME];

    fscanf(fp, "%d %s %d %d %d", &index, nome, &coord.x, &coord.y, &nVizinhos);

    int *vizinhos = (int *)malloc(nVizinhos * sizeof(int));
    float *distVizinhos = (float *)malloc(nVizinhos * sizeof(float));

    for (int i = 0; i < nVizinhos; i++)
    {
        fscanf(fp, "%d %f", &vizinhos[i], &distVizinhos[i]);
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

void cidade_destroy(void *c)
{
    Cidade *cidade = (Cidade *)c;
    free(cidade->nome);
    if (cidade->vizinhosDataStructure != NULL)
    {
        cidade->element_free(cidade->vizinhosDataStructure);
    }
    free(cidade->distVizinhos);
    free(cidade->vizinhos);

    free(cidade);
}

void dfs_search(int partida, int destino, FILE *fp)
{
    int nCidades;
    fscanf(fp, "%d", &nCidades);

    Vector *cidades = vector_construct(nCidades);

    for (int i = 0; i < nCidades; i++)
    {
        vector_push_back(cidades, cidade_construct(fp));
    }

    Cidade *cidade;
    for (int i = 0; i < nCidades; i++)
    {
        cidade = vector_get(cidades, i);
        cidade->vizinhosDataStructure = stack_construct();
        cidade->element_free = stack_destroy;

        for (int j = 0; j < cidade->nVizinhos; j++)
        {
            stack_push(cidade->vizinhosDataStructure, vector_get(cidades, cidade->vizinhos[j]));
        }
    }

    int visitados[nCidades];
    memset(visitados, -1, sizeof(visitados));
    int nVisitados = 0;

    Stack *caminho = stack_construct();
    stack_push(caminho, vector_get(cidades, partida));

    while (!stack_is_empty(caminho))
    {
        cidade = stack_pop(caminho);

        if (visitados[cidade->index] == -1)
        {
            visitados[cidade->index] = 1;
            nVisitados++;

            if (cidade->index == destino)
                break;

            Stack *vizinhos = cidade->vizinhosDataStructure;
            while (!stack_is_empty(vizinhos))
            {
                Cidade *novaCidade = stack_pop(vizinhos);
                if (visitados[novaCidade->index] == -1)
                {
                    stack_push(caminho, novaCidade);
                }
            }
        }
    }

    Stack *caminhoFinal = stack_construct();
    while (!stack_is_empty(caminho))
    {
        stack_push(caminhoFinal, stack_pop(caminho));
    }
    stack_destroy(caminho);

    float custo = 0;
    cidade = stack_pop(caminhoFinal);
    printf("%s\n", cidade->nome);
    int index = cidade->index;
    cidade = stack_pop(caminhoFinal);
    while (!stack_is_empty(caminhoFinal))
    {
        printf("%s\n", cidade->nome);

        for (int i = 0; i < cidade->nVizinhos; i++)
        {
            if (cidade->vizinhos[i] == index)
            {
                custo += cidade->distVizinhos[i];
                break;
            }
        }
        index = cidade->index;

        cidade = stack_pop(caminhoFinal);
    }

    printf("Custo: %.2f Num_Expandidos: %d\n", custo, nVisitados);
    stack_destroy(caminhoFinal);
    vector_destroy(cidades, cidade_destroy);
}

void bfs_search(int partida, int destino, FILE *fp)
{
    int nCidades;
    fscanf(fp, "%d", &nCidades);

    Vector *cidades = vector_construct(nCidades);

    for (int i = 0; i < nCidades; i++)
    {
        vector_push_back(cidades, cidade_construct(fp));
    }

    Cidade *cidade;
    for (int i = 0; i < nCidades; i++)
    {
        cidade = vector_get(cidades, i);
        cidade->vizinhosDataStructure = queue_construct(cidade->nVizinhos);
        cidade->element_free = queue_destroy;

        for (int j = 0; j < cidade->nVizinhos; j++)
        {
            queue_enqueue(cidade->vizinhosDataStructure, vector_get(cidades, cidade->vizinhos[j]));
        }
    }

    int visitados[nCidades];
    for (int i = 0; i < nCidades; i++)
        visitados[i] = 0;
    int nVisitados = 0;

    Queue *caminho = queue_construct(nCidades);
    queue_enqueue(caminho, vector_get(cidades, partida));

    int found = 0;

    while (!queue_is_empty(caminho))
    {
        cidade = queue_dequeue(caminho);

        if (cidade->index == destino)
        {
            found = 1;
            break;
        }

        Queue *vizinhos = cidade->vizinhosDataStructure;
        Queue *auxQueue = queue_construct(queue_size(vizinhos));

        while (!queue_is_empty(vizinhos))
        {
            Cidade *novaCidade = queue_dequeue(vizinhos);
            queue_enqueue(auxQueue, novaCidade); // Restaurar vizinhos

            if (!visitados[novaCidade->index])
            {
                visitados[novaCidade->index] = 1;
                queue_enqueue(caminho, novaCidade);
                nVisitados++;
            }
        }

        // Restaura a fila de vizinhos
        while (!queue_is_empty(auxQueue))
        {
            queue_enqueue(vizinhos, queue_dequeue(auxQueue));
        }
        queue_destroy(auxQueue);
    }

    if (found)
    {
        // Caminho encontrado, processar resultado
        Queue *caminhoFinal = queue_construct(nCidades);
        while (!queue_is_empty(caminho))
        {
            queue_enqueue(caminhoFinal, queue_dequeue(caminho));
        }
        queue_destroy(caminho);

        float custo = 0;
        cidade = queue_dequeue(caminhoFinal);
        printf("%s\n", cidade->nome);
        int index = cidade->index;
        cidade = queue_dequeue(caminhoFinal);
        while (!queue_is_empty(caminhoFinal))
        {
            printf("%s\n", cidade->nome);

            for (int i = 0; i < cidade->nVizinhos; i++)
            {
                if (cidade->vizinhos[i] == index)
                {
                    custo += cidade->distVizinhos[i];
                    break;
                }
            }
            index = cidade->index;

            cidade = queue_dequeue(caminhoFinal);
        }

        printf("Custo: %.2f Num_Expandidos: %d\n", custo, nVisitados);
        queue_destroy(caminhoFinal);
    }
    else
    {
        // Caminho não encontrado
        printf("IMPOSSÍVEL\n");
    }

    queue_destroy(caminho);
    vector_destroy(cidades, cidade_destroy);
}

typedef struct
{
    Cidade *cidade;
    float custo;
    float heuristica;
} NodoAStar;

typedef struct
{
    Cidade *cidade;
    float custo;
} NodoUCS;

int compararNodosUCS(const void *a, const void *b)
{
    NodoUCS *nodoA = (NodoUCS *)a;
    NodoUCS *nodoB = (NodoUCS *)b;
    if (nodoA->custo < nodoB->custo)
        return -1;
    if (nodoA->custo > nodoB->custo)
        return 1;
    return 0;
}

void ucs_search(int partida, int destino, FILE *fp)
{
    int nCidades;
    fscanf(fp, "%d", &nCidades);

    Vector *cidades = vector_construct(nCidades);

    for (int i = 0; i < nCidades; i++)
    {
        vector_push_back(cidades, cidade_construct(fp));
    }

    Cidade *cidade;
    for (int i = 0; i < nCidades; i++)
    {
        cidade = vector_get(cidades, i);
        cidade->vizinhosDataStructure = min_heap_construct(compararNodosUCS);
        cidade->element_free = min_heap_destroy;

        for (int j = 0; j < cidade->nVizinhos; j++)
        {
            NodoUCS novoNodo = {vector_get(cidades, cidade->vizinhos[j]), cidade->distVizinhos[j]};
            min_heap_insert(cidade->vizinhosDataStructure, &novoNodo);
        }
    }

    int visitados[nCidades];
    for (int i = 0; i < nCidades; i++)
        visitados[i] = 0;
    int nVisitados = 0;

    MinHeap *caminho = min_heap_construct(compararNodosUCS);
    Cidade *cidadePartida = vector_get(cidades, partida);
    NodoUCS partidaNodo = {cidadePartida, 0};
    min_heap_insert(caminho, &partidaNodo);

    float custoTotal = 0;
    NodoUCS atual;

    while (!min_heap_is_empty(caminho))
    {
        atual = *(NodoUCS *)min_heap_extract_min(caminho);
        cidade = atual.cidade;

        if (visitados[cidade->index])
            continue;
        visitados[cidade->index] = 1;
        nVisitados++;
        custoTotal = atual.custo;

        if (cidade->index == destino)
            break;

        for (int i = 0; i < cidade->nVizinhos; i++)
        {
            Cidade *vizinho = vector_get(cidades, cidade->vizinhos[i]);
            if (!visitados[vizinho->index])
            {
                float novoCusto = custoTotal + cidade->distVizinhos[i];
                NodoUCS novoNodo = {vizinho, novoCusto};
                min_heap_insert(caminho, &novoNodo);
            }
        }
    }

    if (cidade->index == destino)
    {
        printf("Custo: %.2f Num_Expandidos: %d\n", custoTotal, nVisitados);
    }
    else
    {
        printf("IMPOSSÍVEL\n");
    }

    min_heap_destroy(caminho);
    vector_destroy(cidades, cidade_destroy);
}

int compararNodosAStar(const void *a, const void *b)
{
    NodoAStar *nodoA = (NodoAStar *)a;
    NodoAStar *nodoB = (NodoAStar *)b;
    float fA = nodoA->custo + nodoA->heuristica;
    float fB = nodoB->custo + nodoB->heuristica;
    if (fA < fB)
        return -1;
    if (fA > fB)
        return 1;
    return 0;
}

float calcularHeuristica(Coordenadas a, Coordenadas b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void astar_search(int partida, int destino, FILE *fp)
{
    int nCidades;
    fscanf(fp, "%d", &nCidades);

    Vector *cidades = vector_construct(nCidades);

    for (int i = 0; i < nCidades; i++)
    {
        vector_push_back(cidades, cidade_construct(fp));
    }

    Cidade *cidade;
    for (int i = 0; i < nCidades; i++)
    {
        cidade = vector_get(cidades, i);
        cidade->vizinhosDataStructure = min_heap_construct(compararNodosAStar);
        cidade->element_free = min_heap_destroy;

        for (int j = 0; j < cidade->nVizinhos; j++)
        {
            float heuristica = calcularHeuristica(((Cidade *)vector_get(cidades, cidade->vizinhos[j]))->coord, ((Cidade *)vector_get(cidades, destino))->coord);
            NodoAStar novoNodo = {vector_get(cidades, cidade->vizinhos[j]), cidade->distVizinhos[j], heuristica};
            min_heap_insert(cidade->vizinhosDataStructure, &novoNodo);
        }
    }

    int visitados[nCidades];
    for (int i = 0; i < nCidades; i++)
        visitados[i] = 0;
    int nVisitados = 0;

    MinHeap *caminho = min_heap_construct(compararNodosAStar);
    Cidade *cidadePartida = vector_get(cidades, partida);
    Cidade *cidadeDestino = vector_get(cidades, destino);
    NodoAStar partidaNodo = {cidadePartida, 0, calcularHeuristica(cidadePartida->coord, cidadeDestino->coord)};
    min_heap_insert(caminho, &partidaNodo);

    float custoTotal = 0;
    NodoAStar atual;

    while (!min_heap_is_empty(caminho))
    {
        atual = *(NodoAStar *)min_heap_extract_min(caminho);
        cidade = atual.cidade;

        if (visitados[cidade->index])
            continue;
        visitados[cidade->index] = 1;
        nVisitados++;
        custoTotal = atual.custo;

        if (cidade->index == destino)
            break;

        MinHeap *vizinhos = cidade->vizinhosDataStructure;
        while (!min_heap_is_empty(vizinhos))
        {
            NodoAStar *vizinho = (NodoAStar *)min_heap_extract_min(vizinhos);
            if (!visitados[vizinho->cidade->index])
            {
                float novaHeuristica = calcularHeuristica(vizinho->cidade->coord, cidadeDestino->coord);
                NodoAStar novoNodo = {
                    vizinho->cidade,
                    custoTotal + vizinho->custo,
                    novaHeuristica};
                min_heap_insert(caminho, &novoNodo);
            }
        }
    }

    if (cidade->index == destino)
    {
        printf("Custo: %.2f Num_Expandidos: %d\n", custoTotal, nVisitados);
    }
    else
    {
        printf("IMPOSSÍVEL\n");
    }

    min_heap_destroy(caminho);
    vector_destroy(cidades, cidade_destroy);
}