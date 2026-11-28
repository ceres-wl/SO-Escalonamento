export function getTrace(trace: "silberschatz2001"|"belady"|"escritas"){
    return TRACES.get(trace) as string;
}

const TRACES = new Map([
    ["silberschatz2001",`
7
0
1
2
0
3
0
4
2
3
0
3
2
1
2
0
1
7
0
1
    `],
    ["belady",`
1
2
3
4
1
2
5
1
2
3
4
5
    `],
    ["escritas",`
1 W
2 R
3 W
1 R
4 R
2 W
5 R
3 R
1 W
4 R
    `]
])