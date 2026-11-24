import { MemModule, setMemoria } from "../../context/memoria.svelte";
import createModule, { type Memoria, type Opcao } from "./build/Memory_wasm";

// Teoricamente esperar essa promise desse jeito assim que o módulo carrega vai atrasar
// o carregamento de qualquer componente que queira usar uma dessas funções, de forma desnecessária,
// mas pro nosso caso aqui tá tudo bem, não vai nem ser perceptivel a demora

export const create_memoria = MemModule.create_memoria;

export const FirstFit = (mem: Memoria, tam: number) =>{
    const s = MemModule.FirstFit(mem, tam);
    setMemoria(s.mem);
    return s;
}
export const BestFit = (mem: Memoria, tam: number) =>{
    const s = MemModule.BestFit(mem, tam);
    setMemoria(s.mem);
    return s;
}
export const WorstFit = (mem: Memoria, tam: number) =>{
    const s = MemModule.WorstFit(mem, tam);
    setMemoria(s.mem);
    return s;
}
export const NextFit = (mem: Memoria, tam: number) =>{
    const s = MemModule.NextFit(mem, tam);
    setMemoria(s.mem);
    return s;
}

export const freeid = (mem: Memoria, id: number) =>{
    const s = MemModule.freeid(mem, id);
    setMemoria(s.mem);
    return s;
}
export const freeaddr = (mem: Memoria, addr: number) =>{
    const s = MemModule.freeaddr(mem, addr);
    setMemoria(s.mem);
    return s;
}

export const defrag = (mem: Memoria, opc: Opcao) =>{
    const s = MemModule.defrag(mem, opc);
    setMemoria(s.mem);
    return s;
};

export const gerar_saida = MemModule.gerar_saida;

export type AllocAlgs = "first" | "best" | "worst" | "next";

export function alloc(mem: Memoria, tamanho: number, algo: AllocAlgs){
    // TODO ver o struct se a memória foi alocada
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
    // Mostrar memória
}
export function stats(mem: Memoria){
    // Stats
}

// Não existe enum, não existe...
export const opcao = new Map([
    ["init", 0],
    ["end", 1],
    ["opt", 2]
]);