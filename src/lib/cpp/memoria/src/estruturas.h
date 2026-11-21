#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <vector>

//struct simulando cada bloco de memoria
struct Bloco{
    int id;
    int comeco, tamanho; //comeca representa o endereco inicial do bloco
    bool livre; //indicar se é um bloco livre ou alocado
};

//struct representando a memoria -> uniao de blocos
struct Memoria{
    int tam_total;
    std::vector<Bloco> mem; //manter ordenado pelo comeco de cada bloco
    int id_atual, ptr_next_fit; //ptr_next_fit representa o endereco apos o ultimo bloco alocado
    
    void init(int tamanho){
        tam_total = tamanho;
        id_atual = 1;
        ptr_next_fit = 0;

        mem.clear();
        Bloco b = {0, 0, tamanho, true}; //id 0 para representar o comeco
        mem.push_back(b);
    }
};

//struct com as informacoes a serem exibidas na saida
struct Saida{
    int tam_total;
    int ocupado, livre;
    int buracos;
    int maior_buraco_livre;
    double uso_efetivo;
};

#endif // ESTRUTURAS_H