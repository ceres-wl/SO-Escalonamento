import { add_proc, clear_procs } from "../cpp/api/cppApi";
import type { Processo, ProcessoInput } from "../types";

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
    
    add_proc({
        ...procFinal,
        id: listaProcesso.length
    });

    listaProcesso.push(procFinal);
}

export function updateProcesso(procId: string, inicio: number, duracao: number, prio: number){
    const proc = listaProcesso[listaProcesso.findIndex((proc) => proc.id == procId)];
    proc.inicio = inicio;
    proc.duracao = duracao;
    proc.prioridade_estatica = prio;
    syncProcesses();
}

export function removeProcesso(procId: string){
    listaProcesso = listaProcesso.filter((proc) => proc.id != procId).map((proc, i) => { proc.id = `P${i}`; return proc; });
    syncProcesses();
}

export function syncProcesses(){
    // Extramamente ineficiente, mas é a forma mais fácil de fzr isso :P
    clear_procs();
    for(let i = 0; i < listaProcesso.length; i++){
        add_proc({
            ...listaProcesso[i],
            id: i
        });
    }
}

export function clearProcs(){
    listaProcesso = [];
    clear_procs();
}

export function getProcessos(){
    return listaProcesso;
}