<script lang="ts">
    import { slide } from "svelte/transition";
    import MetricsArea from "./components/charts/MetricsArea.svelte";
    import ProcSimulationChart from "./components/charts/ProcSimulationChart.svelte";
    import ConfigInput from "./components/FileInput/ConfigInput.svelte";
    import ConfirmInput from "./components/FileInput/ConfirmInput.svelte";
    import GenerateProcs from "./components/FileInput/GenerateProcs.svelte";
    import ProcInput from "./components/FileInput/ProcInput.svelte";
    import { FCFS, prio_c, prio_p, round_robin, round_robin_aging, SJF, SRTF } from "./cpp/api/cppApi";
    import { getProcessos } from "./context/listaProcesso.svelte";
    import type { Algo, DataPointEscalonamento, InfoToCopy, Metrics } from "./types";
    import { formatData } from "./utils/formatData";
    import { printTabela } from "./utils/tabela";
    import { getDisableAnimation } from "../../context/disableAnimation";
    import type { Saida } from "./cpp/api/build/Scheduler_wasm";
    import CommonDiv from "../../components/CommonDiv.svelte";

    let data: Array<DataPointEscalonamento> = $state([]);
    let metrics: Metrics = $state({num_change: 0, turnaround: 0, waiting: 0});

    let simulated = $state(false);
    let delaySimul = $state(500);
    let algoSelected: Algo = $state("FCFS");

    let infoToCopy: InfoToCopy = $state();

    function handleSimulateMethod(e: SubmitEvent){
        e.preventDefault();
        simulated = false;

        if(getProcessos().length == 0) {
            window.alert("Adicione um processo antes!");
            return;
        };

        let saida: Saida | undefined;
        switch (algoSelected) {
            case "FCFS":
                saida = FCFS();
                break;
            case "SJF":
                saida = SJF();
                break;
            case "SRTF":
                saida = SRTF();
                break;
            case "PrioC":
                saida = prio_c();
                break;
            case "PrioP":
                saida = prio_p();
                break;
            case "RR":
                saida = round_robin();
                break;
            case "RR-P-E":
                saida = round_robin_aging();
                break;
            default:
                saida = FCFS();
        }

        infoToCopy = printTabela(saida, getProcessos());
        data = formatData(Array.from(saida.diagrama_tempo));
        metrics = {
            num_change: saida.trocas_contexto,
            turnaround: saida.tt,
            waiting: saida.tw
        };
        simulated = true;
    }
</script>

<!-- Visualização
    TODO Fazer uma área com a opção de rodar todos os algoritmos de uma vez, pra mostrar gráficos com comparação entre eles
        tempo médio de vida
        tempo médio de espera
        número de trocas de contexto
        se sobrar tempo, fazer uma forma do usuário clicar e mostrar a timeline individual do algoritmo que ele clicar nessa área tbm
-->

<div class="main">
    <GenerateProcs bind:simulated />
    <form onsubmit={handleSimulateMethod} class="inputs">
        <div class="flex-row-responsive">
            <ConfigInput bind:simulated/>
            <ProcInput bind:simulated />
        </div>
        <ConfirmInput {handleSimulateMethod} bind:delaySimul bind:algoSelected={() => algoSelected, (val) =>{
            simulated = false;
            algoSelected = val;
        }} />
    </form>
    {#if simulated}
    <CommonDiv>
        <div transition:slide={{duration: getDisableAnimation()()?0:500}} class="visual">
            <MetricsArea {metrics} {infoToCopy} />
            <hr>
            <ProcSimulationChart {data} procs={getProcessos()} delaySimul={delaySimul}/>
        </div>
    </CommonDiv>
    {/if}
</div>

<style>
    @import 'layerchart/core.css';

    .main{
        display: flex;
        flex-direction: column;
        gap: 5px;

        padding: 5px;
    }

    .inputs{
        display: flex;
        flex-direction: column;
        gap: 5px;
    }
</style>