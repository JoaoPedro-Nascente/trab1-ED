#ifndef _CIDADE_H_
#define _CIDADE_H_

typedef struct cidade Cidade;

Cidade *cidade_construct();
char *cidade_get_nome(Cidade *c);
int cidade_get_nVizinhos(Cidade *c);
void cidade_destroy(Cidade *c);

void bfs_search(int partida, int destino);
void dfs_search(int partida, int destino);
void ucs_search(int partida, int destino);
void astar_search(int partida, int destino);

#endif