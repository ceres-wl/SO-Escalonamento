#include "alocacao.h"

void alocar(Memoria &memoria, int tamanho, int endereco, int pos){
    Bloco b = create_bloco(memoria.id_atual, endereco, tamanho, false);
    memoria.id_atual++;
    
    vector<Bloco> &v = memoria.mem;
    
    Bloco anterior = v[pos]; //bloco livre em que o novo sera alocado

    //remover do indice i
    v.erase(v.begin() + pos);

    //alocar o novo bloco no indice i
    v.insert(v.begin() + pos, b);

    //adicionar o bloco livre (restante) no indice i+1 e atualizar ptr do next fit
    int novo_comeco = anterior.endereco + tamanho;
    memoria.ptr_next_fit = novo_comeco;

    if(anterior.tamanho > tamanho){
        int novo_tamanho = anterior.tamanho - tamanho;

        Bloco aux = create_bloco(anterior.id, novo_comeco, novo_tamanho, true);
        v.insert(v.begin() + pos + 1, aux);
    }
}