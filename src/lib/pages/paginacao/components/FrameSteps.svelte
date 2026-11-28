<script lang="ts">
    import type { VectorVerboseInfo, VerboseInfo } from '../cpp/api/build/Pages_wasm';

    interface Props {
        verb_info: VectorVerboseInfo;
    }

    const { verb_info }: Props = $props();

    let curStep = $state(0);
    let curInfo: VerboseInfo = $derived(verb_info.get(curStep) as VerboseInfo);

    let auto: number | undefined = $state();
    let autoChecked = $derived(false);

    function forward(){
        if(curStep == verb_info.size()-1) return;
        curStep++;
    }
    function back(){
        if(curStep == 0) return;
        curStep--;
    }

    function handleAutoChange(){
        clearInterval(auto);
        if(autoChecked)
            auto = setInterval(forward, 1000);
    }

    function autoUncheck(){
        clearInterval(auto);
        autoChecked = false;
    }

</script>

<div class="main">
    <h2>Visualização passo a passo</h2>
    <div class="controls">
        <label>Automático
            <input onchange={handleAutoChange} type="checkbox" bind:checked={autoChecked}>
        </label>
        <button onclick={() => {forward(); autoUncheck();}}>Avançar</button>
        <button onclick={() => {back(); autoUncheck();}}>Voltar</button>
        <button onclick={() => {curStep = 0; autoUncheck();}}>Resetar</button>
        <button onclick={() => {curStep = verb_info.size()-1; autoUncheck();}}>Completar</button>
    </div>
    <hr>
    <div>
        <p>Passo {curInfo.passo}</p>
        <p>Página: {curInfo.pag_ref}</p>
        <p>Removido: {curInfo.removed==-1?".":curInfo.removed}; No frame {Array.from(curInfo.cur_frames).findIndex((e) => e==curInfo.pag_ref)}</p>
        <div class="frames flex-center">
            {#each Array.from(curInfo.cur_frames) as frame, i (i)}
                <div class={["frame", curInfo.pag_ref==frame?(curInfo.hit?"acerto":"erro"):null]}>{frame==-1?".":frame}</div>
            {/each}
        </div>
    </div>
</div>

<style>
    h2{
        font-size: 3rem;
        margin: 0;
    }

    .frames{
        display: flex;
        padding: 0.5rem;
    }

    .frame{
            border: 1px solid black;
            background-color: var(--color-secondary);

            padding: 0.25rem;
            width: 4ch;

    }

    .acerto{
        background-color: green;
    }
    .erro{
        background-color: crimson;
    }
</style>