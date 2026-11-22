#include "alocacao.h"

Saida FirstFit(Memoria &memoria, int tamanho){
    bool val = 0;
    for(int i = 0 ; i < memoria.mem.size() ; i++){
        Bloco b = memoria.mem[i];
        if(b.livre && b.tamanho >= tamanho){
            alocar(memoria, tamanho, b.endereco, i);
            val = 1;
            break;
        }
    }

    Saida s = gerar_saida(memoria, val);

    if(!val){
        // cout << "Erro: sem espaço contíguo para ..."
    }

    return s;
}