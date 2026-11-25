import { memoria, setMemoria } from "../context/memoria.svelte";
import { alloc, create_memoria, defrag, freeaddr, freeid, opcao, show, stats, type AllocAlgs } from "../cpp/api/cppApi";
import type { Command } from "../types";

export function runCommand(cmd: Command){
    function parseNumStr(str: string){
        const arg = Math.floor(Number(str));
        if(isNaN(arg)) throw new Error(`Argumento "${str}" inválido`);
        return arg;
    }

    // top switch cases mais feios já escritos
    switch (cmd.cmd) {
        case "init":
            setMemoria(create_memoria(parseNumStr(cmd.args[0])));

            cmd.output = "";
            break;
        case "alloc":
            if(memoria.id_atual == Infinity) throw new Error("Memória não inicializada!");
            const alg = cmd.args[1];
            // Não se assuste! É feio mas funciona... contanto que ninguem mexa em mais nada, nunca mais...
            if(!["first", "best", "worst", "next"].some((e) => e == alg)) throw new Error("Algoritmo inválido!");

            alloc(memoria, parseNumStr(cmd.args[0]), alg as AllocAlgs);

            cmd.output = "";
            break;
        case "freeid":
            if(memoria.id_atual == Infinity) throw new Error("Memória não inicializada!");

            freeid(memoria, parseNumStr(cmd.args[0]));

            cmd.output = "";
            break;
        case "freeaddr":
            if(memoria.id_atual == Infinity) throw new Error("Memória não inicializada!");

            freeaddr(memoria, parseNumStr(cmd.args[0]));

            cmd.output = "";
            break;
        case "show":
            if(memoria.id_atual == Infinity) throw new Error("Memória não inicializada!");

            cmd.output = show(memoria);

            break;
        case "stats":
            if(memoria.id_atual == Infinity) throw new Error("Memória não inicializada!");

            cmd.output = stats(memoria);

            break;
        case "defrag":
            if(memoria.id_atual == Infinity) throw new Error("Memória não inicializada!");
            if(!opcao.has(cmd.args[0])) throw new Error("Opção inválida!");

            defrag(memoria, opcao.get(cmd.args[0]) as 0|1|2);

            cmd.output = "";
            break;
        default:
            throw new Error("Comando inválido!");
    }
}