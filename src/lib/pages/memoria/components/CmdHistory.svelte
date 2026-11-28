<script lang="ts">
    import CommonDiv from "../../../components/CommonDiv.svelte";
    import type { Memoria } from "../cpp/api/build/Memory_wasm";
    import type { Command } from "../types";

    interface Props{
        cmdHistory: Array<Command>;
        curCmd: number;
        clearMemory: () => void;
        runCommand: (cmd: Command) => void;
        setOutput: (output: string) => void;
    }
    
    let {cmdHistory = $bindable(), curCmd = $bindable(), runCommand, setOutput, clearMemory}: Props = $props();

    function setCurCommandIndex(index: number){
        if(index < -1 || index >= cmdHistory.length) return;
        curCmd = index;
        clearMemory();
        // Solução meio lenta, mas serve :)
        for(let i = 0; i <= curCmd; i++){
            try{
                runCommand(cmdHistory[i]);
            }catch(e){}
            finally{
                setOutput(cmdHistory[i].output);
            }
        }
    }
</script>

<CommonDiv>
    <h2>Histórico de comandos</h2>

    <div class="flex-center">
        <ol class="cmd-history">
        <li>
            <p class={["command", "init-command", curCmd==-1?"current-command":null]}>Sem comandos...</p>
        </li>
        {#each cmdHistory as cmd, i(i)}
            <li class={["command", curCmd==i?"current-command":null]}>
                <details>
                    <summary>{cmd.cmd} {cmd.args.join(" ")}</summary>
                    <p class="output">
                        {#if cmd.output== ""}
                            Sem output
                        {:else}
                        {@html cmd.output.replace(/(\r\n|\r|\n)/ig, "<br>")}
                        {/if}
                    </p>
                </details>
                <button onclick={() => setCurCommandIndex(i)}>Saltar aqui</button>
            </li>
        {/each}
        </ol>
    </div>

    <!-- TODO pensar se eu quero fazer a tal da reprodução automática -->
    <button onclick={() => setCurCommandIndex(curCmd-1)}>Voltar</button>
    <button onclick={() => setCurCommandIndex(curCmd+1)}>Avançar</button>
    <button onclick={() => setCurCommandIndex(-1)}>Reiniciar</button>
    <button onclick={() => {
        cmdHistory = [];
        curCmd = -1;
        setOutput("");
        clearMemory();
    }}>Deletar todos</button>
    <button onclick={() => {
        cmdHistory.pop();
        setCurCommandIndex(cmdHistory.length-1);
    } }>Deletar ultimo</button>
</CommonDiv>

<style>
    .command{
        background-color: var(--color-secondary);
        font-weight: bold;
        font-size: 1.3rem;

        button{
            margin-top: -5px;
            width: 100%;
        }
    }

    summary{
        padding: 0.5rem;

        cursor: pointer;
        &:hover{
            background-color: var(--color-input-bg-hover);
        }
    }

    .current-command{
        background-color: var(--color-accent);
        color: white;
    }

    .cmd-history{
        display: flex;
        flex-wrap: wrap;
        gap: 5px;
    }

    ol{
        list-style-type: none;
        margin-top: 0;
    }
</style>