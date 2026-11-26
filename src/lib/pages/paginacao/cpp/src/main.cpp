#include "estruturas.h"
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>

EMSCRIPTEN_BINDINGS(module){
    using namespace emscripten;
    emscripten::function<Saida>("pager", &pager);

    value_object<VerboseInfo>("VerboseInfo")
        .field("passo", &VerboseInfo::passo)
        .field("pag_ref", &VerboseInfo::pag_ref)
        .field("cur_frames", &VerboseInfo::cur_frames)
        .field("hit", &VerboseInfo::hit)
        .field("removed", &VerboseInfo::removed)
        .field("escrita", &VerboseInfo::escrita);
        
    value_object<Saida>("Saida")
        .field("algo", &Saida::algo)
        .field("frames", &Saida::frames)
        .field("referencias", &Saida::referencias)
        .field("page_fault", &Saida::page_fault)
        .field("fault_ratio", &Saida::fault_ratio)
        .field("evictions", &Saida::evictions)
        .field("disk_writes", &Saida::disk_writes)
        .field("frame_ids", &Saida::frame_ids)
        .field("page_ids", &Saida::page_ids)
        .field("verb_info", &Saida::verb_info);

    value_object<PairIB>("PairIB")
        .field("first", &PairIB::first)
        .field("second", &PairIB::second);

    enum_<ALGORITHM>("ALGORITHM")
        .value("FIFO", ALGORITHM::FIFO)
        .value("LRU", ALGORITHM::LRU)
        .value("OTIMO", ALGORITHM::OTIMO)
        .value("CLOCK", ALGORITHM::CLOCK)
        .value("NRU", ALGORITHM::NRU)
        .value("LFU", ALGORITHM::LFU)
        .value("MFU", ALGORITHM::MFU);


    // value_object<Frame>("Frame")
    //     .field("id", &Frame::id)
    //     .field("pagina", &Frame::pagina)
    //     .field("entrada", &Frame::entrada)
    //     .field("ultimo_acesso", &Frame::ultimo_acesso)
    //     .field("bit_r", &Frame::bit_r)
    //     .field("bit_m", &Frame::bit_m)
    //     .field("quant_acessos", &Frame::quant_acessos);

    // value_object<GerenciadorMemoria>("GerenciadorMemoria")
    //     .field("frames", &GerenciadorMemoria::frames)
    //     .field("ponteiro_clock", &GerenciadorMemoria::ponteiro_clock);

    register_vector<int>("vector<int>");
    register_vector<PairIB>("vector<PairIB>");
    register_vector<VerboseInfo>("vector<VerboseInfo>");
}