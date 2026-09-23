<script lang="ts">
    import { addProcesso, removerProcesso, listarProcessos } from "../../listaProcesso.svelte";
    import CommonFileInput from "./CommonFileInput.svelte";

    async function handleProcFile(files: FileList){
        if(!files || !files[0]) return;
        const txt = await files[0].text();

        for(const line of txt.split("\n")){
            if(line.trim() == "") continue;

            const [criacao, duracao, prioridade_estatica] = line.split(" ").map((str) => Number(str));
            if([criacao, duracao, prioridade_estatica].some(isNaN)) throw new Error("Valor não é um número");

            addProcesso({
                criacao,
                duracao,
                prioridade_estatica
            });
        }
    }
</script>

<!-- TODO dar um estilozinho pro header de cada processo e pro botão de remover -->

<CommonFileInput label="Processos" handleFiles={handleProcFile}>
    <button onclick={() => addProcesso({criacao: 0, duracao: 1, prioridade_estatica: 0})}>Adicionar processo</button>
    {#each listarProcessos() as process (process.id)}
        <div class="process">
            <header>P{process.id}</header>
            <div class="input">
                <label for={`criacaoP${process.id}`}>Criação</label>
                <input bind:value={process.criacao} id={`criacaoP${process.id}`} type="number">
            </div>
            <div class="input">
                <label for={`duracaoP${process.id}`}>Duração</label>
                <input bind:value={process.duracao} id={`duracaoP${process.id}`} type="number">
            </div>
            <div class="input">
                <label for={`prioridadeP${process.id}`}>Prioridade</label>
                <input bind:value={process.prioridade_estatica} id={`prioridadeP${process.id}`} type="number">
            </div>
            <button onclick={() => removerProcesso(process.id)}>Remover</button>
        </div>
    {/each}
</CommonFileInput>

<style>
    button{
        margin-top: 0.5rem;
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