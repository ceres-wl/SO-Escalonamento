#include "pager.h"

int lru(GerenciadorMemoria& gerenciador){
    const vector<Frame>& v = gerenciador.frames;
    int escolhido = 0;

    for(int i = 1; i < v.size(); i++){
        if(v[i].ultimo_acesso < v[escolhido].ultimo_acesso)
            escolhido = i;
    }
    return escolhido;
}