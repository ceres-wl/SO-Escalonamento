#include "operacoes.h"

//juntar blocos adjacentes (coalescencia)
void juntar(vector<Bloco> &v, int pos){
    //a ideia é deletar o adjacente que tiver livre e atualizar o tamanho do inserido
    if(pos < v.size() - 1 && v[pos + 1].livre){
        v[pos].tamanho += v[pos + 1].tamanho;
        v.erase(v.begin() + pos + 1);
    }

    if(pos > 0 && v[pos-1].livre){
        v[pos].tamanho += v[pos - 1].tamanho;
        v[pos].endereco = v[pos - 1].endereco; //endereco inicial vira o da esquerda
        v.erase(v.begin() + pos - 1);
    }
}

SaidaFree freeid(Memoria &memoria, int id){
    SaidaFree s;
    int pos = -1; //posicao do bloco a ser liberado

    for(int i = 0 ; i < memoria.mem.size() ; i++){
        Bloco b = memoria.mem[i];
        if(b.id == id && b.livre == false){
            pos = i;
            break;
        }
    }
    if(pos == -1) s.sucesso = false;

    memoria.mem[pos].livre = 1;
    memoria.mem[pos].id = 0;
    juntar(memoria.mem, pos);
    s.sucesso = true;

    s.mem = memoria;
    return s;
}

SaidaFree freeaddr(Memoria &memoria, int endereco){
    SaidaFree s;
    int pos = -1; //posicao do bloco a ser liberado

    for(int i = 0 ; i < memoria.mem.size() ; i++){
        Bloco b = memoria.mem[i];
        if(b.endereco == endereco && b.livre == false){
            pos = i;
            break;
        }
    }
    if(pos == -1) s.sucesso = false;

    memoria.mem[pos].livre = 1;
    memoria.mem[pos].id = 0;
    juntar(memoria.mem, pos);
    s.sucesso = true;

    s.mem = memoria;
    return s;
}