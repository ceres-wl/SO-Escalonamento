#include "scheduling.h"

using namespace std;

Saida RoundRobinAging(vector<Proc> processos, int quantum, int aging){
    int n = processos.size();

    //ordenar os processor por ordem de chegada
    sort(processos.begin(), processos.end(), [](Proc &a, Proc &b){
        if(a.inicio != b.inicio) return a.inicio < b.inicio;
        if(a.tempo_restante != b.tempo_restante) return a.tempo_restante < b.tempo_restante;
        return a.id < b.id;
    });

    vector<Proc> prontos;

    int tempo_atual = 0, trocas = 0, id_anterior = -1;
    vector<int> diagrama;
    int tt_total = 0, tw_total = 0;

    int prox = 0; //indicar o proximo processo a ser inserido
    int concluidos = 0;

    while(concluidos < n){
        //verificar processos que ja chegaram
        while(prox < processos.size() && processos[prox].inicio <= tempo_atual){
            prontos.push_back(processos[prox]);
            prox++;
        }
        //incrementar o tempo atual ate o processo chegar
        if(prontos.empty()){
            diagrama.push_back(-1);
            tempo_atual++;
            continue;
        }

        sort(prontos.begin(), prontos.end(), [id_anterior](const Proc &a, const Proc &b){
            if(a.prioridade_dinamica != b.prioridade_dinamica) return a.prioridade_dinamica > b.prioridade_dinamica; 
            
            //evitar troca de contexto
            bool a_na_cpu = (a.id == id_anterior), b_na_cpu = (b.id == id_anterior);
            if(a_na_cpu != b_na_cpu) return a_na_cpu; 

            if(a.tempo_restante != b.tempo_restante) return a.tempo_restante < b.tempo_restante; 

            return a.id < b.id;
        });

        Proc atual = prontos[0]; prontos.erase(prontos.begin());

        //restaurar a prioridade dinamica
        atual.prioridade_dinamica = atual.prioridade_estatica;

        //troca de contexto
        if(id_anterior != -1 && id_anterior != atual.id) trocas++;
        id_anterior = atual.id;

        //processamento do atual
        int iteracoes = 0;
        while(atual.tempo_restante > 0 && iteracoes < quantum){
            diagrama.push_back(atual.id);
            tempo_atual++;
            atual.tempo_restante--;
            
            //verificar se chegou algum processo
            while(prox < processos.size() && processos[prox].inicio <= tempo_atual){
                prontos.push_back(processos[prox]);
                prox++;
            }

            iteracoes++;
        }

        //atualizar as prioridades dinamicas (a cada quantum ou se terminou)
        for(Proc &p : prontos){
            p.prioridade_dinamica += aging;
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
            prontos.push_back(atual);
        }
    }
    Saida s = formatar_saida(n, tt_total, tw_total, trocas, diagrama);
    return s;
}