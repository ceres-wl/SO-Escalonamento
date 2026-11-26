#include "eviccao.h"

int selecionar_frame(ALGORITHM algo, GerenciadorMemoria& gerenciador, vector<PairIB>& trace, int idx_atual) {
    switch(algo){
        case FIFO:
            return fifo(gerenciador);
        case LRU:
            return lru(gerenciador);
        case OTIMO:
            return otimo(gerenciador, trace, idx_atual);
        case CLOCK:
            return clock(gerenciador);
        case NRU:
            return nru(gerenciador);
        case LFU:
            return lfu(gerenciador);
        case MFU:
            return mfu(gerenciador);
    }
}