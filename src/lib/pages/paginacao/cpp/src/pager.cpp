#include "estruturas.h"
#include "algoritmos/eviccao.h"

int buscar_pagina(vector<Frame> &frames, int pagina){
    for(int i = 0 ; i < frames.size() ; i++){
        if(frames[i].pagina == pagina) return i; 
    }
    return -1;
}

int buscar_frame_livre(vector<Frame> &frames){
    for(int i = 0 ; i < frames.size() ; i++){
        if(frames[i].pagina == -1) return i; 
    }
    return -1;
}

Saida pager(ALGORITHM algo, int frame_num, vector<PairIB> trace, bool verbose){
    GerenciadorMemoria gerenciador;
    vector<Frame> &frames = gerenciador.frames;

    frames.resize(frame_num);

    //inicializar ids dos frames no gerenciador
    for(int i = 0 ; i < frame_num ; i++){
        frames[i].id = i;
    }

    Saida saida;
    saida.algo = algo; 
    saida.frames = frame_num;
    saida.referencias = trace.size();
    saida.frame_ids.resize(frame_num);
    saida.page_ids.resize(frame_num);
    
    vector<VerboseInfo> verb_info;

    for(int i = 0 ; i < trace.size() ; i++){
        int pagina = trace[i].first, escrita = trace[i].second;
        int idx_frame = buscar_pagina(frames, pagina);
        bool hit = (idx_frame != -1);
        int passo = i + 1;

        VerboseInfo verb;
        verb.passo = passo;
        verb.pag_ref = pagina;
        verb.hit = hit;

        //se encontrou a pagina na memoria
        if(hit){
            frames[idx_frame].ultimo_acesso = passo;
            frames[idx_frame].bit_r = 1;
            if(escrita) frames[idx_frame].bit_m = 1;
            frames[idx_frame].quant_acessos++;
        }
        else{
            saida.page_fault++;
            int alvo = buscar_frame_livre(frames);
            //verifica se tem algum frame livre na memoria
            if(alvo == -1){
                alvo = selecionar_frame(algo, gerenciador, trace, i);
                saida.evictions++;
                verb.removed = frames[alvo].pagina;
                if(frames[alvo].bit_m){
                    saida.disk_writes++;
                    verb.escrita = 1;
                }
            }
            //colocar na memoria (atualizar as informacoes do frame)
            frames[alvo].pagina = pagina;
            frames[alvo].bit_m = escrita;
            frames[alvo].bit_r = 1;
            frames[alvo].entrada = passo;
            frames[alvo].quant_acessos = 1;
            frames[alvo].ultimo_acesso = passo;
        }
        if(algo == NRU && passo % 4 == 0){
            for(Frame &f : frames) f.bit_r = 0;
        }
        for(Frame &f : frames){
            verb.cur_frames.push_back(f.pagina);
        }
        verb_info.push_back(verb);
    }
    for(int i = 0 ; i < frames.size() ; i++){
        saida.frame_ids[i] = frames[i].id;
        saida.page_ids[i] = frames[i].pagina;
    }
    if(saida.referencias != 0)
        saida.fault_ratio = 100.0 * saida.page_fault / saida.referencias;
    else
        saida.fault_ratio = 0;

    saida.verb_info = verb_info;

    return saida;
}