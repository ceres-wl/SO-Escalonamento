#include "eviccao.h"

int nru(GerenciadorMemoria& gerenciador){
    vector<Frame>& v = gerenciador.frames;
    int escolhido = 0;
    int menor_classe = 2*v[0].bit_r + v[0].bit_m;

    for(int i = 1 ; i < v.size() ; i++){
        int classe_atual = 2 * v[i].bit_r + v[i].bit_m;
        if(classe_atual < menor_classe ||
        (classe_atual == menor_classe && v[i].entrada < v[escolhido].entrada)){
            escolhido = i;
            menor_classe = classe_atual;
        }
    }
    return escolhido;
}