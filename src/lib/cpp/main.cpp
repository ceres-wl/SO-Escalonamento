#include <vector>
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>

struct Proc {
    int inicio;
    int duracao;
    int prioridade_estatica;
};

std::vector<Proc> procs = {};

std::vector<Proc>* get_procs(){
    return &procs;
}

void add_proc(Proc proc){
    procs.push_back(proc);
}

EMSCRIPTEN_BINDINGS(module){
    using namespace emscripten;
    function("get_procs", &get_procs, return_value_policy::reference());
    function("add_proc", &add_proc);

    value_object<Proc>("Proc")
        .field("inicio", &Proc::inicio)
        .field("duracao", &Proc::duracao)
        .field("prioridade_estatica", &Proc::prioridade_estatica);

    register_vector<Proc>("vector<Proc>");
}