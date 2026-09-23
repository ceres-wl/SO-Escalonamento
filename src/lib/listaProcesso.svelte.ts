import type { Processo, ProcessoInput } from "./types";

// Módulo que contém a lista de de processos e seus métodos

// A lista é feita com uma variável reativa por causa da UI,
// mas em geral isso não muda nd na lógica
let listaProcesso: Array<Processo> = $state([]);

export function addProcesso(proc: ProcessoInput){
    const id = listaProcesso.length;

    const procFinal: Processo = {
        ...proc,
        prioridade_dinamica: proc.prioridade_estatica,
        id
    }
    listaProcesso.push(procFinal);
}

export function removerProcesso(procId: number){
    // Ineficiente mas é o que temos
    listaProcesso = listaProcesso.filter((proc) => proc.id != procId).map((proc, i) => { proc.id = i; return proc; });
}

export function listarProcessos(){
    return listaProcesso;
}