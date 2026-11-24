// Módulo que contém só os dados de configuração

import createModule, { type Memoria } from "../cpp/api/build/Memory_wasm";
import { create_memoria } from "../cpp/api/cppApi";

// kinda HACK but whatever i dont care!!!!!!!!!!!!!!
export const PromiseModule = createModule();
export const MemModule = await PromiseModule;

// Não dê reassign nessa variável diretamente, use o método setMemoria
export let memoria: Memoria = $state(MemModule.create_memoria(0));

// HACK pra dizer que a memória não tá inicializada,
// não posso usar null pq é um saco fzr a tipagem certa com o esmcripten
memoria.id_atual = Infinity;

export function setMemoria(mem: Memoria){
    memoria.id_atual = mem.id_atual;
    memoria.mem = mem.mem;
    memoria.ptr_next_fit = mem.ptr_next_fit;
    memoria.tam_total = mem.tam_total;
}