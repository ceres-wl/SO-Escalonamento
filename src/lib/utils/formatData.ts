import type { DataPoint } from "../types";

export function formatData(data: Array<number>){
    if(data.length == 0) return [];

    const formated: Array<DataPoint> = [];
    
    let start = 0;
    let lastProc = data[0];
    for(let i = 1; i <= data.length; i++){
        if(lastProc == data[i] && i != data.length) continue;
        formated.push({
            start,
            end: i,
            id: data[i-1] == -1?"Nenhum":`P${data[i-1]}`,
            current_prio: undefined
        })
        start = i;
        lastProc = data[i];
    }

    return formated;
}