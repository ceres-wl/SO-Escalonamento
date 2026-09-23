<script lang="ts">
    import DragAndDrop from "../form/DragAndDrop.svelte";

    let { handleFiles, label, children } = $props();
</script>

<!--
    TODO input de texto bonitinho
    TODO fonte
    TODO uma polida no tamanho e espaçamento das coisas
-->

<div class="main">
    <p>{label}</p>
    <DragAndDrop handleFiles={handleFiles} />
    {@render children()}
</div>

<style>
    p{
        font-size: 1.2rem;
        font-weight: bold;
        text-align: center;

        margin: 0.5rem 0;
    }

    .main{
        background-color: var(--color-primary);
        width: 100%;

        text-align: center;

        border: 1px solid black;
        padding: 5px;
    }
</style>