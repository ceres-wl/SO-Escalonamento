<script lang="ts">
    import type { Config } from "./lib/types";
    import { addProcesso, removerProcesso, listarProcessos } from "./lib/listaProcesso.svelte";

    let processesFile: FileList | null = $state(null);
    let configFile: FileList | null = $state(null);

    // TODO tacar isso aqui num arquivo separado
    let config: Config = $state({
        aging: 1,
        quantum: 1
    });

    async function handleProcessesFile(){
        if(!processesFile || !processesFile[0]) return;
        const txt = await processesFile[0].text();

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

    async function handleConfigFile(){
        if(!configFile || !configFile[0]) return;
        const txt = await configFile[0].text();

        const [quantum, aging] = txt.split("\n", 2).map((str) => {
            const num = Number(str.split(":")[1] ?? str);
            if(isNaN(num)) throw new Error("Valor não é um número")
            return num;
        })

        config.quantum = quantum;
        config.aging = aging;
    }
</script>

<!-- TODO separar os inputs de arquivo e processo em dois componentes separados -->

<div>
    <div>
        <label> Arquivo de processos
            <input onchange={handleProcessesFile} bind:files={processesFile} type="file" name="processos">
        </label>
        <button onclick={() => addProcesso({criacao: 0, duracao: 1, prioridade_estatica: 0})}>Adicionar processo</button>
        {#each listarProcessos() as process (process.id)}
            <div>
                <p>ID {process.id}</p>
                <label>
                    <input bind:value={process.criacao} type="number">
                </label>
                <label> 
                    <input bind:value={process.duracao} type="number">
                </label>
                <label> Prioridade
                    <input bind:value={process.prioridade_estatica} type="number">
                </label>
                <button onclick={() => removerProcesso(process.id)}>Remover</button>
            </div>
        {/each}
    </div>
    <div>
        <label> Arquivo de configuração
            <input onchange={handleConfigFile} bind:files={configFile} type="file" name="config">
        </label>
        <label> Quantum
            <input bind:value={config.quantum} type="number" name="quantum">
        </label>
        <label> Aging
            <input bind:value={config.aging} type="number" name="aging">
        </label>
    </div>
</div>
