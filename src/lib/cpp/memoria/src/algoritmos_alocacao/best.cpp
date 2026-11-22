#include "alocacao.h"

Saida BestFit(Memoria &memoria, int tamanho){
    int melhor = __INT_MAX__, pos = -1, endereco = -1;
    for(int i = 0 ; i < memoria.mem.size() ; i++){
        Bloco b = memoria.mem[i];
        if(b.livre && b.tamanho >= tamanho){
            if(b.tamanho < melhor){
                melhor = b.tamanho;
                pos = i;
                endereco = b.endereco;
            }
        }
    }

    Saida s;

    if(pos != -1){
        alocar(memoria, tamanho, endereco, pos);
        s = gerar_saida(memoria, true);
    }
    else{
        s = gerar_saida(memoria, false);
        // cout << "Erro: sem espaço contíguo para ..."
    }

    return s;
}