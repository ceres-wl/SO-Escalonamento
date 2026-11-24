<script lang="ts">
    import type { Memoria, Opcao } from "./cpp/api/build/Memory_wasm";
    import { alloc, create_memoria, defrag, freeaddr, freeid, opcao, show, stats, type AllocAlgs } from "./cpp/api/cppApi";

    // Todos os comandos devem ser apis do cpp, 
    // Memória pode ser um vetor de struct criada no cpp tbm

    let cliInput = $state("");
    let output = $state("");

    let memoria: Memoria | null = $state(null);

    function handleSubmit(e: SubmitEvent){
        e.preventDefault();

        const tokens = cliInput.trim().toLowerCase().split(" ");
        const cmd = tokens[0];

        function parseNumStr(str: string){
            const arg = Math.floor(Number(str));
            if(isNaN(arg)) throw new Error(`Argumento "${str}" inválido`);
            return arg;
        }

        try{
            // top switch cases mais feios já escritos
            switch (cmd) {
                case "init":
                    memoria = create_memoria(parseNumStr(tokens[1]));
                    break;
                case "alloc":
                    if(memoria == null) throw new Error("Memória não inicializada!");
                    const alg = tokens[2];
                    // Não se assuste! É feio mas funciona... contanto que ninguem mexa em mais nada, nunca mais...
                    if(!["first", "best", "worst", "next"].some((e) => e == alg)) throw new Error("Algoritmo inválido!");
                    alloc(memoria, parseNumStr(tokens[1]), alg as AllocAlgs);
                    break;
                case "freeid":
                    if(memoria == null) throw new Error("Memória não inicializada!");
                    freeid(memoria, parseNumStr(tokens[1]));
                    break;
                case "freeaddr":
                    if(memoria == null) throw new Error("Memória não inicializada!");
                    freeaddr(memoria, parseNumStr(tokens[1]));
                    break;
                case "show":
                    if(memoria == null) throw new Error("Memória não inicializada!");
                    show(memoria);
                    break;
                case "stats":
                    if(memoria == null) throw new Error("Memória não inicializada!");
                    stats(memoria);
                    break;
                case "defrag":
                    if(memoria == null) throw new Error("Memória não inicializada!");
                    if(!opcao.has(tokens[2])) throw new Error("Opção inválida!");
                    defrag(memoria, opcao.get(tokens[2]) as unknown as Opcao);
                    break;
                default:
                    throw new Error("Comando inválido!");
            }
        }catch(e){
            if(!(e instanceof Error)) return;
            output = e.message;
        }finally{
            cliInput = "";
        }
    }
</script>

<main>
    <form onsubmit={handleSubmit}>
        <!-- TODO decidir se coloco um label -->
        <input bind:value={cliInput} type="text">
        <button>Enviar</button>
    </form>
    <div>
        <p>{output}</p>
    </div>
    <!-- Alguma forma de visualização aqui-->
    {#each memoria?.mem as bloco(bloco.id)}
        <div>
            <p>{bloco.id}</p>
            <p>{bloco.endereco}</p>
            <p>{bloco.livre}</p>
            <p>{bloco.tamanho}</p>
        </div>
    {/each}
</main>