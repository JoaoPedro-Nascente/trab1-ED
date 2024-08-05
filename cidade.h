#ifndef _CIDADE_H_
#define _CIDADE_H_

#include <stdio.h>

typedef struct cidade Cidade;

Cidade *cidade_construct(FILE *fp);
char *cidade_get_nome(Cidade *c);
int cidade_get_nVizinhos(Cidade *c);
void cidade_destroy(void *c);

void bfs_search(int partida, int destino, FILE *fp);
void dfs_search(int partida, int destino, FILE *fp);
void ucs_search(int partida, int destino, FILE *fp);
void astar_search(int partida, int destino, FILE *fp);

#endif