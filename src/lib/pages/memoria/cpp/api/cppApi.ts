import { setMemoria } from "../../context/memoria.svelte";
import createModule, { type Memoria } from "./build/Memory_wasm";

// Teoricamente esperar essa promise desse jeito assim que o módulo carrega vai atrasar
// o carregamento de qualquer componente que queira usar uma dessas funções, de forma desnecessária,
// mas pro nosso caso aqui tá tudo bem, não vai nem ser perceptivel a demora

export const Module = await createModule();

export const create_memoria = Module.create_memoria;

export const FirstFit = (mem: Memoria, tam: number) =>{
    const s = Module.FirstFit(mem, tam);
    setMemoria(s.mem);
    return s;
}
export const BestFit = (mem: Memoria, tam: number) =>{
    const s = Module.BestFit(mem, tam);
    setMemoria(s.mem);
    return s;
}
export const WorstFit = (mem: Memoria, tam: number) =>{
    const s = Module.WorstFit(mem, tam);
    setMemoria(s.mem);
    return s;
}
export const NextFit = (mem: Memoria, tam: number) =>{
    const s = Module.NextFit(mem, tam);
    setMemoria(s.mem);
    return s;
}

export const freeid = (mem: Memoria, id: number) =>{
    const s = Module.freeid(mem, id);
    setMemoria(s.mem);
    return s;
}
export const freeaddr = (mem: Memoria, addr: number) =>{
    const s = Module.freeaddr(mem, addr);
    setMemoria(s.mem);
    return s;
}

export const defrag = (mem: Memoria, opc: 0 | 1 | 2) =>{
    const s = Module.defrag(mem, {value: opc});
    setMemoria(s.mem);
    return s;
};

export const gerar_saida = Module.gerar_saida;

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
    const saida = Module.gerar_saida(mem, true);
    
    const repeatChar = (char: string, n: number) =>{
        return (new Array(n)).fill(undefined)
        .map(() => char).join("");
    }

    const blocos = Array.from(saida.mem.mem);
    
    return( 
`
Mapa de Memória (${saida.mem.tam_total} bytes)
${repeatChar("-", saida.mem.tam_total+2)}
[${blocos.map(bloco => repeatChar(bloco.livre?".":"#", bloco.tamanho)).join("")}]
[${blocos.map(bloco => repeatChar(bloco.livre?".":bloco.id.toString(), bloco.tamanho)).join("")}]
${repeatChar("-", saida.mem.tam_total+2)}
`
    )
}

export function stats(mem: Memoria){
    // Stats
    const saida = Module.gerar_saida(mem, true);

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