#ifndef OPERACOES_H
#define OPERACOES_H

#include "estruturas.h"
#include <algorithm>

struct SaidaFree{
    bool sucesso;
    Memoria mem;
};

//retorna verdadeiro se conseguiu liberar e falso caso contrario
SaidaFree freeid(Memoria &memoria, int id);
SaidaFree freeaddr(Memoria &memoria, int endereco);

SaidaDefrag defrag(Memoria &memoria, Opcao op);

#endif