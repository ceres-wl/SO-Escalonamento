export interface SimulationConfig {
    quantum: number;
    aging: number;
}

export interface Processo {
    criacao: number; // Tempo de criação
    duracao: number;
    prioridade_estatica: number;
    id: string;
    prioridade_dinamica: number;
}

export interface DataPoint{
    id: string;
    start: number;
    end: number;
    current_prio?: number;
}