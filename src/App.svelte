<script lang="ts">
    import ProcSimulationChart from "./lib/components/charts/ProcSimulationChart.svelte";
    import ConfigInput from "./lib/components/FileInput/ConfigInput.svelte";
    import ConfirmInput from "./lib/components/FileInput/ConfirmInput.svelte";
    import GenerateProcs from "./lib/components/FileInput/GenerateProcs.svelte";
    import ProcInput from "./lib/components/FileInput/ProcInput.svelte";
    import { getProcessos } from "./lib/listaProcesso.svelte";
    import type { DataPoint, Metrics } from "./lib/types";

    let data: Array<DataPoint> = $state([]);
    let metrics: Metrics = $state({num_change: 0, turnaround: 0, waiting: 0});

    let simulated = $state(false);
    let delaySimul = $state(500);
</script>

<!-- Acessibilidade
    TODO transformar todos os inputs em forms, pra navegar com enter e tal
    TODO responsividade :(
-->

<!-- Estilo
    TODO estilizar as coisas, eu quero manter minimalista mas tá faltando mexer numas coisas
        titulo da página
        área de confirmar simualação
        rever cores
-->

<!-- Visualização
    TODO Fazer uma área com a opção de rodar todos os algoritmos de uma vez, pra mostrar gráficos com comparação entre eles
        tempo médio de vida
        tempo médio de espera
        número de trocas de contexto
        se sobrar tempo, fazer uma forma do usuário clicar e mostrar a timeline individual do algoritmo que ele clicar nessa área tbm
-->

<main>
    <h1>Simulação de escalonamento</h1>
    <GenerateProcs bind:simulated />
    <div class="inputs">
        <div>
            <ConfigInput/>
            <ConfirmInput bind:metrics bind:simulated bind:data bind:delaySimul/>
        </div>
        <ProcInput bind:simulated />
    </div>
    {#if simulated}
    <div class="visual">
        <!-- TODO estilozinho melhor pra isso-->
        <p>TT: {metrics.turnaround} | TW: {metrics.waiting} | trocas de contexto: {metrics.num_change}</p>
        <ProcSimulationChart {data} procs={getProcessos()} delaySimul={delaySimul}/>
    </div>
    {/if}
</main>

<style>
    @import 'layerchart/core.css';
    @import "./lib/components/commonDiv.css";

    main{
        width: 120ch;
        margin: 0 auto;

        display: flex;
        flex-direction: column;
        gap: 5px;

        padding: 5px;
    }

    .inputs{
        display: flex;
        flex-direction: row;
        gap: 5px;

        height: 40vh;
    }

    .visual{
        background-color: var(--color-bg);
    }

    :global(html, body){
        margin: 0;
    }

    :global(body){
        background-color: aquamarine;
    }

    :global(*){
        box-sizing: border-box;
    }

    :global(:root){
        /* TODO decidir cores */
        --color-primary: whitesmoke;
        --color-secondary: lightgray;
        --color-accent: rgb(255, 106, 136);
        --color-bg: white;
    }

    :global(button, input, select){
        background-color: var(--color-accent);
        border: 1px solid black;
        color: white;
    }
</style>