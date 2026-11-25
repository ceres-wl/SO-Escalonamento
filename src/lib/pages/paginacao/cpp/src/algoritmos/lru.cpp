#include "eviccao.h"

int lru(GerenciadorMemoria& gerenciador){
    vector<Frame>& v = gerenciador.frames;
    int escolhido = 0;

    for(int i = 1; i < v.size(); i++){
        //2 acessos nao podem ser iguais, nao precisa desempate por entrada
        if(v[i].ultimo_acesso < v[escolhido].ultimo_acesso)
            escolhido = i;
    }
    return escolhido;
}