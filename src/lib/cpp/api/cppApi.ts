import createModule from "../main.js";

// Teoricamente esperar essa promise desse jeito assim que o módulo carrega vai atrasar
// o carregamento de qualquer componente que queira usar uma dessas funções, de forma desnecessária,
// mas pro nosso caso aqui tá tudo bem, não vai nem ser perceptivel a demora

const Module = await createModule();

/**
 * Não deletar o vector que isso retorna, é uma referência controlada pelo c++
 */
export const get_procs = Module.get_procs;

export const add_proc = Module.add_proc;