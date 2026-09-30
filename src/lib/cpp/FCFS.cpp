#include "scheduling.h"

using namespace std;

Saida FCFS(vector<Proc> processos){
    //ordenar os processor por ordem de chegada
    sort(processos.begin(), processos.end(), [](Proc &a, Proc &b){
        if(a.inicio != b.inicio) return a.inicio < b.inicio;
        if(a.tempo_restante != b.tempo_restante) return a.tempo_restante < b.tempo_restante;
        return a.id < b.id;
    });

    int tempo_atual = 0, trocas = 0, id_anterior = -1;
    vector<int> diagrama;
    int tt_total = 0, tw_total = 0;

    int prox = 0; //indicar o proximo processo a ser inserido

    for(int i = 0 ; i < processos.size() ; i++){
        Proc atual = processos[i];

        //ver tempo ocioso (nenhum processo pronto)
        while(tempo_atual < atual.inicio){
            diagrama.push_back(-1);
            tempo_atual++;
        }

        //ver se teve troca de contexto + contas das metricas
        if(id_anterior != -1 && id_anterior != atual.id) trocas++;
        id_anterior = atual.id;

        atual.tempo_espera = tempo_atual - atual.inicio;
        atual.tempo_vida = atual.tempo_espera + atual.duracao;

        tw_total += atual.tempo_espera;
        tt_total += atual.tempo_vida;

        //processamento do processo atual
        for(int i = 0 ; i < atual.duracao ; i++){
            diagrama.push_back(atual.id);
            tempo_atual++;
        }
    }
    Saida s = formatar_saida(processos.size(), tt_total, tw_total, trocas, diagrama);
    return s;
}