#ifndef SO_ESTRUTURAS_H
#define SO_ESTRUTURAS_H

#include <vector>

//struct simulando cada processo e suas informações
struct Proc {
    int id;
    int inicio, duracao, prioridade_estatica, prioridade_dinamica;

    int tempo_restante, tempo_espera, tempo_vida;
};

//struct com as informações produzidas por cada algoritmo de escalonamento
struct Saida{
    double tt; //turnaround time
    double tw; //waiting time
    int trocas_contexto;
    std::vector<int> diagrama_tempo; //cada posição indica o tempo e o valor guardado indica o id do processo
    //ex: diagrama_tempo[1] = 3 -> no tempo 1-2, o processo de id 3 estava executando
    //diagrama_tempo[0] = -1 -> no tempo 0-1, nenhum processo estava executando
};

#endif // SO_ESTRUTURAS_H