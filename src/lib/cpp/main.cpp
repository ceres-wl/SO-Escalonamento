#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <queue>
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>

using namespace std;

struct ProcInput{
    int id;
    int inicio, duracao, prioridade_estatica;
};

//struct simulando cada processo e suas informações
struct Proc {
    int id;
    int inicio, duracao, prioridade_estatica, prioridade_dinamica;
    string status;

    int tempo_restante, tempo_espera, tempo_vida;
};

//struct com as informações produzidas por cada algoritmo de escalonamento
struct Saida{
    double tt; //turnaround time
    double tw; //waiting time
    int trocas_contexto;
    vector<int> diagrama_tempo; //cada posição indica o tempo e o valor guardado indica o id do processo
    //ex: diagrama_tempo[1] = 3 -> no tempo 1-2, o processo de id 3 estava executando
    //diagrama_tempo[0] = -1 -> no tempo 0-1, nenhum processo estava executando
    vector<int> prioridades_dinamicas;
};

vector<Proc> procs = {};
int quantum, aging;

void printProcs(){
    cout << "[ " << endl;
    for(Proc proc : procs){
        cout << "{ Id: P" << proc.id << "; inicio: " << proc.inicio << "; duracao: " << proc.duracao << " }" << endl;
    }
    cout << "]" << endl;
}

vector<Proc>* get_procs(){
    return &procs;
}

void clear_procs(){
    procs.clear();
}

void add_proc(ProcInput proc_input){
    Proc proc;

    proc.id = proc_input.id;
    proc.inicio = proc_input.inicio;
    proc.duracao = proc_input.duracao;
    proc.prioridade_estatica = proc_input.prioridade_estatica;
    proc.prioridade_dinamica = proc_input.prioridade_estatica;

    proc.status = "";
    proc.tempo_espera = 0;
    proc.tempo_restante = proc.duracao;
    proc.tempo_vida = 0;

    procs.push_back(proc);
}

void set_config(int _aging, int _quantum){
    quantum = _quantum;
    aging = _aging;
}

Saida FCFS(){
    vector<Proc> processos = procs;

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



struct ComparadorSJF{
    bool operator()(const Proc &a, const Proc &b){
        if(a.duracao != b.duracao) return a.duracao > b.duracao;
        return a.id > b.id;
    }
};
Saida ShortestJobFirst(){
    vector<Proc> processos = procs;

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



struct ComparadorSRTF{
    bool operator()(const Proc &a, const Proc &b){
        if(a.tempo_restante != b.tempo_restante) return a.tempo_restante > b.tempo_restante;
        return a.id > b.id;
    }
};
Saida ShortestRemainingTimeFirst(){
    vector<Proc> processos = procs;
    int n = processos.size();

    //ordenar os processor por ordem de chegada
    sort(processos.begin(), processos.end(), [](Proc &a, Proc &b){
        if(a.inicio != b.inicio) return a.inicio < b.inicio;
        if(a.tempo_restante != b.tempo_restante) return a.tempo_restante < b.tempo_restante;
        return a.id < b.id;
    });

    priority_queue<Proc, vector<Proc>, ComparadorSRTF> prontos;

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
            
            //verificar se chegou algum processo com tempo restante menor
            while(prox < processos.size() && processos[prox].inicio <= tempo_atual){
                prontos.push(processos[prox]);
                prox++;
            }
            if(!prontos.empty() && prontos.top().tempo_restante < atual.tempo_restante){
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



struct ComparadorPRIO{
    bool operator()(const Proc &a, const Proc &b){
        if(a.prioridade_estatica != b.prioridade_estatica) return a.prioridade_estatica < b.prioridade_estatica;
        if(a.tempo_restante != b.tempo_restante) return a.tempo_restante > b.tempo_restante;
        return a.id > b.id;
    }
};
Saida PRIOc(){
    vector<Proc> processos = procs;

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



Saida PRIOp(){
    vector<Proc> processos = procs;
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

EMSCRIPTEN_BINDINGS(module){
    using namespace emscripten;
    emscripten::function<vector<Proc>*>("get_procs", &get_procs, return_value_policy::reference());
    emscripten::function<void>("add_proc", &add_proc);
    emscripten::function<void>("clear_procs", &clear_procs);
    emscripten::function<void>("set_config", &set_config);
    emscripten::function<Saida>("FCFS", &FCFS);
    emscripten::function<Saida>("SJF", &ShortestJobFirst);
    emscripten::function<Saida>("SRTF", &ShortestRemainingTimeFirst);

    value_object<Saida>("Saida")
        .field("tt", &Saida::tt)
        .field("tw", &Saida::tw)
        .field("trocas_contexto", &Saida::trocas_contexto)
        .field("diagrama_tempo", &Saida::diagrama_tempo);

    value_object<ProcInput>("ProcInput")
        .field("id", &ProcInput::id)
        .field("inicio", &ProcInput::inicio)
        .field("duracao", &ProcInput::duracao)
        .field("prioridade_estatica", &ProcInput::prioridade_estatica);

    value_object<Proc>("Proc")
        .field("id", &Proc::id)
        .field("inicio", &Proc::inicio)
        .field("duracao", &Proc::duracao)
        .field("prioridade_estatica", &Proc::prioridade_estatica)
        .field("prioridade_dinamica", &Proc::prioridade_dinamica)
        .field("status", &Proc::status)
        .field("tempo_restante", &Proc::tempo_restante)
        .field("tempo_espera", &Proc::tempo_espera)
        .field("tempo_vida", &Proc::tempo_vida);

    register_vector<Proc>("vector<Proc>");
    register_vector<int>("vector<int>");
}