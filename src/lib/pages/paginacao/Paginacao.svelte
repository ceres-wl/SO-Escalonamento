<script lang="ts">
    import CommonDiv from "../../components/CommonDiv.svelte";
    import DragAndDrop from "../../components/form/DragAndDrop.svelte";
    import FrameInput from "./components/FrameInput.svelte";
    import FrameOutput from "./components/FrameOutput.svelte";
    import FrameSteps from "./components/FrameSteps.svelte";
    import type { PairIB, Saida } from "./cpp/api/build/Pages_wasm";
    import { ALGO_MAP, INVERSE_ALGO_MAP, pager, StateVector, type ALGORITHM_STR } from "./cpp/api/cppApi.svelte";

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