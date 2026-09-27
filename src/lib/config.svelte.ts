import { set_config } from "./cpp/api/cppApi";
import type { SimulationConfig } from "./types";

// Módulo que contém só os dados de configuração

// Não dê reassign nessa variável diretamente, use o método setConfig
export let config: SimulationConfig = $state({
    aging: 0,
    quantum: 0
});

export function setConfig(aging: number, quantum: number){
    set_config(aging, quantum);
    config.aging = aging;
    config.quantum = quantum;
}

setConfig(1, 1);