#include "estruturas.h"
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>

EMSCRIPTEN_BINDINGS(module){
    using namespace emscripten;
    emscripten::function<Saida>("pager", &pager);

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

    value_object<VerboseInfo>("VerboseInfo")
        .field("ref", &VerboseInfo::ref)
        .field("cur_frames", &VerboseInfo::cur_frames)
        .field("hit", &VerboseInfo::hit)
        .field("removed", &VerboseInfo::removed);
    
    enum_<ALGORITHM>("ALGORITHM")
        .value("FIFO", &ALGORITHM::FIFO)
        .value("LRU", &ALGORITHM::LRU)
        .value("OTIMO", &ALGORITHM::OTIMO)
        .value("CLOCK", &ALGORITHM::CLOCK)
        .value("NRU", &ALGORITHM::NRU)
        .value("LFU", &ALGORITHM::LFU)
        .value("MFU", &ALGORITHM::MFU);

    register_vector<Bloco>("vector<Bloco>");
}