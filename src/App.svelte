<script lang="ts">
    import ChartTest from "./lib/components/charts/ChartTest.svelte";
    import ConfigInput from "./lib/components/FileInput/ConfigInput.svelte";
    import ProcInput from "./lib/components/FileInput/ProcInput.svelte";
    import { add_proc, get_procs } from "./lib/cpp/api/cppApi";
    import { addProcesso, getProcessos } from "./lib/listaProcesso.svelte";
    import type { DataPoint } from "./lib/types";

    // Testando o wasm
    // let procs = get_procs();
    // if(procs){
    //     console.log(Array.from(procs));
    //     procs.push_back({inicio: 10, duracao: 15, prioridade_estatica: 20});
    //     add_proc({inicio: 500, duracao: 1500, prioridade_estatica: 2000})
    //     console.log(Array.from(procs));
    //     console.log(procs.size());
    // }

    // mockando os dados pra testar
    addProcesso({
        criacao: 0,
        duracao: 5,
        prioridade_estatica: 2
    });
    addProcesso({
        criacao: 0,
        duracao: 2,
        prioridade_estatica: 3
    });
    addProcesso({
        criacao: 1,
        duracao: 4,
        prioridade_estatica: 1
    });
    addProcesso({
        criacao: 3,
        duracao: 1,
        prioridade_estatica: 4
    });
    addProcesso({
        criacao: 5,
        duracao: 2,
        prioridade_estatica: 5
    });

	const data: Array<DataPoint> = [
        {
            id: "P0",
            start: 0,
            end: 2
        },
        {
            id: "P1",
            start: 2,
            end: 4
        },
        {
            id: "P2",
            start: 4,
            end: 6
        },
        {
            id: "P0",
            start: 6,
            end: 8
        },
        {
            id: "P3",
            start: 8,
            end: 9
        },
        {
            id: "P4",
            start: 9,
            end: 11
        },
        {
            id: "P2",
            start: 11,
            end: 13
        },
        {
            id: "P0",
            start: 13,
            end: 14
        },
	];

</script>

<!-- Estilo
    TODO icones? yes or no
    TODO background image? ou deixa a cor msm
    TODO deixar tudo redondo provavelmente, ou não seila
-->

<!-- Visualização
    TODO Mostrar o gráfico com timeline dos processos

    TODO Fazer uma área com a opção de rodar todos os algoritmos de uma vez, pra mostrar gráficos com comparação entre eles
        tempo médio de vida
        tempo médio de espera
        número de trocas de contexto
        se sobrar tempo, fazer uma forma do usuário clicar e mostrar a timeline individual do algoritmo que ele clicar nessa área tbm
-->

<main>
    <div class="inputs">
        <ConfigInput/>
        <ProcInput/>
    </div>
    <div class="visual">
        <ChartTest {data} procs={getProcessos()}/>
    </div>
</main>

<style>
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
    }
</style>