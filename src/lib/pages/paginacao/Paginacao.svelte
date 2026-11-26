<script lang="ts">
    import { pager, type ALGORITHM } from "./cpp/api/cppApi";

    let algorithm: ALGORITHM = $state("FIFO");
    let num_frames = $state(3);
    let verbose = $state(false);

    function onSubmit(e: SubmitEvent){
        e.preventDefault();

        const saida: Saida = pager(algorithm, );
    }
</script>

<main>
    <form onsubmit={onSubmit}>
        <label>Número de frames
            <input type="number" bind:value={num_frames}>
        </label>
        <label>Algoritmo
            <select bind:value={algorithm}>
                <option value="FIFO">FIFO</option>
                <option value="LRU">LRU</option>
                <option value="OTIMO">Ótimo</option>
                <option value="CLOCK">Clock</option>
                <option value="NRU">NRU</option>
                <option value="LFU">LFU</option>
                <option value="MFU">MFU</option>
            </select>
        </label>
        <!-- TODO dragndrop de arquivo -->
        <label>Verbose
            <input type="checkbox" bind:checked={verbose}>
        </label>
        <button>Simular</button>
    </form>
</main>