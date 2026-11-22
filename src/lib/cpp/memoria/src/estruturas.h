#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <vector>

using namespace std;

//struct simulando cada bloco de memoria
struct Bloco{
    int id;
    int endereco, tamanho; //endereco referente ao endereco inicial do bloco
    bool livre; //indicar se é um bloco livre ou alocado

    Bloco(int id, int endereco, int tam, bool livre) : 
        id(id), endereco(endereco), tamanho(tam), livre(livre) {}
};

//struct representando a memoria -> uniao de blocos
struct Memoria{
    int tam_total;
    vector<Bloco> mem; //ordenado pelo endereco inicial de cada bloco
    int id_atual, ptr_next_fit; //ptr_next_fit representa o endereco apos o ultimo bloco alocado
    
    void init(int tamanho){
        tam_total = tamanho;
        id_atual = 1;
        ptr_next_fit = 0;

        mem.clear();
        Bloco b = {0, 0, tamanho, true}; //id 0 para representar blocos livres
        mem.push_back(b);
    }
};

//struct com as informacoes da memoria a serem exibidas na saida
struct Saida{
    int tam_total;
    int ocupado, livre;
    int buracos;
    int maior_buraco_livre;
    double uso_efetivo;

    bool conseguiu_alocar;
};

enum Opcao{
    INIT,
    END,
    OPT
};

struct SaidaDefrag{
    int blocos_movidos;
    int mem_deslocada;
};

#endif // ESTRUTURAS_H