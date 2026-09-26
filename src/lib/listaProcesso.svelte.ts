import type { Processo, ProcessoInput } from "./types";

// Módulo que contém a lista de de processos e seus métodos

// A lista é feita com uma variável reativa por causa da UI,
// mas em geral isso não muda nd na lógica
let listaProcesso: Array<Processo> = $state([]);

export function addProcesso(proc: ProcessoInput){
    const id = `P${listaProcesso.length}`;

    const procFinal: Processo = {
        ...proc,
        prioridade_dinamica: proc.prioridade_estatica,
        id
    }
    listaProcesso.push(procFinal);
}

export function removerProcesso(procId: string){
    // Ineficiente mas é o que temos
    listaProcesso = listaProcesso.filter((proc) => proc.id != `P${procId}`).map((proc, i) => { proc.id = `P${i}`; return proc; });
}

export function getProcessos(){
    return listaProcesso;
}