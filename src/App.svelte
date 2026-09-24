<script lang="ts">
    import ConfigInput from "./lib/components/FileInput/ConfigInput.svelte";
    import ProcInput from "./lib/components/FileInput/ProcInput.svelte";
    import { add_proc, get_procs } from "./lib/cpp/api/cppApi";

    let procs = get_procs();
    if(procs){
        console.log(Array.from(procs));
        procs.push_back({inicio: 10, duracao: 15, prioridade_estatica: 20});
        add_proc({inicio: 500, duracao: 1500, prioridade_estatica: 2000})
        console.log(Array.from(procs));
        console.log(procs.size());
    }
</script>

<!--
    TODO icones? yes or no
    TODO background image? ou deixa a cor msm
    TODO deixar tudo redondo provavelmente, ou não seila
-->

<main>
    <div class="inputs">
        <ConfigInput/>
        <ProcInput/>
    </div>
</main>

<style>
    main{
        width: 120ch;
        margin: 0 auto;

        display: flex;
        flex-direction: column;
        gap: 5px;

        padding: 5px;
    }

    .inputs{
        display: flex;
        flex-direction: row;
        gap: 5px;
    }

    :global(html, body){
        margin: 0;
    }

    :global(body){
        background-color: aquamarine;
    }

    :global(*){
        box-sizing: border-box;
    }

    :global(:root){
        /* TODO decidir cores */
        --color-primary: whitesmoke;
        --color-secondary: lightgray;
        --color-accent: rgb(255, 106, 136);
    }
</style>