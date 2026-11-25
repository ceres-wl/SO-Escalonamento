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

    <div class="cmd-history">
        <ol>
        <li><p class={curCmd==-1?"current-command":null}>Sem comandos...</p></li>
        {#each cmdHistory as cmd, i(i)}
            <li class={curCmd==i?"current-command":null}>
                <details>
                    <summary>{cmd.cmd} {cmd.args.join(" ")}</summary>
                    <p class="output">{@html cmd.output.replace(/(\r\n|\r|\n)/ig, "<br>")}</p>
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
    

    .current-command{
        background-color: green;
        color: white;
    }
</style>