<script lang="ts">
    import CommonDiv from "../../../components/CommonDiv.svelte";
    import DragAndDrop from "../../../components/form/DragAndDrop.svelte";
    import { getTrace } from "../../util/traces";
    import type { PairIB, Saida } from "../cpp/api/build/Pages_wasm";
    import { ALGO_MAP, pager, type ALGORITHM_STR, type StateVector } from "../cpp/api/cppApi.svelte";


    interface Props{
        trace: StateVector;
        saida: Saida | null;
        verbose: boolean;
    }

    let { trace, saida = $bindable(), verbose = $bindable() }: Props = $props();

    let algorithm: ALGORITHM_STR = $state("FIFO");
    let num_frames = $state(3);

    function loadTrace(txt: string){
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
    
    async function handleFiles(files: FileList | null){
        if(!files || !files[0]) return;
        const txt = await files[0].text();

        loadTrace(txt);
    }

    function onSubmit(e: SubmitEvent){
        e.preventDefault();
        
        const alg = ALGO_MAP.get(algorithm);
        if(!alg) return;
        saida = pager(alg, num_frames, trace.vec, verbose);
    }
</script>

<div class="main">
    <CommonDiv>
        <h2>Adicionar trace</h2>
        <DragAndDrop {handleFiles}/>
        <button onclick={() => loadTrace(getTrace("silberschatz2001"))}>Silberschatz2001</button>
        <button onclick={() => loadTrace(getTrace("belady"))}>Belady</button>
        <button onclick={() => loadTrace(getTrace("escritas"))}>Escritas</button>
        <div class="table-div">
            {#if trace.length > 0}
            <table>
                <thead>
                    <tr>
                        <td></td>
                        {#each Array.from(trace) as trace_line, i(i)}
                        <th>{trace_line?.first}</th>
                        {/each}
                    </tr>
                </thead>
                <tbody>
                    <tr>
                        <th>Acesso</th>
                        {#each Array.from(trace) as trace_line, i(i)}
                        {#if trace_line}
                        <td class={trace_line.second?"table-accent":"null"}>{trace_line?.second?"W":"R"}</td>
                        {/if}
                        {/each}
                    </tr>
                </tbody>
            </table>
            {/if}
        </div>
    </CommonDiv>
    <CommonDiv>
        <form onsubmit={onSubmit}>
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
</div>

<style>
    .main{
        display: flex;
        flex-direction: column;
        gap: 5px;
    }

    .table-div{
        display: flex;
        justify-content: center;

        overflow: auto;
    }
</style>