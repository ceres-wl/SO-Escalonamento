<script lang="ts">
    import { FCFS } from "../../cpp/api/cppApi";
    import { getProcessos } from "../../listaProcesso.svelte";
    import type { DataPoint, Metrics } from "../../types";
    import { formatData } from "../../utils/formatData";

    interface Props{
        simulated: boolean;
        metrics: Metrics
        data: Array<DataPoint>;
        delaySimul: number;
    }

    let { simulated = $bindable(), metrics = $bindable(), data = $bindable(), delaySimul = $bindable() }: Props = $props();

    type Algorithm = "FCFS" | "SJF" | "SRTF" | "PrioC" | "PrioP" | "RR" | "RR-P-E";
    let algoSelected: Algorithm = $state("FCFS");

    function handleSimulateMethod(){
        if(getProcessos().length == 0) return;

        let saida;
        switch (algoSelected) {
            case "FCFS":
                saida = FCFS();
                break;
            case "SJF":
            case "SRTF":
            case "PrioC":
            case "PrioP":
            case "RR":
            case "RR-P-E":
            default:
                saida = FCFS();
        }

        data = formatData(Array.from(saida.diagrama_tempo));
        metrics = {
            num_change: saida.trocas_contexto,
            turnaround: saida.tt,
            waiting: saida.tw
        };
        simulated = true;
    }

    function handleCompare(){

    }
</script>

<div class="common-div confirm">
    <h2>Parâmetros simulação</h2>
    <div>
        <label>Algoritmo
            <select id="select-algo" bind:value={algoSelected}>
                <option value="FCFS">First Come, First Served</option>
                <option value="SJF">Shortest Job First</option>
                <option value="SRTF">Shortest Remaining Time First</option>
                <option value="PrioC">Prioridade, sem preempção</option>
                <option value="PrioP">Prioridade, com preempção por prioridade</option>
                <option value="RR">Round-Robin, sem prioridade</option>
                <option value="RR-P-E">Round-Robin, com priodade e envelhecimento</option>
            </select>
        </label>
        <label>Delay simulação(ms)
            <input id="setDelayMS" type="number" step="100" bind:value={delaySimul}>
        </label>
        <button onclick={handleSimulateMethod}>Simular</button>
    </div>
    <button onclick={handleCompare}>Comparar métricas de todos os métodos</button>
</div>

<style>
    .confirm{
        h2{
            margin: 0.5rem 0;
        }
    }

    .confirm{
        margin-top: 5px;
    }
</style>