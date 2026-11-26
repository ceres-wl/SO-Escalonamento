import createModule from "./build/Pages_wasm";

// Teoricamente esperar essa promise desse jeito assim que o módulo carrega vai atrasar
// o carregamento de qualquer componente que queira usar uma dessas funções, de forma desnecessária,
// mas pro nosso caso aqui tá tudo bem, não vai nem ser perceptivel a demora

export const Module = await createModule();

export const pager = Module.pager;

export type ALGORITHM = 
    "FIFO" |
    "LRU" |
    "OTIMO" |
    "CLOCK" |
    "NRU" |
    "LFU" |
    "MFU";

export const opcao = new Map([
    ["FIFO", { value: Module.ALGORITHM.FIFO.value }],
    ["LRU", { value: Module.ALGORITHM.LRU.value }],
    ["OTIMO", { value: Module.ALGORITHM.OTIMO.value }],
    ["CLOCK", { value: Module.ALGORITHM.CLOCK.value }],
    ["NRU", { value: Module.ALGORITHM.NRU.value }],
    ["LFU", { value: Module.ALGORITHM.LFU.value }],
    ["MFU", { value: Module.ALGORITHM.MFU.value }]
]);