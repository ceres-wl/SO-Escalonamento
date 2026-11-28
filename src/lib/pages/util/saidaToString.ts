import type { Saida } from "../paginacao/cpp/api/build/Pages_wasm";
import { INVERSE_ALGO_MAP } from "../paginacao/cpp/api/cppApi.svelte";

export function saidaToString(saida: Saida, verbose: boolean){
    return(`\
${!verbose?"":Array.from(saida.verb_info)
.map((info) => 
`${info.passo} ref=${info.pag_ref} [ ${Array.from(info.cur_frames).map(e => e==-1?".":e.toString()).join(" ")} ] ${info.hit?"acerto":"falta"}${info.removed!=-1?` (remove ${info.removed})`:""}`)
.join("\n")}

Algoritmo: ${INVERSE_ALGO_MAP.get(saida.algo.value)}
Frames: ${saida.frames}
Referências: ${saida.referencias}
Faltas de página: ${saida.page_fault}
Taxa de faltas: ${saida.fault_ratio.toPrecision(2)}%
Evicções: ${saida.evictions}
Escritas em disco:${saida.disk_writes}
Conjunto residente final:
frame_ids: ${Array.from(saida.frame_ids).map(e => e.toString()).join(" ")}
page_ids:  ${Array.from(saida.page_ids).map(e => e.toString()).join(" ")}\
`);
}