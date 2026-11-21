#include "alocacao.h"

//funcao auxiliar para inserir um bloco no vetor da memoria
void alocar(Memoria &memoria, vector<Bloco> &v, int tamanho, int comeco, int pos){
    Bloco b(memoria.id_atual, comeco, tamanho, false);
    memoria.id_atual++;

    Bloco anterior = v[pos]; //bloco livre em que o novo sera alocado

    //remover do indice i
    v.erase(v.begin() + pos);

    //adicionar o novo bloco ocupado no indice i
    v.insert(v.begin() + pos, b);

    //adicionar o bloco livre (restante) no indice i+1
    if(anterior.tamanho > tamanho){
        int novo_comeco = anterior.comeco + tamanho;
        int novo_tamanho = anterior.tamanho - tamanho;

        Bloco aux(anterior.id, novo_comeco, novo_tamanho, true);
        v.insert(v.begin() + pos + 1, aux);
    }
}

Saida FirstFit(Memoria &memoria, int tamanho){
    bool val = 0;
    for(int i = 0 ; i < memoria.mem.size() ; i++){
        Bloco b = memoria.mem[i];
        if(b.livre && b.tamanho >= tamanho){
            alocar(memoria, memoria.mem, tamanho, b.comeco, i);
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