import type { DataPoint } from "../types";

export function getXDomain(data: Array<DataPoint>){
    if(data.length == 0) return [0, 0];
    return [
        data.reduce((prev, cur) => prev.start<cur.start?prev:cur, data[0]).start,
        data.reduce((prev, cur) => prev.end>cur.end?prev:cur, data[0]).end
    ];
}
export function getYDomain(data: Array<DataPoint>){
    const set: Set<string> = new Set();
    for(let point of data) set.add(point.id);
    return Array.from(set.values());
}