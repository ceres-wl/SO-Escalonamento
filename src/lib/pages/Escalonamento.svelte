<script lang="ts">
    import { slide } from "svelte/transition";
    import MetricsArea from "../components/charts/MetricsArea.svelte";
    import ProcSimulationChart from "../components/charts/ProcSimulationChart.svelte";
    import ConfigInput from "../components/FileInput/ConfigInput.svelte";
    import ConfirmInput from "../components/FileInput/ConfirmInput.svelte";
    import GenerateProcs from "../components/FileInput/GenerateProcs.svelte";
    import ProcInput from "../components/FileInput/ProcInput.svelte";
    import { FCFS, prio_c, prio_p, round_robin, round_robin_aging, SJF, SRTF } from "../cpp/escalonamento/api/cppApi";
    import { getProcessos } from "../context/listaProcesso.svelte";
    import type { Algo, DataPoint, InfoToCopy, Metrics } from "../types";
    import { formatData } from "../utils/formatData";
    import { printTabela } from "../utils/tabela";
    import { getDisableAnimation, setDisableAnimation } from "../context/disableAnimation";
    import type { Saida } from "../cpp/api/build/Scheduler_wasm";
    import SchedulingIcon from '../../assets/scheduling_nobg.webp';
    import External from '~icons/fa-solid/external-link-alt'

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
        <div class="flex-center">
            <img class="pixelated" src={SchedulingIcon} alt="Icone de temporizador">
            <h1>Simulação de escalonamento</h1>
        </div>
        
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
    <footer>
        <p>
            Projeto criado para a cadeira de Sistemas Operacionais da UFC
        </p>
        <p><a target="_blank" href="https://github.com/ceres-wl/SO-Escalonamento">Link para o Repositório <External/></a></p>
    </footer>
</main>

<style>
    @import 'layerchart/core.css';
    @import "../components/commonDiv.css";

    main{
        max-width: 120ch;
        margin: 0 auto;

        display: flex;
        flex-direction: column;
        gap: 5px;

        padding: 5px;
    }

    footer{
        display: flex;
        align-items: center;
        justify-content: space-between;

        background-color: var(--color-primary);

        font-weight: bold;

        a{
            text-decoration: none;

            &:hover{
                text-decoration: underline dotted;
            }
        }

        padding: 0.5rem;
    }

    .header{
        display: flex;
        align-items: center;
        justify-content: space-between;

        color: white;

        h1{
            display: inline;
            font-size: 2rem;
        }
        img{
            height: 4rem;
            display: inline;
        }
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
</style>