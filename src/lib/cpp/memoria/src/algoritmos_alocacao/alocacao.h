#ifndef ALOCACAO_H
#define ALOCACAO_H

#include "../estruturas.h"
#include "../saida.h"

//funcao auxiliar para inserir um novo bloco no vetor da memoria
void alocar(Memoria &memoria, int tamanho, int comeco, int pos);

Saida FirstFit(Memoria &memoria, int tamanho);
Saida BestFit(Memoria &memoria, int tamanho);
Saida WorstFit(Memoria &memoria, int tamanho);
Saida NextFit(Memoria &memoria, int tamanho);

#endif