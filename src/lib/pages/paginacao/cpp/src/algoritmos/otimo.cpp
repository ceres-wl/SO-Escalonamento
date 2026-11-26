#include "eviccao.h"

int prox_acesso(vector<PairIB>& trace, int pagina, int idx_atual){
    for(int i = idx_atual + 1 ; i < trace.size() ; i++){
        if(trace[i].first == pagina) return i;
    }
    return -1;
}

int otimo(GerenciadorMemoria& gerenciador, vector<PairIB>& trace, int idx_atual){
    vector<Frame>& v = gerenciador.frames;
    int escolhido = 0;
    int melhor = prox_acesso(trace, v[0].pagina, idx_atual);

    for(int i = 1; i < v.size(); i++){
        int acesso = prox_acesso(trace, v[i].pagina, idx_atual);
        bool troca = 0;
        //desempate pelo menor tempo de entrada (a mais tempo na memoria)
        if(acesso == -1 && melhor != -1) troca = 1;
        else if(acesso == -1 && melhor == -1 && v[i].entrada < v[escolhido].entrada) troca = 1;
        else if(melhor != -1 && (acesso > melhor || (acesso == melhor && v[i].entrada < v[escolhido].entrada))) troca = 1;
        
        if(troca){
            escolhido = i;
            melhor = acesso;
        } 
    }
    return escolhido;
}