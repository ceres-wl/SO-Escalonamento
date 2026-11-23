#include "estruturas.h"
#include "algoritmos_alocacao/alocacao.h"
#include "saida.h"
#include "operacoes.h"
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>

EMSCRIPTEN_BINDINGS(module){
    using namespace emscripten;
    emscripten::function<void>("init_mem", &init_mem);
    emscripten::function<Saida>("FirstFit", &FirstFit);
    emscripten::function<Saida>("BestFit", &BestFit);
    emscripten::function<Saida>("WorstFit", &WorstFit);
    emscripten::function<Saida>("NextFit", &NextFit);
    emscripten::function<bool>("freeid", &freeid);
    emscripten::function<bool>("freeaddr", &freeaddr);
    emscripten::function<SaidaDefrag>("defrag", &defrag);
    emscripten::function<Saida>("gerar_saida", &gerar_saida);

    value_object<Bloco>("Bloco")
        .field("id", &Bloco::id)
        .field("endereco", &Bloco::endereco)
        .field("tamanho", &Bloco::tamanho)
        .field("livre", &Bloco::livre);

    value_object<Memoria>("Memoria")
        .field("tam_total", &Memoria::tam_total)
        .field("mem", &Memoria::mem)
        .field("id_atual", &Memoria::id_atual)
        .field("ptr_next_fit", &Memoria::ptr_next_fit);

    value_object<Saida>("Saida")
        .field("id", &Saida::tam_total)
        .field("ocupado", &Saida::ocupado)
        .field("livre", &Saida::livre)
        .field("buracos", &Saida::buracos)
        .field("maior_buraco_livre", &Saida::maior_buraco_livre)
        .field("uso_efetivo", &Saida::uso_efetivo)
        .field("conseguiu_alocar", &Saida::conseguiu_alocar);

    value_object<SaidaDefrag>("SaidaDefrag")
        .field("blocos_movidos", &SaidaDefrag::blocos_movidos)
        .field("mem_deslocada", &SaidaDefrag::mem_deslocada);
    
    enum_<Opcao>("Opcao")
        .value("INIT", Opcao::INIT)
        .value("END", Opcao::END)
        .value("OPT", Opcao::OPT);

    register_vector<Bloco>("vector<Bloco>");
}