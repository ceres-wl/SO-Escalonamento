#include "scheduling.h"

using namespace std;

Saida RoundRobin(vector<Proc> processos, int quantum, int aging){
    int n = processos.size();

    //ordenar os processor por ordem de chegada
    sort(processos.begin(), processos.end(), [](Proc &a, Proc &b){
        if(a.inicio != b.inicio) return a.inicio < b.inicio;
        if(a.tempo_restante != b.tempo_restante) return a.tempo_restante < b.tempo_restante;
        return a.id < b.id;
    });

    queue<Proc> prontos;

    int tempo_atual = 0, trocas = 0, id_anterior = -1;
    vector<int> diagrama;
    int tt_total = 0, tw_total = 0;

    int prox = 0; //indicar o proximo processo a ser inserido
    int concluidos = 0;

    while(concluidos < n){
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

        Proc atual = prontos.front(); prontos.pop();

        //troca de contexto
        if(id_anterior != -1 && id_anterior != atual.id) trocas++;
        id_anterior = atual.id;

        //processamento do atual
        int iteracao_atual = 0;
        while(atual.tempo_restante > 0 && iteracao_atual < quantum){
            diagrama.push_back(atual.id);
            tempo_atual++;
            atual.tempo_restante--;
            
            //ver se chegou alguem
            while(prox < processos.size() && processos[prox].inicio <= tempo_atual){
                prontos.push(processos[prox]);
                prox++;
            }
            iteracao_atual++;
        }
        //so calcula as metricas se terminou
        if(atual.tempo_restante == 0){
            atual.tempo_vida = tempo_atual - atual.inicio;
            atual.tempo_espera = atual.tempo_vida - atual.duracao;

            tw_total += atual.tempo_espera;
            tt_total += atual.tempo_vida;
            concluidos++;
        }
        else{
            prontos.push(atual);
        }
    }
    Saida s = formatar_saida(processos.size(), tt_total, tw_total, trocas, diagrama);
    return s;
}