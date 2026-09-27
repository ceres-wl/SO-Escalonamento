import { add_proc, clear_procs } from "./cpp/api/cppApi";
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
    
    add_proc({
        ...procFinal,
        id: listaProcesso.length
    });

    listaProcesso.push(procFinal);
}

export function removerProcesso(procId: string){
    // Extramamente ineficiente, mas não lembro como faz isso no c++ então tou fzd no js e copiando tudo pra lá :P
    listaProcesso = listaProcesso.filter((proc) => proc.id != procId).map((proc, i) => { proc.id = `P${i}`; return proc; });
    clear_procs();
    for(let i = 0; i < listaProcesso.length; i++){
        add_proc({
            ...listaProcesso[i],
            id: i
        });
    }
}

export function getProcessos(){
    return listaProcesso;
}