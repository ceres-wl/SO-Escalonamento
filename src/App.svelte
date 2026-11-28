<script lang="ts">
    import Escalonamento from "./lib/pages/escalonamento/Escalonamento.svelte";
    import Paginacao from "./lib/pages/paginacao/Paginacao.svelte";
    import Memoria from "./lib/pages/memoria/Memoria.svelte";
    import Header from "./lib/components/Header.svelte";
    import { setDisableAnimation } from "./lib/context/disableAnimation";
    import External from '~icons/fa-solid/external-link-alt'

    let selected: "Escalonamento" | "Paginação" | "Memória" = $state("Paginação");

    let disableAnimation = $state(false);
    setDisableAnimation(() => disableAnimation);
</script>

<!-- TODO Ver os elementos certos pra isso dps -->
<nav>
    <!-- TODO estilizar isso aqui -->
    <button onclick={() => selected = "Escalonamento"}>Escalonamento</button>
    <button onclick={() => selected = "Memória"}>Memória</button>
    <button onclick={() => selected = "Paginação"}>Paginação</button>
</nav>
<main>
    <!-- TODO icone pra simulação de memória e paginação -->
    <Header page={selected} bind:disableAnimation/>
    <div class={selected!="Escalonamento"?"hide":null}>
        <Escalonamento/>
    </div>
    <div class={selected!="Memória"?"hide":null}>
        <Memoria/>
    </div>
    <div class={selected!="Paginação"?"hide":null}>
        <Paginacao/>
    </div>
    <footer>
        <p>
            Projeto criado para a cadeira de Sistemas Operacionais da UFC
        </p>
        <p><a target="_blank" href="https://github.com/ceres-wl/SO-Escalonamento">Link para o Repositório <External/></a></p>
    </footer>
</main>

<style>
    main{
        max-width: 120ch;
        margin: 0 auto;
    }

    .hide{
        display: none;
    }

    footer{
        display: flex;
        align-items: center;
        justify-content: space-between;

        background-color: var(--color-primary);

        font-weight: bold;

        a{
            text-decoration: none;

            &:hover{
                text-decoration: underline dotted;
            }
        }

        padding: 0.5rem;
        margin: 0.25rem 0;
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

    :global(.flex-row-responsive){
        display: flex;
        flex-direction: row;
        gap: 5px;

        @media screen and (max-width: 48em) {
            flex-direction: column;
        }
    }

    :global(table){
        table-layout: fixed;
        border-collapse: collapse;
        border: 1px solid black;

        margin: 0.5rem 0;
        font-size: 1.3rem;

        :global(thead td, th){
            border: 1px solid black;
            background-color: var(--color-secondary);
        }

        :global(th){
            padding: 0.25rem;
        }

        :global(td){
            border: 1px solid black;
            padding: 0.5rem;
        }

        :global(.table-accent){
            background-color: var(--color-accent);
        }
    }

    :global(.striped-table){
        :global(tr:nth-child(2n)){
            background-color: var(--color-secondary);
        }
    }
</style>