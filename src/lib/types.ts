export interface Config {
    quantum: number;
    aging: number;
}

export interface ProcessoInput {
    criacao: number; // Tempo de criação
    duracao: number;
    prioridade_estatica: number;
}

export interface Processo extends ProcessoInput{
    id: number;
    prioridade_dinamica: number;
}

export type FuncEscalonamento = (processos: Array<Processo>) => Processo;