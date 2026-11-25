<script lang="ts">
    import CommonDiv from "../../../components/CommonDiv.svelte";
    import type { Memoria } from "../cpp/api/build/Memory_wasm";
    import type { Command } from "../types";

    interface Props{
        cmdHistory: Array<Command>;
        memoria: Memoria;
        curCmd: number;
        clearMemory: () => void;
        runCommand: (cmd: Command) => void;
        setOutput: (output: string) => void;
    }
    
    let {cmdHistory = $bindable(), curCmd = $bindable(), memoria = $bindable(), runCommand, setOutput, clearMemory}: Props = $props();

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

    <div class="cmd-history">
        <ol>
        <li><p class={curCmd==-1?"current-command":null}>Sem comandos...</p></li>
        {#each cmdHistory as cmd, i(i)}
        <!-- TODO botão para saltar pro comando atual -->
            <li class={curCmd==i?"current-command":null}>
                <details>
                    <summary>{cmd.cmd} {cmd.args.join(" ")}</summary>
                    <p>{cmd.output}</p>
                </details>
            </li>
        {/each}
        </ol>
    </div>

    <!-- TODO pensar se eu quero fazer a tal da reprodução automática -->
    <button onclick={() => setCurCommandIndex(curCmd+1)}>Avançar</button>
    <button onclick={() => setCurCommandIndex(curCmd-1)}>Voltar</button>
    <button onclick={() => setCurCommandIndex(-1)}>Reiniciar</button>
    <button onclick={() => {
        cmdHistory = [];
        clearMemory();
    }}>Deletar todos</button>
</CommonDiv>

<style>
    

    .current-command{
        background-color: green;
        color: white;
    }
</style>