#include "scheduling.h"

using namespace std;

struct ComparadorPRIO{
    bool operator()(const Proc &a, const Proc &b){
        if(a.prioridade_estatica != b.prioridade_estatica) return a.prioridade_estatica < b.prioridade_estatica;
        if(a.tempo_restante != b.tempo_restante) return a.tempo_restante > b.tempo_restante;
        return a.id > b.id;
    }
};

Saida PRIOp(vector<Proc> processos){
    int n = processos.size();

    //ordenar os processor por ordem de chegada
    sort(processos.begin(), processos.end(), [](Proc &a, Proc &b){
        if(a.inicio != b.inicio) return a.inicio < b.inicio;
        if(a.tempo_restante != b.tempo_restante) return a.tempo_restante < b.tempo_restante;
        return a.id < b.id;
    });

    priority_queue<Proc, vector<Proc>, ComparadorPRIO> prontos;

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

        Proc atual = prontos.top(); prontos.pop();

        //troca de contexto
        if(id_anterior != -1 && id_anterior != atual.id) trocas++;
        id_anterior = atual.id;

        //processamento do atual
        while(atual.tempo_restante > 0){
            diagrama.push_back(atual.id);
            tempo_atual++;
            atual.tempo_restante--;
            
            //verificar se chegou algum processo com prioridade maior
            while(prox < processos.size() && processos[prox].inicio <= tempo_atual){
                prontos.push(processos[prox]);
                prox++;
            }
            if(!prontos.empty() && prontos.top().prioridade_estatica > atual.prioridade_estatica){
                prontos.push(atual);
                break;
            }
        }
        //so calcula as metricas se terminou
        if(atual.tempo_restante == 0){
            atual.tempo_vida = tempo_atual - atual.inicio;
            atual.tempo_espera = atual.tempo_vida - atual.duracao;

            tw_total += atual.tempo_espera;
            tt_total += atual.tempo_vida;
            concluidos++;
        }
    }
    Saida s = formatar_saida(processos.size(), tt_total, tw_total, trocas, diagrama);
    return s;
}