<script lang="ts">
	import { BarChart, defaultChartPadding } from 'layerchart';
    import { cubicOut } from 'svelte/easing';
    import type { DataPoint } from '../../types';
    import BigButton from '../form/bigButton.svelte';
    import { randomHexColor } from '../../utils/randomColor';

    interface Props{
        title: string;
        data: Array<DataPoint>;
        getXDomain: (data: Array<DataPoint>) => Array<any>;
        getYDomain: (data: Array<DataPoint>) => Array<any>;
    }

    interface DisplayDataPoint extends DataPoint{
        displayId: string;
    }

    const { title, data, getXDomain, getYDomain }: Props = $props();

    let xDomain = $derived(getXDomain(data));
    let yDomain = $derived(getYDomain(data).sort());

    // Processando os dados pra dar display
    const displayData: Array<DisplayDataPoint> = $derived(
        data
        .map((point) => {
            return {
                ...point,
                displayId: point.id
            }}
    ));
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
        <h2>{title}</h2>
        <!-- <div class="controls"> Pensar se faço um controls generico ou nn, qualquer coisa dá pra fzr um snippet
            <BigButton onclick={() => {time=0; /*disableSimulationCheckbox = false*/}}>Resetar</BigButton>
            <BigButton onclick={() => time=Infinity}>Completar</BigButton>
        </div> -->
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
        cRange={["#ffffff07", "#000000", ...data.map(() => randomHexColor(256, 128))]}
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
    >
    </BarChart>
</div>

<style>
    /* @import "/src/lib/components/charts/chartsDiv.css"; */

    /* .controls{
        display: flex;
        flex-direction: column;
        align-items: center;
        justify-content: center;
        width: 50%;

        gap: 0.5rem;
    } */
</style>