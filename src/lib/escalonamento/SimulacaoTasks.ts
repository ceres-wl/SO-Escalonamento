import type { FuncEscalonamento, Processo } from "../types";

export class SimulacaoTasks{
    queue: Array<Processo> = [];
    time: number = 0;
    escalonador: FuncEscalonamento;

    constructor(escalonador: FuncEscalonamento){
        this.escalonador = escalonador;
    }
}