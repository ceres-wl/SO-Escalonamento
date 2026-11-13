<script lang="ts">
    let algorithm = "FIFO";
    let verbose = false;
</script>

<main>
    <form>
        <label>Número de frames
            <input type="number">
        </label>
        <label>Algoritmo
            <select bind:value={algorithm}>
                <option value="fifo">FIFO</option>
                <option value="lru">LRU</option>
                <option value="opt">Ótimo</option>
                <option value="clock">Clock</option>
                <option value="nru">NRU</option>
                <option value="lfu">LFU</option>
                <option value="mfu">MFU</option>
            </select>
        </label>
        <!-- TODO dragndrop de arquivo -->
        <label>Verbose
            <input type="checkbox" bind:checked={verbose}>
        </label>
        <button>Simular</button>
    </form>
</main>