<script lang="ts">
    import { config, setConfig } from "../../config.svelte";
    import CommonFileInput from "./CommonFileInput.svelte";

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

<!-- HACK to force the config input to not take 100% width, making the proc input take the space instead, 
    not fully a hack just not the prettiest code ever 
-->
<div class="config-wrapper">
    <CommonFileInput label="Configuração" handleFiles={handleConfigFile}>
        <div class="display">
            <label> Quantum
                <input bind:value={config.quantum} type="number" name="quantum">
            </label>
            <label> Aging
                <input bind:value={config.aging} type="number" name="aging">
            </label>
        </div>
    </CommonFileInput>
</div>

<style>
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