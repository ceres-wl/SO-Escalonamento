import createModule from "../main.js";

// Só criando o módulo e renomeando as funções pra exportar

// Teóricamente esperar essa promise desse jeito assim que o módulo carrega vai atrasar
// o carregamento de qualquer componente que queira usar uma dessas funções, de forma desnecessária,
// mas pro nosso caso aqui tá tudo bem, não vai nem ser perceptivel a demora

const Module = await createModule();

export const add = Module._add;
export const helloWorld = Module._helloWorld;