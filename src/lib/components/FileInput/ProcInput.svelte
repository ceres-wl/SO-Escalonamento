<script lang="ts">
    import { addProcesso, removeProcesso, getProcessos, updateProcesso, clearProcs } from "../../context/listaProcesso.svelte";
    import type { Processo } from "../../types";
    import CommonFileInput from "./CommonFileInput.svelte";
    import Times from "~icons/fa-solid/times";

    interface Props{
        simulated: boolean;
    }

    let { simulated = $bindable() }: Props = $props();

    async function handleProcFile(files: FileList){
        if(!files || !files[0]) return;
        const txt = await files[0].text();

        for(const line of txt.split("\n")){
            if(line.trim() == "") continue;

            const [criacao, duracao, prioridade_estatica] = line.split(" ").map((str) => Number(str));
            if([criacao, duracao, prioridade_estatica].some(isNaN)) throw new Error("Valor não é um número");

            addProcesso({
                inicio: criacao,
                duracao,
                prioridade_estatica
            });
        }
    }

    function updateProc(process: Processo){
        updateProcesso(process.id, process.inicio, process.duracao, process.prioridade_estatica);
        simulated = false;
    }
</script>

<div class="proc-wrapper">
    <CommonFileInput handleFiles={handleProcFile}>
        {#snippet label()}
            <h2>Processos</h2>
        {/snippet}
    
        <!-- HACKY but i dont have the time to think about that -->
        <form onsubmit={(e) => e.preventDefault()}>
            <button onclick={() => {addProcesso({inicio: 0, duracao: 1, prioridade_estatica: 0}); simulated = false}}>Adicionar processo</button>
            <button onclick={() => {clearProcs(); simulated = false}}>Limpar processos</button>
        </form>
        <div class="procs">
            {#each getProcessos() as process (process.id)}
                <div class="process">
                    <header>{process.id}</header>
                    <div class="input">
                        <label for={`inicio${process.id}`}>Início:</label>
                        <input id={`inicio${process.id}`} type="number" 
                        bind:value={() => process.inicio, (newVal) => updateProc({...process, inicio: newVal})}>
                    </div>
                    <div class="input">
                        <label for={`duracaoP${process.id}`}>Duração:</label>
                        <input id={`duracaoP${process.id}`} type="number" 
                        bind:value={() => process.duracao, (newVal) => updateProc({...process, duracao: newVal})}>
                    </div>
                    <div class="input">
                        <label for={`prioridadeP${process.id}`}>Prioridade:</label>
                        <input id={`prioridadeP${process.id}`} type="number"
                        bind:value={() => process.prioridade_estatica, (newVal) => updateProc({...process, prioridade_estatica: newVal})}>
                    </div>
                    <form onsubmit={(e) => e.preventDefault()}>
                        <button aria-label="Remover processo" onclick={() => {removeProcesso(process.id); simulated = false}}><Times/></button>
                    </form>
                </div>
            {/each}
        </div>
    </CommonFileInput>
</div>

<style>
    button{
        margin-top: 0.5rem;
    }

    .proc-wrapper{
        width: 100%;
        height: 100%;
    }
    .proc-wrapper h2{
        margin: 0.5rem 0;
    }

    .procs{
        height: 12rem;
    }

    .process{
        margin-top: 0.5rem;

        display: flex;
        flex-direction: row;
        flex-wrap: wrap;
        align-items: center;
        justify-content: space-around;
        gap: 0.5rem;

        border: 1px solid black;
        background-color: var(--color-secondary);

        padding: 1rem;

        font-weight: bold;

        header{
            padding: 0.1rem;
            border: 3px dashed var(--color-accent);
            background-color: white;
        }

        button{
            margin: 0;
            display: flex;
            align-items: center;
            justify-content: center;
        }
    }
</style>