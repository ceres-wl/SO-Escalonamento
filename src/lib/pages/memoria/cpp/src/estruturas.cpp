#include "estruturas.h"

Bloco create_bloco(int id, int endereco, int tam, bool livre){
    Bloco b;
    b.id = id;
    b.endereco = endereco;
    b.tamanho = tam;
    b.livre = livre;
    return b;
}

Memoria create_memoria(int tamanho){
    Memoria m;
    m.tam_total = tamanho;
    m.id_atual = 1;
    m.ptr_next_fit = 0;

    m.mem.clear();
    
    Bloco b = create_bloco(0, 0, tamanho, true);
    m.mem.push_back(b);
    return m;
}