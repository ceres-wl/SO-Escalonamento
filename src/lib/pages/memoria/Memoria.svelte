<script lang="ts">
    import { memoria } from "./context/memoria.svelte";
    import MemoryChart from "./components/charts/MemoryChart.svelte";
    import CommonDiv from "../../components/CommonDiv.svelte";
    import type { Command } from "./types";
    import CmdHistory from "./components/CmdHistory.svelte";
    import { runCommand } from "./utils/commands";
    import CmdFileInput from "./components/CmdFileInput.svelte";

    let cliInput = $state("");
    let output = $state("");

    let cmdHistory: Array<Command> = $state([]);
    let curCmd = $state(-1);

    function handleSubmit(e?: SubmitEvent){
        e?.preventDefault();

        // TODO arrow up e down pra selecionar histórico de comandos

        const tokens = cliInput.trim().toLowerCase().split(/[ ]{1,}/);
        const action = tokens.shift() as string;
        
        cliInput = "";

        if(action == "#") return;

        const cmd: Command = {
            args: tokens,
            cmd: action,
            output: ""
        }

        try{
            runCommand(cmd);
        }catch(e){
            if(!(e instanceof Error)) return;
            cmd.output = "Erro: "+e.message;
        }finally{
            output = cmd.output;
            cmdHistory.push(cmd);
            curCmd = cmdHistory.length-1;
        }
    }
</script>

<main>
    <!-- TODO pensar o layout q eu qro pra isso aq -->
    <!-- TODO div com explicações de como usa? -->
    <div class="flex-row-responsive">
        <div class="mem-file-input">
            <CmdFileInput {handleSubmit} bind:cliInput/>
        </div>
        <div class="terminal">
            <CommonDiv>
                <form onsubmit={handleSubmit}>
                    <h2>
                        <label for="cli">Terminal</label>
                    </h2>
        
                    <input id="cli" bind:value={cliInput} type="text">
                    <button>Enviar</button>
                </form>
                <!-- the weird regex here is because aparently either svelte or the way html works itself doesnt respect \n in strings -->
                <p class="output">{@html output.replace(/(\r\n|\r|\n)/ig, "<br>")}</p>
            </CommonDiv>
        </div>
    </div>
    <CmdHistory bind:cmdHistory bind:curCmd {runCommand} setOutput={(o) => output = o} clearMemory={() => memoria.id_atual = Infinity}/>
    {#if memoria && memoria.id_atual != Infinity}
    <!-- TODO adicionar informações gerais da memória -->
     <div class="chart">
        <h2>Memória</h2>
        <MemoryChart/>
     </div>
    {/if}
</main>

<style>
    main{
        display: flex;
        flex-direction: column;
        gap: 5px;
    }

    .terminal{
        width: 100%;
        height: 18rem;
        overflow: auto;
    }

    .chart{
        padding: 0.5rem;

        border: 1px solid black;
        background-color: var(--color-secondary);

        & > h2{
            text-align: center;
            font-size: 3rem;
            margin: 0;
        }
    }

    :global(.output){
        word-break: break-all;
        font-family: 'Courier New', Courier, monospace;
    }
</style>