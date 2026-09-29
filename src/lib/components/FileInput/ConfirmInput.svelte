<script lang="ts">
    import type { Algo } from "../../types";
    import BigButton from "../form/bigButton.svelte";

    interface Props{
        algoSelected: Algo;
        delaySimul: number;
        handleSimulateMethod: (e: SubmitEvent) => void;
    }

    let { algoSelected = $bindable("FCFS"), delaySimul = $bindable(), handleSimulateMethod }: Props = $props();

    function handleCompare(){

    }
</script>

<form onsubmit={handleSimulateMethod} class="common-div main">
    <header>
        <label for="select-algo">
            <h2>Seleção do algoritmo de escalonamento</h2>
        </label>
    </header>
    <select id="select-algo" bind:value={algoSelected}>
        <option value="FCFS">First Come, First Served</option>
        <option value="SJF">Shortest Job First</option>
        <option value="SRTF">Shortest Remaining Time First</option>
        <option value="PrioC">Prioridade, sem preempção</option>
        <option value="PrioP">Prioridade, com preempção por prioridade</option>
        <option value="RR">Round-Robin, sem prioridade</option>
        <option value="RR-P-E">Round-Robin, com priodade e envelhecimento</option>
    </select>
    <BigButton onclick={() =>{}}>Simular</BigButton>
    <!-- Ficou confusa essa feature, resolvi tirar -->
    <!-- <label>Delay simulação(ms)
        <input id="setDelayMS" type="number" step="100" bind:value={delaySimul}>
    </label> -->
    <!-- TODO -->
    <!-- <button onclick={handleCompare}>Comparar métricas de todos os métodos</button> -->
</form>

<style>
    .main{
        display: flex;
        flex-direction: column;
        align-items: center;
        justify-content: space-around;
        gap: 5px;

        h2{
            font-size: 2rem;
            margin: 0;
        }

        select{
            font-size: 1.5rem;
            font-weight: bold;
        }
    }
</style>