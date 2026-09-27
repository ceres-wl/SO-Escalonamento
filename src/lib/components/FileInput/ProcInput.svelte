<script lang="ts">
    import { addProcesso, removerProcesso, getProcessos } from "../../listaProcesso.svelte";
    import CommonFileInput from "./CommonFileInput.svelte";

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
</script>

<!-- TODO dar um estilozinho pro header de cada processo e pro botão de remover -->
<div class="proc-wrapper">
    <CommonFileInput handleFiles={handleProcFile}>
        {#snippet label()}
            <h2>Processos</h2>
        {/snippet}
    
        <button onclick={() => {addProcesso({inicio: 0, duracao: 1, prioridade_estatica: 0}); simulated = false}}>Adicionar processo</button>
        <div class="procs">
            {#each getProcessos() as process (process.id)}
                <div class="process">
                    <header>{process.id}</header>
                    <div class="input">
                        <label for={`inicio${process.id}`}>Início</label>
                        <input bind:value={process.inicio} id={`inicio${process.id}`} type="number">
                    </div>
                    <div class="input">
                        <label for={`duracaoP${process.id}`}>Duração</label>
                        <input bind:value={process.duracao} id={`duracaoP${process.id}`} type="number">
                    </div>
                    <div class="input">
                        <label for={`prioridadeP${process.id}`}>Prioridade</label>
                        <input bind:value={process.prioridade_estatica} id={`prioridadeP${process.id}`} type="number">
                    </div>
                    <button onclick={() => {removerProcesso(process.id); simulated = false}}>Remover</button>
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
        align-items: center;
        gap: 0.5rem;

        border: 1px solid black;
        background-color: var(--color-secondary);

        padding: 1rem;
    }
</style>