#include "alocacao.h"

Saida NextFit(Memoria &memoria, int tamanho){
    //achar o primeiro bloco livre cujo fim é maior que o ponteiro do next
    int pos = 0;
    for(int i = 0 ; i < memoria.mem.size() ; i++){
        Bloco b = memoria.mem[i];
        if(b.livre && b.comeco + b.tamanho > memoria.ptr_next_fit){
            pos = i;
            break;
        }
    }

    //procurar a partir dele um bloco livre que caiba
    bool achou = 0;
    for(int i = pos ; i < memoria.mem.size() ; i++){
        Bloco b = memoria.mem[i];
        if(b.livre && b.tamanho >= tamanho){
            alocar(memoria, tamanho, b.comeco, i);
            achou = 1;
            break;
        }
    }
    
    //se nao achou, procura do comeco
    if(!achou){
        for(int i = 0 ; i < pos ; i++){
            Bloco b = memoria.mem[i];
            if(b.livre && b.tamanho >= tamanho){
                alocar(memoria, tamanho, b.comeco, i);
                achou = 1;
                break;
            }
        }
    }

    Saida s = gerar_saida(memoria, achou);

    if(!achou){
        // cout << "Erro: sem espaço contíguo para ..."
    }

    return s;
}