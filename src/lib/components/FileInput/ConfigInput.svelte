<script lang="ts">
    import { config, setConfig } from "../../context/config.svelte.js";
    import CommonFileInput from "./CommonFileInput.svelte";

    interface Props{
        simulated: boolean;
    }

    let { simulated = $bindable() }: Props = $props();

    async function handleConfigFile(files: FileList){
        if(!files || !files[0]) return;
        const txt = await files[0].text();

        const [quantum, aging] = txt.split("\n", 2).map((str) => {
            const num = Number(str.split(":")[1] ?? str);
            if(isNaN(num)) throw new Error("Valor não é um número")
            return num;
        })

        setConfig(quantum, aging);
    }
</script>

<div class="config-wrapper">
    <CommonFileInput handleFiles={handleConfigFile}>
        {#snippet label()}
            <h2>Configuração</h2>
        {/snippet}

        <div class="display">
            <label> Quantum
                <input bind:value={() => config.quantum, (val) => setConfig(config.aging, val)} type="number" name="quantum">
            </label>
            <label> Aging
                <input bind:value={() => config.aging, (val) => setConfig(val, config.aging)} type="number" name="aging">
            </label>
        </div>
    </CommonFileInput>
</div>

<style>
    .config-wrapper h2{
        margin: 0.5rem 0;
    }

    .display{
        margin-top: 0.5rem;

        display: flex;
        flex-direction: column;
        gap: 0.5rem;

        border: 1px solid black;
        background-color: var(--color-secondary);

        padding: 1rem 0;
    }
</style>