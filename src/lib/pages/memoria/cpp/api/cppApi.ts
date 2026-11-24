import createModule, { type Memoria, type Opcao } from "./build/Memory_wasm";

// Teoricamente esperar essa promise desse jeito assim que o módulo carrega vai atrasar
// o carregamento de qualquer componente que queira usar uma dessas funções, de forma desnecessária,
// mas pro nosso caso aqui tá tudo bem, não vai nem ser perceptivel a demora

const Module = await createModule();

export const create_memoria = Module.create_memoria;
export const FirstFit = Module.FirstFit;
export const BestFit = Module.BestFit;
export const WorstFit = Module.WorstFit;
export const NextFit = Module.NextFit;
export const freeid = Module.freeid;
export const freeaddr = Module.freeaddr;
export const defrag = Module.defrag;
export const gerar_saida = Module.gerar_saida;

export type AllocAlgs = "first" | "best" | "worst" | "next";

export function alloc(mem: Memoria, tamanho: number, algo: AllocAlgs){
    switch (algo) {
        case "first":
            FirstFit(mem, tamanho);
            break;
        case "best":
            BestFit(mem, tamanho);
            break;
        case "worst":
            WorstFit(mem, tamanho);
            break;
        case "next":
            NextFit(mem, tamanho);
            break;
    }
}

// TODO ver com o paulo como ficam essas duas
export function show(mem: Memoria){

}
export function stats(mem: Memoria){
    
}

// Não existe enum, não existe...
export const opcao = new Map([
    ["init", 0],
    ["end", 1],
    ["opt", 2]
]);