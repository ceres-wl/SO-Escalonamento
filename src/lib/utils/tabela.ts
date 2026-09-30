
import type { Saida } from "../../lib/cpp/api/build/Scheduler_wasm";
import type { DataPoint, Processo } from "../types";

export function printTabela(saida: Saida, procs: Array<Processo>){
    const data: Array<number> = Array.from(saida.diagrama_tempo);
    const procIds = new Set(data);

    let metricasStr = 
`tt: ${saida.tt}
tw: ${saida.tw}
trocas de contexto: ${saida.trocas_contexto}`;

    let diagramaStr = "";
    
    const inactive: Array<DataPoint> = (
        procs.map((proc) =>{
            let end = proc.inicio;
            let remaining = proc.duracao;
            for(let i = 0; i < data.length; i++){
                if(`P${data[i]}` == proc.id) remaining--;
                if(remaining == 0){
                    end = i+1;
                    break;
                }
            }

            return{
                start: proc.inicio,
                end,
                id: proc.id
            }
        }));

    diagramaStr += "tempo " + Array.from(procIds.values()).sort().map((id) => `P${id}`).join(" ") + "\n";
    for(let i = 0; i < data.length; i++){
        diagramaStr += `${i}- ${i+1} ` + 
            Array.from(procIds.values()).sort().map((id) =>{
                if(data[i] == id) return "##";
                const inactiveData = inactive.find((proc) => proc.id == `P${id}`);
                if(inactiveData && inactiveData.start <= i && i < inactiveData.end ) return "--";
                return "  ";
            })
            .join(" ") + "\n";
    }

    console.log(metricasStr);
    console.log(diagramaStr);
    return {diagramaStr, metricasStr};
}