#include "alocacao.h"

Saida WorstFit(Memoria &memoria, int tamanho){
    int melhor = -1, pos = -1, comeco = -1;
    for(int i = 0 ; i < memoria.mem.size() ; i++){
        Bloco b = memoria.mem[i];
        if(b.livre && b.tamanho >= tamanho){
            if(b.tamanho > melhor){
                melhor = b.tamanho;
                pos = i;
                comeco = b.comeco;
            }
        }
    }

    Saida s;

    if(pos != -1){
        alocar(memoria, tamanho, comeco, pos);
        s = gerar_saida(memoria, true);
    }
    else{
        s = gerar_saida(memoria, false);
        // cout << "Erro: sem espaço contíguo para ..."
    }

    return s;
}