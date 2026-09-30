#include "formatar_saida.h"

Saida formatar_saida(int n, int tt_total, int tw_total, int trocas, std::vector<int> diagrama){
    Saida s;
    s.diagrama_tempo = diagrama;
    s.trocas_contexto = trocas;
    s.tt = (double) tt_total / n;
    s.tw = (double) tw_total / n;
    return s;
}