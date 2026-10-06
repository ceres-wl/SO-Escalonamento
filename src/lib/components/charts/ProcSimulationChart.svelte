<script lang="ts">
	import { BarChart, defaultChartPadding } from 'layerchart';
    import { randomHexColor } from '../../utils/randomColor';
    import type { DataPoint, Processo } from '../../types';
    import { cubicOut } from 'svelte/easing';
    import { getXDomain, getYDomain } from '../../utils/procDataDomain';
    import BigButton from '../form/bigButton.svelte';
    import { getDisableAnimation } from '../../context/disableAnimation';

    interface Props{
        data: Array<DataPoint>;
        procs: Array<Processo>;
        delaySimul: number;
    }

    interface DisplayDataPoint extends DataPoint{
        displayId: string;
    }

    const { data, procs, delaySimul = 500 }: Props = $props();

    let xDomain = $derived(getXDomain(data));
    let yDomain = $derived(getYDomain(data).sort());

    // Calculando os ranges de dados que vão representar processos inativos,
    // é meio que uma gambiarra mas funciona -> Uma opção que talvez fosse melhor 
    // seria usar series e stackar elas: https://www.layerchart.com/docs/components/BarChart#grouped-and-stacked
    const inactive: Array<DisplayDataPoint> = $derived(
        procs.map((proc) =>{
            let end = proc.inicio;
            for(let point of data){
                if(point.id!=proc.id) continue;
                if(point.end > end) end = point.end;
            }

            return{
                start: proc.inicio,
                end,
                id: proc.id,
                displayId: "inactive"
            }
        }));
    
    let time = $state(0);
    let interval = 0;
    
    function setupAutoSimulation(delay: number){
        clearInterval(interval);
        if(delay == 0 || getDisableAnimation()()){
            time = Infinity;
            return;
        }
        
        interval = setInterval(() => {
            time++;
            if(time >= data.length){
                clearInterval(interval);
            };
        }, delay);
    }

    $effect(() =>{
        setupAutoSimulation(3000/data.length);
    })

    // Processando os dados pra dar display
    const displayData: Array<DisplayDataPoint> = $derived(
        inactive
        .concat(
            data
            .slice(0, time)
            .map((point) => {
                return {
                    ...point,
                    displayId: point.id,
                    // Mostrando a prioridade estática no lugar da dinâmica
                    current_prio: procs.find((proc) => point.id == proc.id)?.prioridade_estatica ?? undefined
                }}
        ))
    );

</script>

<div class="chart-div">
    <!-- Ficou confusa essa feature, resolvi tirar -->
    <!-- <label> Simular automaticamente 
        <input type="checkbox" disabled={disableSimulationCheckbox} bind:checked={automaticSimulation} onclick={(e) =>{
            if(automaticSimulation){
                clearInterval(interval);
                return;
            }
            setupAutoSimulation(delaySimul);
        }}>
    </label> -->
    <header>
        <h2>Diagrama de tempo da execução</h2>
        <div class="controls">
            <BigButton onclick={() => {time=0; /*disableSimulationCheckbox = false*/}}>Resetar</BigButton>
            <BigButton onclick={() => time=Infinity}>Completar</BigButton>
        </div>
    </header>
    <BarChart class="chart"
        data={displayData}
        x={['start', 'end']}
        y="id"
        xBaseline={0}
        {xDomain}
        {yDomain}
        xNice={false}
        c="displayId"
        cDomain={["inactive", "Nenhum", ...yDomain]}
        cRange={["#ffffff07", "#000000", ...procs.map(() => randomHexColor(256, 128))]}
        grid={{ y: true, bandAlign: 'between' }}
        orientation="horizontal"
        labels={{
            value: (d) => d.current_prio ?? null,
            placement: 'center',
            fill: 'white'
        }}
        padding={defaultChartPadding({ left: 50 })}
        height={400}
        props={{
            labels:{
            },
            bars:{
                motion: { width: { type: "tween", duration: 400, easing: cubicOut } }
            }
        }}
        // transform={{ mode: 'domain' }}
    >
    </BarChart>
</div>

<style>
    @import "/src/lib/components/charts/chartsDiv.css";

    .controls{
        display: flex;
        flex-direction: column;
        align-items: center;
        justify-content: center;
        width: 50%;

        gap: 0.5rem;
    }
</style>