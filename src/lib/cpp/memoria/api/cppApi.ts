import createModule from "./build/Memory_wasm";

// Teoricamente esperar essa promise desse jeito assim que o módulo carrega vai atrasar
// o carregamento de qualquer componente que queira usar uma dessas funções, de forma desnecessária,
// mas pro nosso caso aqui tá tudo bem, não vai nem ser perceptivel a demora

const Module = await createModule();

export const init_mem = Module.init_mem;
export const FirstFit = Module.FirstFit;
export const BestFit = Module.BestFit;
export const WorstFit = Module.WorstFit;
export const NextFit = Module.NextFit;
export const freeid = Module.freeid;
export const freeaddr = Module.freeaddr;
export const defrag = Module.defrag;
export const gerar_saida = Module.gerar_saida;

// export const get_procs = Module.get_procs;

// export const add_proc = Module.add_proc;

// export const set_config = Module.set_config;
// export const FCFS = Module.FCFS;
// export const SJF = Module.SJF;
// export const SRTF = Module.SRTF;
// export const prio_c = Module.prio_c;
// export const prio_p = Module.prio_p;
// export const round_robin = Module.round_robin;
// export const round_robin_aging = Module.round_robin_aging;

// export const clear_procs = Module.clear_procs;