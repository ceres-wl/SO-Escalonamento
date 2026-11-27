<script lang="ts">
    import CommonDiv from "../../components/CommonDiv.svelte";
    import DragAndDrop from "../../components/form/DragAndDrop.svelte";
    import type { PairIB, Saida } from "./cpp/api/build/Pages_wasm";
    import { ALGO_MAP, INVERSE_ALGO_MAP, pager, StateVector, type ALGORITHM_STR } from "./cpp/api/cppApi.svelte";

    let algorithm: ALGORITHM_STR = $state("FIFO");
    let num_frames = $state(3);
    let verbose = $state(false);

    let trace = new StateVector();

    let saida: Saida | null = $state(null);

    async function handleFiles(files: FileList | null){
        if(!files || !files[0]) return;
        const txt = await files[0].text();

        const trace_input: Array<PairIB> = txt.split("\n")
        .map((line) =>{
            const tokens = line.split(/[ ]{1,}/);
            if(!tokens[0] || tokens[0] == "#") return null;

            trace.clear();

            const first = Number(tokens[0]);
            if(isNaN(first)) throw new Error(`Frame "${tokens[0]}" do trace não é um número`)

            // Operador ternário aninhado jumpscare
            const second = tokens[1]?(tokens[1].toLowerCase().trim()=="w"?true:false):false;

            return {
                first,
                second
            }
        })
        .filter((e) => e!=null);

        for(let input of trace_input){
            trace.push_back(input);
        }
    }

    function onSubmit(e: SubmitEvent){
        e.preventDefault();
        
        const alg = ALGO_MAP.get(algorithm);
        if(!alg) return;
        saida = pager(alg, num_frames, trace.vec, verbose);
    }
</script>

<main>
    <CommonDiv>
        <form onsubmit={onSubmit}>
            <DragAndDrop {handleFiles}/>
            <div>
                {#each Array.from(trace) as trace_line, i(i)}
                    {#if trace_line}
                    <p>{trace_line.first} {trace_line.second}</p>
                    {/if}
                {/each}
            </div>
            <!-- TODO tabela com o trace carregado -->
            <label>Número de frames
                <input id="frame-num" type="number" bind:value={num_frames}>
            </label>
            <label>Algoritmo
                <select id="select-algorithm-pages" bind:value={algorithm}>
                    <option value="FIFO">FIFO</option>
                    <option value="LRU">LRU</option>
                    <option value="OTIMO">Ótimo</option>
                    <option value="CLOCK">Clock</option>
                    <option value="NRU">NRU</option>
                    <option value="LFU">LFU</option>
                    <option value="MFU">MFU</option>
                </select>
            </label>
            <label>Verbose
                <input type="checkbox" bind:checked={verbose}>
            </label>
            <button>Simular</button>
        </form>
    </CommonDiv>
    <CommonDiv>
        <!-- TODO fazer isso como texto copiável, or fazer o executável de terminal -->
        <!-- TODO fazer a saida verbose -->
        <!-- TODO fazer a visualização dos frames -->
        {#if saida}
            <p>Algoritmo: {INVERSE_ALGO_MAP.get(saida.algo.value)}</p>
            <p>Frames: {saida.frames}</p>
            <p>Referências: {saida.referencias}</p>
            <p>Faltas de página: {saida.page_fault}</p>
            <p>Taxa de faltas: {saida.fault_ratio.toPrecision(2)}%</p>
            <p>Evicções: {saida.evictions}</p>
            <p>Escritas em disco:{saida.disk_writes}</p>
            <p>Conjunto residente final:</p>
            <p>frame_ids:
            {#each Array.from(saida.frame_ids) as frame_id(frame_id)}
                {frame_id}, 
            {/each}
            </p>
            <p>page_ids:
            {#each Array.from(saida.page_ids) as frame_id(frame_id)}
                {frame_id}, 
            {/each}
            </p>
        {/if}
    </CommonDiv>
</main>