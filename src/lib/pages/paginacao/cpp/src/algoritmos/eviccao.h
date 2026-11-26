#ifndef PAGER_H
#define PAGER_H

#include "../estruturas.h"

//retorna o indice do frame escolhido
int selecionar_frame(ALGORITHM algo, GerenciadorMemoria &gerenciador, vector<PairIB>& trace, int idx_atual);

int fifo(GerenciadorMemoria& gerenciador);
int lru(GerenciadorMemoria& gerenciador);
int otimo(GerenciadorMemoria& gerenciador, vector<PairIB>& trace, int idx_atual);
int clock(GerenciadorMemoria& gerenciador);
int nru(GerenciadorMemoria& gerenciador);
int lfu(GerenciadorMemoria& gerenciador);
int mfu(GerenciadorMemoria& gerenciador);

#endif