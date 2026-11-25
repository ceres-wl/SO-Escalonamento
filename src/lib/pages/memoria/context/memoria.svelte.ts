// Módulo que contém só os dados de configuração

import type { Memoria } from "../cpp/api/build/Memory_wasm";
import { Module } from "../cpp/api/cppApi";

// Não dê reassign nessa variável diretamente, use o método setMemoria
export let memoria: Memoria = $state(Module.create_memoria(0));

// HACK pra dizer que a memória não tá inicializada,
// não posso usar null pq é um saco fzr a tipagem certa com o esmcripten
memoria.id_atual = Infinity;

export function setMemoria(mem: Memoria){
    memoria.id_atual = mem.id_atual;
    memoria.mem = mem.mem;
    memoria.ptr_next_fit = mem.ptr_next_fit;
    memoria.tam_total = mem.tam_total;
}