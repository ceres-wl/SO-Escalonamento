export interface SimulationConfig {
    quantum: number;
    aging: number;
}

export interface ProcessoInput {
    criacao: number; // Tempo de criação
    duracao: number;
    prioridade_estatica: number;
}

export interface Processo extends ProcessoInput{
    id: string;
    prioridade_dinamica: number;
}

export interface DataPoint{
    id: string;
    start: number;
    end: number;
    current_prio?: number;
}