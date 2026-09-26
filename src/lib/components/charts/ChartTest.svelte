<script lang="ts">
	import { BarChart, defaultChartPadding } from 'layerchart';
    import { randomHexColor } from '../../utils/randomColor';
    import type { DataPoint, Processo } from '../../types';
    import { cubicInOut } from 'svelte/easing';

    interface Props{
        data: Array<DataPoint>;
        procs: Array<Processo>;
    }

    interface DisplayDataPoint extends DataPoint{
        displayId: string;
    }

    const { data, procs }: Props = $props();

    let xDomain = $derived(getXDomain(data));
    let yDomain = $derived(getYDomain(data));

    // Calculando os ranges de dados que vão representar processos inativos,
    // é meio que uma gambiarra mas funciona
    const inactive: Array<DisplayDataPoint> = $derived(
        procs.map((proc) =>{
            let end = proc.criacao;
            for(let point of data){
                if(point.id!=proc.id) continue;
                if(point.end > end) end = point.end;
            }

            return{
                start: proc.criacao,
                end,
                id: proc.id,
                displayId: "inactive"
            }
        }));
    
    let time = $state(0);
    const interval = setInterval(() => {
        time++;
        if(time >= data.length) clearInterval(interval);
    }, 1000);

    // Processando os dados pra dar display
    const displayData: Array<DisplayDataPoint> = $derived(
        inactive
        .concat(
            data
            .slice(0, time)
            .map((point) => {
                return {
                    ...point,
                    displayId: point.id
                }}
        ))
    );

    function getXDomain(data: Array<DataPoint>){
        if(data.length == 0) return [0, 0];
        return [
            data.reduce((prev, cur) => prev.start<cur.start?prev:cur, data[0]).start,
            data.reduce((prev, cur) => prev.end>cur.end?prev:cur, data[0]).end
        ];
    }
    function getYDomain(data: Array<DataPoint>){
        return data.map((point) => point.id);
    }
</script>

<div>
    <BarChart 
        data={displayData}
        x={['start', 'end']}
        y="id"
        xBaseline={0}
        {xDomain}
        {yDomain}
        xNice={false}
        c="displayId"
        cDomain={["inactive", ...getYDomain(data)]}
        cRange={["#ffffff07", ...procs.map(() => randomHexColor(256, 128))]}
        grid={{ y: true, bandAlign: 'between' }}
        orientation="horizontal"
        labels={{
            value: (d) => d.current_prio ?? null,
            placement: 'center',
            fill: 'white'
        }}
        padding={defaultChartPadding({ left: 30 })}
        height={400}
        props={{
            bars:{
                motion: { width: 'tween', duration: 1000, easing: cubicInOut }
            }
        }}
    >
    </BarChart>
</div>
