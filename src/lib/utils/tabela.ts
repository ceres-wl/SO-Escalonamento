import type { DataPoint } from "../types";
import { getYDomain } from "./procDataDomain";

// Literalmente mais dificil que fazer a tabela gráfica isso aqui,
// vai ficar pra depois

// export function printTabelaDoTrinta(data: Array<DataPoint>){
//     let domain = getYDomain(data);
//     console.log("tempo " + domain.join(" "));
    
//     let finish = false;
//     let time = 0;
//     while(!finish){
//         let str = `${time}- ${time+1} `;
        
//         for(let proc of domain){
//             let procPoints = data.filter((point) => proc == point.id);

//             let end = 0;
//             for(let point of procPoints){
//                 if(point.end > end) end = point.end;
//             }

//             const point = procPoints.find((point) => point.)

//             if(point.start >= time && point.end < time) {
//                 str += "## ";
//                 break;
//             }
//             if(point.start > time && ){

//             }
//         }

//         console.log(str);
//         time++;
//     }
// }