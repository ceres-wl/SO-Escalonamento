<script lang="ts">
    import Escalonamento from "./lib/pages/escalonamento/Escalonamento.svelte";
    import Paginacao from "./lib/pages/paginacao/Paginacao.svelte";
    import Memoria from "./lib/pages/memoria/Memoria.svelte";

    let selected: "Escalonamento" | "Paginacao" | "Memoria" = "Memoria";
</script>

<!-- TODO Ver os elementos certos pra isso dps -->
<nav>
    <!-- TODO estilizar isso aqui -->
    <button onclick={() => selected = "Escalonamento"}>Escalonamento</button>
    <button onclick={() => selected = "Paginacao"}>Paginação</button>
    <button onclick={() => selected = "Memoria"}>Memória</button>
</nav>
<main>
    <div class={selected!="Escalonamento"?"hide":null}>
        <Escalonamento/>
    </div>
    <div class={selected!="Paginacao"?"hide":null}>
        <Paginacao/>
    </div>
    <div class={selected!="Memoria"?"hide":null}>
        <Memoria/>
    </div>
</main>

<style>
    main{
        max-width: 120ch;
        margin: 0 auto;
    }

    .hide{
        display: none;
    }

    :global(html, body){
        margin: 0;
    }

    :global(body){
        background-color: rgb(20, 92, 68);
    }

    :global(*){
        box-sizing: border-box;
    }

    :global(:root){
        /* TODO decidir cores */
        --color-primary: whitesmoke;
        --color-secondary: rgb(235, 235, 235);
        --color-accent: rgb(255, 106, 136);
        --color-bg: white;

        --color-input-bg: rgb(255, 106, 136);
        --color-input-bg-hover: rgb(155, 65, 83);
    }

    :global(button, input, select){
        background-color: var(--color-input-bg);
        border: 1px solid black;
        color: white;

        text-align: center;
    }

    :global(button){
        background-color: var(--color-input-bg);  
        cursor: pointer;

        &:hover{
            background-color: var(--color-input-bg-hover);
        }
    }

    :global(input[type=number]){
        font-size: 1rem;
        max-width: 10ch;
    }

    :global(h1, h2, h3){
        font-family: 'Franklin Gothic Medium', 'Arial Narrow', Arial, sans-serif;
        font-variant: small-caps;
    }

    :global(.flex-center){
        display: flex;
        align-items: center;
        justify-content: center;
    }

    :global(.pixelated){
        image-rendering: pixelated;
    }
</style>