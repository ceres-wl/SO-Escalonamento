#ifndef PAGER_H
#define PAGER_H

#include "../estruturas.h"

//retorna o indice do frame escolhido
int selecionar_frame(ALGORITHM algo, GerenciadorMemoria &gerenciador, vector<pair<int, bool>>& trace, int idx_atual);

int fifo(GerenciadorMemoria& gerenciador);
int lru(GerenciadorMemoria& gerenciador);
int otimo(GerenciadorMemoria& gerenciador, vector<pair<int, bool>>& trace, int idx_atual);

#endif