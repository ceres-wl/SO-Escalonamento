<script lang="ts">
    import { slide } from "svelte/transition";
    import MetricsArea from "./lib/components/charts/MetricsArea.svelte";
    import ProcSimulationChart from "./lib/components/charts/ProcSimulationChart.svelte";
    import ConfigInput from "./lib/components/FileInput/ConfigInput.svelte";
    import ConfirmInput from "./lib/components/FileInput/ConfirmInput.svelte";
    import GenerateProcs from "./lib/components/FileInput/GenerateProcs.svelte";
    import ProcInput from "./lib/components/FileInput/ProcInput.svelte";
    import { FCFS, prio_c, prio_p, round_robin, round_robin_aging, SJF, SRTF } from "./lib/cpp/api/cppApi";
    import { getProcessos } from "./lib/context/listaProcesso.svelte";
    import type { Algo, DataPoint, InfoToCopy, Metrics } from "./lib/types";
    import { formatData } from "./lib/utils/formatData";
    import { printTabela } from "./lib/utils/tabela";
    import { getDisableAnimation, setDisableAnimation } from "./lib/context/disableAnimation";
    import type { Saida } from "./lib/cpp/api/build/Scheduler_wasm";

    let data: Array<DataPoint> = $state([]);
    let metrics: Metrics = $state({num_change: 0, turnaround: 0, waiting: 0});

    let simulated = $state(false);
    let delaySimul = $state(500);
    let algoSelected: Algo = $state("FCFS");

    let disableAnimation = $state(false);
    setDisableAnimation(() => disableAnimation);

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

<main>
    <div class="header">
        <h1>Simulação de escalonamento</h1>
        
        <label> Desativar animações
            <input type="checkbox" bind:checked={disableAnimation} >
        </label>
    </div>
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
    <div transition:slide={{duration: getDisableAnimation()()?0:500}} class="visual common-div">
        <MetricsArea {metrics} {infoToCopy} />
        <hr>
        <ProcSimulationChart {data} procs={getProcessos()} delaySimul={delaySimul}/>
    </div>
    {/if}
</main>

<style>
    @import 'layerchart/core.css';
    @import "./lib/components/commonDiv.css";

    main{
        max-width: 120ch;
        margin: 0 auto;

        display: flex;
        flex-direction: column;
        gap: 5px;

        padding: 5px;
    }

    .header{
        display: flex;
        align-items: center;
        justify-content: space-between;

        color: white;
    }

    .inputs{
        display: flex;
        flex-direction: column;
        gap: 5px;
    }

    .flex-row-responsive{
        display: flex;
        flex-direction: row;
        gap: 5px;

        @media screen and (max-width: 48em) {
            flex-direction: column;
        }
    }

    :global(html, body){
        margin: 0;
    }

    :global(body){
        background-color: rgb(20, 92, 68);
    }

    :global(*){
        box-sizing: border-box;
    }

    :global(:root){
        /* TODO decidir cores */
        --color-primary: whitesmoke;
        --color-secondary: rgb(235, 235, 235);
        --color-accent: rgb(255, 106, 136);
        --color-bg: white;

        --color-input-bg: rgb(255, 106, 136);
        --color-input-bg-hover: rgb(155, 65, 83);
    }

    :global(button, input, select){
        background-color: var(--color-input-bg);
        border: 1px solid black;
        color: white;

        text-align: center;
    }

    :global(button){
        background-color: var(--color-input-bg);  
        cursor: pointer;

        &:hover{
            background-color: var(--color-input-bg-hover);
        }
    }

    :global(input[type=number]){
        font-size: 1rem;
        max-width: 10ch;
    }

    :global(h1, h2, h3){
        font-family: 'Franklin Gothic Medium', 'Arial Narrow', Arial, sans-serif;
        font-variant: small-caps;
    }
</style>