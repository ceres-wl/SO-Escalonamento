#include "eviccao.h"

int clock(GerenciadorMemoria& gerenciador){
    vector<Frame>& v = gerenciador.frames;
    int escolhido;

    for(int i = 0 ; i < v.size() + 1 ; i++){
        int idx = (i + gerenciador.ponteiro_clock) % v.size();
        if(v[idx].bit_r == 0){
            gerenciador.ponteiro_clock = (idx + 1) % v.size();
            escolhido = idx;
            break;
        }
        else v[idx].bit_r = 0;
    }
    return escolhido;
}