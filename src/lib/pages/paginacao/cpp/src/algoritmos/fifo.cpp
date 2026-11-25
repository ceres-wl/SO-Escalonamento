#include "pager.h"

int fifo(GerenciadorMemoria& gerenciador){
    const vector<Frame>& v = gerenciador.frames;
    int escolhido = 0;

    for(int i = 1; i < v.size(); i++){
        if(v[i].entrada < v[escolhido].entrada)
            escolhido = i;
    }
    return escolhido;
}