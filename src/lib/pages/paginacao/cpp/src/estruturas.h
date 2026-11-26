#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <vector>

using namespace std;

enum ALGORITHM{
    FIFO,
    LRU,
    OTIMO,
    CLOCK,
    NRU,
    LFU,
    MFU
};

//struct representando as informacoes exibidas a cada instante no verbose
struct VerboseInfo{
    int passo;
    int pag_ref;
    vector<int> cur_frames;
    bool hit;
    int removed = -1;
    bool escrita = 0;
};

//informacoes exibidas na saida
struct Saida{
    ALGORITHM algo;
    int frames;
    int referencias;
    int page_fault = 0;
    double fault_ratio;
    int evictions = 0;
    int disk_writes = 0;
    vector<int> frame_ids;  
    vector<int> page_ids; 
    vector<VerboseInfo> verb_info;
};

struct Frame{
    int id;
    int pagina = -1; //-1 por padrao, muda quando for alocado
    int entrada; //passo em que a pagina entrou na memoria
    int ultimo_acesso; //passo do ultimo acesso (leitura ou escrita) -> LRU
    bool bit_r = 0; //bit R usado no clock e NRU
    bool bit_m = 0; //M usado no NRU e escritas em disco
    int quant_acessos = 0; //contar os acessos de uma pagina -> LFU / MFU
};

struct GerenciadorMemoria{
    vector<Frame> frames;
    int ponteiro_clock = 0; //mudar a cada eviccao
};

// trace - 0: leitura; 1: escrita
Saida pager(ALGORITHM algo, int frame_num, vector<pair<int, bool>> trace, bool verbose);

#endif