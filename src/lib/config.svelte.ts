import type { SimulationConfig } from "./types";

// Módulo que contém só os dados de configuração

// Não dê reassign nessa variável diretamente, use o método setConfig
export let config: SimulationConfig = $state({
    aging: 1,
    quantum: 1
});

export function setConfig(aging: number, quantum: number){
    config.aging = aging;
    config.quantum = quantum;
}