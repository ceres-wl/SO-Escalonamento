#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <queue>
// #include <emscripten/emscripten.h>
// #include <emscripten/bind.h>

using namespace std;

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
};

vector<Proc> procs = {};

vector<Proc>* get_procs(){
    return &procs;
}

void add_proc(Proc proc){
    procs.push_back(proc);
}

void ler_configuracao(int &quantum, int &aging){
    ifstream arquivo("config.txt");
    string linha;
    while(getline(arquivo, linha)){
        string atual, valor; //ver se é quantum ou aging, guardar o valor
        bool separacao = 0;

        //vai colocar em atual ate ver um ponto e virgula (:). Depois disso, coloca em valor
        //no final, converte para inteiro e armazena na variavel correspondente
        for(int i = 0 ; i < linha.size() ; i++){
            if(linha[i] == ' ') continue;
            if(linha[i] == ':') separacao = 1;
            else if(!separacao) atual.push_back(linha[i]);
            else valor.push_back(linha[i]); 
        }
        if(atual == "quantum") quantum = stoi(valor);
        else if(atual == "aging") aging = stoi(valor);
    }
}

void ler_processos(){
    int data_criacao, tempo_execucao, prioridade_estatica;
    int id = 1;
    while(cin >> data_criacao >> tempo_execucao >> prioridade_estatica){
        Proc p;
        p.inicio = data_criacao; p.duracao = tempo_execucao;
        p.prioridade_estatica = prioridade_estatica; p.prioridade_dinamica = prioridade_estatica;
        p.id = id; p.status = "Pronto";

        p.tempo_restante = tempo_execucao;
        id++;

        add_proc(p);
    }
}

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
    
    queue<Proc> q;
    q.push(processos[0]);
    int prox = 1; //indicar o proximo processo a ser inserido

    while(!q.empty()){
        Proc atual = q.front(); q.pop();

        //ver tempo ocioso da CPU
        while(tempo_atual < atual.inicio){
            diagrama.push_back(-1);
            tempo_atual++;
        }

        //ver se teve troca de contexto
        if(id_anterior != -1 && id_anterior != atual.id) trocas++;
        id_anterior = atual.id;

        atual.tempo_espera = tempo_atual - atual.inicio;
        atual.tempo_vida = atual.tempo_espera + atual.duracao;

        tw_total += atual.tempo_espera;
        tt_total += atual.tempo_vida;

        for(int i = 0 ; i < atual.duracao ; i++){
            diagrama.push_back(atual.id);
            tempo_atual++;
        }

        if(prox < processos.size()){
            q.push(processos[prox]);
            prox++;
        }
    }

    Saida s; 
    s.tt = (double) tt_total / processos.size();
    s.tw = (double) tw_total / processos.size();
    s.trocas_contexto = trocas;
    s.diagrama_tempo = diagrama;

    // cout << "trocas: " << s.trocas_contexto << endl;
    // cout << "tt: " << fixed << s.tt << endl;
    // cout << "tw: " << fixed << s.tw << endl;
    // for(int x : s.diagrama_tempo) cout << x << " "; cout << endl;

    return s;
}

int main(){
    int quantum, aging;
    ler_configuracao(quantum, aging);

    ler_processos();
    if(procs.size() == 0){
        cout << "Nenhum processo recebido" << "\n";
        return 0;
    }

    Saida s = FCFS(procs);
    return 0;
}

// EMSCRIPTEN_BINDINGS(module){
//     using namespace emscripten;
//     function("get_procs", &get_procs, return_value_policy::reference());
//     function("add_proc", &add_proc);

//     value_object<Proc>("Proc")
//         .field("inicio", &Proc::inicio)
//         .field("duracao", &Proc::duracao)
//         .field("prioridade_estatica", &Proc::prioridade_estatica);

//     register_vector<Proc>("vector<Proc>");
// }