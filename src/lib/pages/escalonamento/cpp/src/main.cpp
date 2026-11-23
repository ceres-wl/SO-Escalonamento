#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <queue>
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#include "schedulers/scheduling.h"

using namespace std;

struct ProcInput{
    int id;
    int inicio, duracao, prioridade_estatica;
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

    proc.tempo_espera = 0;
    proc.tempo_restante = proc.duracao;
    proc.tempo_vida = 0;

    procs.push_back(proc);
}

void set_config(int _aging, int _quantum){
    quantum = _quantum;
    aging = _aging;
}

Saida run_FCFS() { return FCFS(procs, quantum, aging); }
Saida run_SJF() { return ShortestJobFirst(procs, quantum, aging); }
Saida run_SRTF() { return ShortestRemainingTimeFirst(procs, quantum, aging); }
Saida run_prio_c() { return PRIOc(procs, quantum, aging); }
Saida run_prio_p() { return PRIOp(procs, quantum, aging); }
Saida run_round_robin() { return RoundRobin(procs, quantum, aging); }
Saida run_round_robin_aging() { return RoundRobinAging(procs, quantum, aging); }

EMSCRIPTEN_BINDINGS(module){
    using namespace emscripten;
    emscripten::function<vector<Proc>*>("get_procs", &get_procs, return_value_policy::reference());
    emscripten::function<void>("add_proc", &add_proc);
    emscripten::function<void>("clear_procs", &clear_procs);
    emscripten::function<void>("set_config", &set_config);
    emscripten::function<Saida>("FCFS", &run_FCFS);
    emscripten::function<Saida>("SJF", &run_SJF);
    emscripten::function<Saida>("SRTF", &run_SRTF);
    emscripten::function<Saida>("prio_c", &run_prio_c);
    emscripten::function<Saida>("prio_p", &run_prio_p);
    emscripten::function<Saida>("round_robin", &run_round_robin);
    emscripten::function<Saida>("round_robin_aging", &run_round_robin_aging);

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
        .field("tempo_restante", &Proc::tempo_restante)
        .field("tempo_espera", &Proc::tempo_espera)
        .field("tempo_vida", &Proc::tempo_vida);

    register_vector<Proc>("vector<Proc>");
    register_vector<int>("vector<int>");
}