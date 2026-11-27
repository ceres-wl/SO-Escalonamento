import createModule, { type ALGORITHM, type ALGORITHMValue, type PairIB, type VectorPairIB } from "./build/Pages_wasm";

// Teoricamente esperar essa promise desse jeito assim que o módulo carrega vai atrasar
// o carregamento de qualquer componente que queira usar uma dessas funções, de forma desnecessária,
// mas pro nosso caso aqui tá tudo bem, não vai nem ser perceptivel a demora

export const Module = await createModule();

const createVectorPairIB = () => new Module.VectorPairIB();

// Classe wrapper no vec do c++, necessária pra fazer o vector ser statefull
export class StateVector{
    vec: VectorPairIB;
    length;
    constructor(){
        this.vec = $state(createVectorPairIB());
        this.length = $state(this.vec.size());
    }

    resize(){
        throw new Error("Não implementado!!!!!!")
    }

    push_back(p: PairIB){
        this.vec.push_back(p);
        this.length = this.vec.size();
    }

    set(n: number, p: PairIB){
        this.vec.set(n, p);
        this.length = this.vec.size();
    }

    clear(){
        this.vec.delete();
        this.vec = createVectorPairIB();
    }
    
    [Symbol.iterator](){
        const length = this.length;
        let i = 0;
        const vec = this.vec;
        return{
            next(){
                if(i < length){
                    return {value: vec.get(i++), done: false};
                }
                return { value: undefined, done: true }
            }
        }
    }
}

export const pager = Module.pager;

export type ALGORITHM_STR = 
    "FIFO" |
    "LRU" |
    "OTIMO" |
    "CLOCK" |
    "NRU" |
    "LFU" |
    "MFU";

export const ALGO_MAP: Map<ALGORITHM_STR, ALGORITHM> = new Map([
    ["FIFO", { value: Module.ALGORITHM.FIFO.value }],
    ["LRU", { value: Module.ALGORITHM.LRU.value }],
    ["OTIMO", { value: Module.ALGORITHM.OTIMO.value }],
    ["CLOCK", { value: Module.ALGORITHM.CLOCK.value }],
    ["NRU", { value: Module.ALGORITHM.NRU.value }],
    ["LFU", { value: Module.ALGORITHM.LFU.value }],
    ["MFU", { value: Module.ALGORITHM.MFU.value }]
]);

// there is some cool and easy way to do this but i spent way too long trying it so now im doing it the hardcoded way,
// does anybody care? no nobody does, so im doing it.......................
export const INVERSE_ALGO_MAP = new Map([
    [0, "FIFO"],
    [1, "LRU"],
    [2, "OTIMO"],
    [3, "CLOCK"],
    [4, "NRU"],
    [5, "LFU"],
    [6, "MFU"]
]);