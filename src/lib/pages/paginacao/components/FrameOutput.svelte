<script lang="ts">
    import CommonDiv from "../../../components/CommonDiv.svelte";
    import { saidaToString } from "../../util/saidaToString";
    import type { Saida } from "../cpp/api/build/Pages_wasm";
    import { INVERSE_ALGO_MAP } from "../cpp/api/cppApi.svelte";
    import FrameSteps from "./FrameSteps.svelte";

    interface Props{
        saida: Saida;
        verbose: boolean;
    }

    const { saida, verbose }: Props = $props();

    function copyString(){
        return navigator.clipboard.writeText(saidaToString(saida, verbose));
    }
</script>

<div>
    <!-- TODO fazer isso como texto copiável, or fazer o executável de terminal -->
    <!-- TODO fazer a saida verbose -->
    <!-- TODO fazer a visualização dos frames -->
    <CommonDiv>
        <FrameSteps verb_info={saida.verb_info}/>
    </CommonDiv>
    <CommonDiv>
        <h2>Métricas</h2>
        <button onclick={copyString}>Copiar como string</button>
        <div class="stats">
            <div>
                <header>Algoritmo</header>
                <p>{INVERSE_ALGO_MAP.get(saida.algo.value)}</p>
            </div>
            <div>
                <header>Frames</header>
                <p>{saida.frames}</p>
            </div>
            <div>
                <header>Referências</header>
                <p>{saida.referencias}</p>
            </div>
            <div>
                <header>Faltas de página</header>
                <p>{saida.page_fault}</p>
            </div>
            <div>
                <header>Taxa de faltas</header>
                <p>{saida.fault_ratio.toPrecision(2)}%</p>
            </div>
            <div>
                <header>Evicções</header>
                <p>{saida.evictions}</p>
            </div>
            <div>
                <header>Escritas em disco</header>
                <p>{saida.disk_writes}</p>
            </div>
        </div>
        <div class="final-set">
            <h3>Conjunto residente final:</h3>
            <div class="flex-center">
                <table>
                    <thead>
                        <tr>
                        <th>Frame IDs</th>
                        {#each Array.from(saida.frame_ids) as frame_id, i(i)}
                            <th>{frame_id}</th>
                        {/each}
                        </tr>
                    </thead>
                    <tbody>
                        <tr>
                            <th>Page IDs</th>
                            {#each Array.from(saida.page_ids) as page_id, i(i)}
                                <td>{page_id==-1?".":page_id}</td>
                            {/each}
                        </tr>
                    </tbody>
                </table>
            </div>
        </div>
    </CommonDiv>
    {#if verbose}
        <CommonDiv>
            <h2>Verbose</h2>
            <div class="flex-center">
                <table class="striped-table">
                    <thead>
                        <tr>
                            <th>Passo</th>
                            <th>Referência</th>
                            <th>Frames</th>
                            <th>Acerto</th>
                            <th>Removido</th>
                        </tr>
                    </thead>
                    <tbody>
                        {#each Array.from(saida.verb_info) as info, i(i)}
                        <tr>
                            <td>{info.passo}</td>
                            <td>{info.pag_ref}</td>
                            <td>[ {Array.from(info.cur_frames).map(e => e==-1?".":e.toString()).join(" ")} ]</td>
                            <td class={info.hit?null:"table-accent"}>{info.hit?"Acerto":"Falta"}</td>
                            <td>{info.removed==-1?"":info.removed}</td>
                        </tr>
                        {/each}
                    </tbody>
                </table>
            </div>
        </CommonDiv>
    {/if}
</div>

<style>
    .stats{
        display: flex;
        flex-direction: row;
        justify-content: center;
        gap: 0.5rem;

        margin: 0.5rem 0;

        flex-wrap: wrap;

        & > div{
            width: 30%;
            border: 1px solid black;
            background-color: var(--color-secondary);
        }
    }

    h2{
        font-size: 3rem;
        margin: 0;
    }
    h3{
        font-size: 2rem;
        margin: 0;
    }
</style>