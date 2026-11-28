<script lang="ts">
    import FrameInput from "./components/FrameInput.svelte";
    import FrameOutput from "./components/FrameOutput.svelte";
    import type { Saida } from "./cpp/api/build/Pages_wasm";
    import { StateVector } from "./cpp/api/cppApi.svelte";

    let trace = new StateVector();

    let saida: Saida | null = $state(null);
    let verbose = $state(false);
</script>

<main>
    <FrameInput bind:saida {trace} bind:verbose/>
    {#if saida}
        <FrameOutput {saida} {verbose}/>
    {/if}
</main>

<style>
    main{
        display: flex;
        flex-direction: column;
        gap: 5px;
    }
</style>