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
    switch (algo) {
        case "first": {
                const s = FirstFit(mem, tamanho);
                if(!s.conseguiu_alocar) throw new Error("Espaço indisponivel!");
                return s;
            }
        case "best": {
                const s = BestFit(mem, tamanho);
                if(!s.conseguiu_alocar) throw new Error("Espaço indisponivel!");
                return s;
            }
        case "worst": {
                const s = WorstFit(mem, tamanho);
                if(!s.conseguiu_alocar) throw new Error("Espaço indisponivel!");
                return s;
            }
        case "next": {
                const s = NextFit(mem, tamanho);
                if(!s.conseguiu_alocar) throw new Error("Espaço indisponivel!");
                return s;
            }
    }
}

// Por incrivel q pareça, essa é uma das funções mais bonitas que eu já escrevi na vida
export function show(mem: Memoria){
    // Mostrar memória
    const saida = MemModule.gerar_saida(mem, true);
    
    const repeatChar = (char: string, n: number) =>{
        return (new Array(n)).fill(undefined)
        .map(() => char).join("");
    }

    const blocosCheios = Array.from(saida.mem.mem)
    .filter(bloco => !bloco.livre)
    .map(bloco => {
        return {id: bloco.id, tam: bloco.tamanho}
    });
    
    return( 
`
Mapa de Memória (${saida.mem.tam_total} bytes)
${repeatChar("-", saida.mem.tam_total+2)}
[${blocosCheios.map(bloco => repeatChar("#", bloco.tam)).join("")}${repeatChar(".", saida.livre)}]
[${blocosCheios.map(bloco => repeatChar(bloco.id.toString(), bloco.tam)).join("")}${repeatChar(".", saida.livre)}]
${repeatChar("-", saida.mem.tam_total+2)}
`
    )
}

export function stats(mem: Memoria){
    // Stats
    const saida = MemModule.gerar_saida(mem, true);

    return(
// TODO essa primeira linha fica numa linha só mesmo? o que é o +? qual a diferença do + pro (usado=)
`
Blocos ativos: [id=1] @0 +10B (usado=10B) | [id=3] @10 +6B (usado=6B)
== Estatísticas ==
Tamanho total: ${saida.mem.tam_total} bytes
Ocupado: ${saida.ocupado} bytes | Livre: ${saida.livre}} bytes
Buracos (fragmentação externa): ${saida.buracos}
Maior buraco livre: ${saida.maior_buraco_livre} bytes
Uso efetivo: ${saida.uso_efetivo*100}%
`
    )
}

// Não existe enum, não existe...
export const opcao = new Map([
    ["init", 0],
    ["end", 1],
    ["opt", 2]
]);