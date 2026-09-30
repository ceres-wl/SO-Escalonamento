#ifndef SO_SCHEDULING_H
#define SO_SCHEDULING_H

#include <algorithm>
#include <queue>

#include "estruturas.h"
#include "formatar_saida.h"

Saida ShortestJobFirst(std::vector<Proc> processos);
Saida ShortestRemainingTimeFirst(std::vector<Proc> processos);
Saida PRIOp(std::vector<Proc> processos);
Saida PRIOc(std::vector<Proc> processos);
Saida FCFS(std::vector<Proc> processos);

#endif // SO_SCHEDULING_H