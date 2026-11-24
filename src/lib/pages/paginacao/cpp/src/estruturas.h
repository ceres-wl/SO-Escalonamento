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

struct VerboseInfo{
    int ref;
    vector<int> cur_frames;
    bool hit;
    int removed;
};

struct Saida{
    ALGORITHM algo;
    int frames;
    int referencias;
    int page_fault;
    double fault_ratio;
    int evictions;
    int disk_writes;
    vector<int> frame_ids;  
    vector<int> page_ids; 
    vector<VerboseInfo> verb_info;
};

// trace - 0: leitura; 1: escrita

Saida pager(ALGORITHM algo, int frame_num, vector<pair<int, bool>> trace, bool verbose);
