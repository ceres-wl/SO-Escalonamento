#include "saida.h"

//funcao auxiliar para calcular as estatisticas para a saida dada uma memoria
Saida gerar_saida(Memoria &memoria, bool alocacao_valida){
    Saida s; 

    int buracos = 0, tam_livre = 0, maior_livre = 0;

    for(Bloco &b : memoria.mem){
        if(b.livre){
            buracos++;
            tam_livre += b.tamanho;
            maior_livre = max(maior_livre, b.tamanho);
        }
    }
    int tam_ocupado = memoria.tam_total - tam_livre;

    s = {
        memoria.tam_total, 
        tam_ocupado,
        tam_livre,
        buracos,
        maior_livre,
        (double)(tam_ocupado) / memoria.tam_total, 
        alocacao_valida
    };

    return s;
}