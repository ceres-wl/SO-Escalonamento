#ifndef SO_SCHEDULING_H
#define SO_SCHEDULING_H

#include <algorithm>
#include <queue>

#include "../estruturas.h"
#include "../formatar_saida.h"

Saida ShortestJobFirst(std::vector<Proc> processos, int quantum, int aging);
Saida ShortestRemainingTimeFirst(std::vector<Proc> processos, int quantum, int aging);
Saida PRIOp(std::vector<Proc> processos, int quantum, int aging);
Saida PRIOc(std::vector<Proc> processos, int quantum, int aging);
Saida FCFS(std::vector<Proc> processos, int quantum, int aging);
Saida RoundRobin(std::vector<Proc> processos, int quantum, int aging);
Saida RoundRobinAging(std::vector<Proc> processos, int quantum, int aging);

#endif // SO_SCHEDULING_H