<script lang="ts">
    import type { Opcao } from "./cpp/api/build/Memory_wasm";
    import { alloc, create_memoria, defrag, freeaddr, freeid, opcao, show, stats, type AllocAlgs } from "./cpp/api/cppApi";
    import { memoria, setMemoria } from "./context/memoria.svelte";
    import MemoryChart from "./components/charts/MemoryChart.svelte";
    import CommonFileInput from "../../components/FileInput/CommonFileInput.svelte";
    import CommonDiv from "../../components/CommonDiv.svelte";
    import type { Command } from "./types";
    import CmdHistory from "./components/CmdHistory.svelte";

    let cliInput = $state("");
    let output = $state("");

    // TODO mudar a lógica do histórico de comanods pra um componente separado
    let cmdHistory: Array<Command> = $state([]);
    let curCmd = $state(-1);
    
    function runCommand(cmd: Command){
        function parseNumStr(str: string){
            const arg = Math.floor(Number(str));
            if(isNaN(arg)) throw new Error(`Argumento "${str}" inválido`);
            return arg;
        }

        // top switch cases mais feios já escritos
        switch (cmd.cmd) {
            case "init":
                setMemoria(create_memoria(parseNumStr(cmd.args[0])));

                cmd.output = "";
                break;
            case "alloc":
                if(memoria.id_atual == Infinity) throw new Error("Memória não inicializada!");
                const alg = cmd.args[1];
                // Não se assuste! É feio mas funciona... contanto que ninguem mexa em mais nada, nunca mais...
                if(!["first", "best", "worst", "next"].some((e) => e == alg)) throw new Error("Algoritmo inválido!");

                alloc(memoria, parseNumStr(cmd.args[0]), alg as AllocAlgs);

                cmd.output = "";
                break;
            case "freeid":
                if(memoria.id_atual == Infinity) throw new Error("Memória não inicializada!");

                freeid(memoria, parseNumStr(cmd.args[0]));

                cmd.output = "";
                break;
            case "freeaddr":
                if(memoria.id_atual == Infinity) throw new Error("Memória não inicializada!");

                freeaddr(memoria, parseNumStr(cmd.args[0]));

                cmd.output = "";
                break;
            case "show":
                if(memoria.id_atual == Infinity) throw new Error("Memória não inicializada!");

                cmd.output = show(memoria);

                break;
            case "stats":
                if(memoria.id_atual == Infinity) throw new Error("Memória não inicializada!");

                cmd.output = stats(memoria);

                break;
            case "defrag":
                if(memoria.id_atual == Infinity) throw new Error("Memória não inicializada!");
                if(!opcao.has(cmd.args[0])) throw new Error("Opção inválida!");

                defrag(memoria, opcao.get(cmd.args[0]) as unknown as Opcao);

                cmd.output = "";
                break;
            default:
                throw new Error("Comando inválido!");
        }
    }

    function handleFiles(f: FileList | null){

    }

    function handleSubmit(e: SubmitEvent){
        e.preventDefault();

        // TODO arrow up e down pra selecionar histórico de comandos

        const tokens = cliInput.toLowerCase().split(/[ ]{1,}/);
        const action = tokens.shift() as string;

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
            cliInput = "";
            output = cmd.output;
            cmdHistory.push(cmd);
            curCmd = cmdHistory.length-1;
        }
    }
</script>

<main>
    <!-- TODO pensar o layout q eu qro pra isso aq -->
    <!-- TODO div com explicações de como usa? -->
    <CommonFileInput {handleFiles}>
        {#snippet label()}
            <h2>Arquivo com comandos</h2>
        {/snippet}
    </CommonFileInput>
    <CmdHistory bind:cmdHistory bind:curCmd {memoria} {runCommand} setOutput={(o) => output = o} clearMemory={() => memoria.id_atual = Infinity}/>
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
    {#if memoria && memoria.id_atual != Infinity}
    <!-- TODO adicionar informações gerais da memória -->
    <MemoryChart mem={memoria}/>
    {/if}
</main>

<style>
    .output{
        word-break: break-all;
        font-family: 'Courier New', Courier, monospace;
    }
</style>