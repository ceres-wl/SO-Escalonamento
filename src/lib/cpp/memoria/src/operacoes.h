#ifndef OPERACOES_H
#define OPERACOES_H

#include "estruturas.h"
#include <algorithm>

//retorna verdadeiro se conseguiu liberar e falso caso contrario
bool freeid(Memoria &memoria, int id);
bool freeaddr(Memoria &memoria, int endereco);

SaidaDefrag defrag(Memoria &memoria, Opcao op);

#endif