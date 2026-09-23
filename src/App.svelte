<script lang="ts">
    import ConfigInput from "./lib/components/FileInput/ConfigInput.svelte";
    import ProcInput from "./lib/components/FileInput/ProcInput.svelte";
    import { add, helloWorld } from "./lib/cpp/api/cppApi";

    helloWorld();
    console.log(add(5.5526623, 4.55325));
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