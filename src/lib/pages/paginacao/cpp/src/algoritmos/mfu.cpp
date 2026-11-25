#include "eviccao.h"

int mfu(GerenciadorMemoria& gerenciador){
    vector<Frame>& v = gerenciador.frames;
    int escolhido = 0;

    for(int i = 1; i < v.size(); i++){
        if(v[i].quant_acessos > v[escolhido].quant_acessos || 
        (v[i].quant_acessos == v[escolhido].quant_acessos && v[i].entrada < v[escolhido].entrada))
            escolhido = i;
    }
    return escolhido;
}