<script lang="ts">
    import ProcSimulationChart from "./lib/components/charts/ProcSimulationChart.svelte";
    import ConfigInput from "./lib/components/FileInput/ConfigInput.svelte";
    import ConfirmInput from "./lib/components/FileInput/ConfirmInput.svelte";
    import GenerateProcs from "./lib/components/FileInput/GenerateProcs.svelte";
    import ProcInput from "./lib/components/FileInput/ProcInput.svelte";
    import { FCFS } from "./lib/cpp/api/cppApi";
    import { addProcesso, getProcessos } from "./lib/listaProcesso.svelte";
    import type { DataPoint } from "./lib/types";
    import { formatData } from "./lib/utils/formatData";

    // mockando os dados pra testar
    addProcesso({
        inicio: 0,
        duracao: 5,
        prioridade_estatica: 2
    });
    addProcesso({
        inicio: 0,
        duracao: 2,
        prioridade_estatica: 3
    });
    addProcesso({
        inicio: 1,
        duracao: 4,
        prioridade_estatica: 1
    });
    addProcesso({
        inicio: 3,
        duracao: 1,
        prioridade_estatica: 4
    });
    addProcesso({
        inicio: 5,
        duracao: 2,
        prioridade_estatica: 5
    });

    let data: Array<DataPoint> = $state([]);

    let simulated = $state(false);
    let delaySimul = $state(500);
</script>

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
    <!-- TODO area pra gerar arquivo com processos aleatório, 
     com base em parâmetros tipo 
            range de duração, 
            range de criação,
            range de prioridade,
            quantidade de processos
    -->
    <GenerateProcs/>
    <div class="inputs">
        <div>
            <ConfigInput/>
            <ConfirmInput bind:simulated bind:data bind:delaySimul/>
        </div>
        <ProcInput bind:simulated />
    </div>
    {#if simulated}
    <div class="visual">
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
</style>