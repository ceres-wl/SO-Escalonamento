#include "operacoes.h"

SaidaDefrag defrag(Memoria &memoria, Opcao op){
    if(op == 0){
        return defrag_init(memoria);
    }
    else if(op == 1){
        return defrag_end(memoria);
    }
    else{
        return defrag_opt(memoria);
    }
}

SaidaDefrag defrag_init(Memoria &memoria){
    // int endr_atual = memoria.tam_total;
    // for(int i = memoria.mem.size() - 1)
}

SaidaDefrag defrag_end(Memoria &memoria){
    int endr_atual = 0, blocos_movidos = 0, mem_deslocada = 0;
    for(int i = 0 ; i < memoria.mem.size() ; i++){
        Bloco b = memoria.mem[i];
        if(b.livre == 0){
            if(b.endereco > endr_atual){
                blocos_movidos++;
                mem_deslocada += b.tamanho;
                b.endereco = endr_atual;
            }
            endr_atual = b.endereco + b.tamanho + 1;
        }
    }
    return {blocos_movidos, mem_deslocada};
}

SaidaDefrag defrag_opt(Memoria &memoria){

}