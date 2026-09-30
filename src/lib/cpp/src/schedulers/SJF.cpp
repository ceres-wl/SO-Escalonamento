#include "scheduling.h"

using namespace std;

struct ComparadorSJF{
    bool operator()(const Proc &a, const Proc &b){
        if(a.duracao != b.duracao) return a.duracao > b.duracao;
        return a.id > b.id;
    }
};
Saida ShortestJobFirst(vector<Proc> processos, int quantum, int aging){
    //ordenar os processor por ordem de chegada
    sort(processos.begin(), processos.end(), [](Proc &a, Proc &b){
        if(a.inicio != b.inicio) return a.inicio < b.inicio;
        if(a.tempo_restante != b.tempo_restante) return a.tempo_restante < b.tempo_restante;
        return a.id < b.id;
    });

    priority_queue<Proc, vector<Proc>, ComparadorSJF> prontos;

    int tempo_atual = 0, trocas = 0, id_anterior = -1;
    vector<int> diagrama;
    int tt_total = 0, tw_total = 0;

    int prox = 0; //indicar o proximo processo a ser inserido
    int concluidos = 0;

    while(concluidos < processos.size()){
        //verificar processos que ja chegaram
        while(prox < processos.size() && processos[prox].inicio <= tempo_atual){
            prontos.push(processos[prox]);
            prox++;
        }
        //incrementar o tempo atual ate o processo chegar
        if(prontos.empty()){
            diagrama.push_back(-1);
            tempo_atual++;
            continue;
        }

        Proc atual = prontos.top(); prontos.pop();

        //metricas
        if(id_anterior != -1 && id_anterior != atual.id) trocas++;
        id_anterior = atual.id;

        atual.tempo_espera = tempo_atual - atual.inicio;
        atual.tempo_vida = atual.tempo_espera + atual.duracao;

        tw_total += atual.tempo_espera;
        tt_total += atual.tempo_vida;

        //processamento do atual
        for(int i = 0 ; i < atual.duracao ; i++){
            diagrama.push_back(atual.id);
            tempo_atual++;
        }
        concluidos++;
    }
    Saida s = formatar_saida(processos.size(), tt_total, tw_total, trocas, diagrama);

    return s;
}