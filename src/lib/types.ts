export interface SimulationConfig {
    quantum: number;
    aging: number;
}

export interface ProcessoInput{
    inicio: number; // Tempo de criação
    duracao: number;
    prioridade_estatica: number;
}

export interface Processo extends ProcessoInput {
    id: string;
    prioridade_dinamica: number;
}

export interface DataPoint{
    id: string;
    start: number;
    end: number;
    priority?: number;
}

export interface Metrics{
    turnaround: number;
    waiting: number;
    num_change: number;
}

export type InfoToCopy = {
    metricasStr: string;
    diagramaStr: string;
} | undefined;

export type Algo = "FCFS" | "SJF" | "SRTF" | "PrioC" | "PrioP" | "RR" | "RR-P-E";