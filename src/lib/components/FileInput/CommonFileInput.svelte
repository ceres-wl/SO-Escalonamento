<script lang="ts">
    import DragAndDrop from "../form/DragAndDrop.svelte";

    let { handleFiles, label, children } = $props();
</script>

<!--
    TODO input de texto bonitinho
    TODO fonte
    TODO uma polida no tamanho e espaçamento das coisas
-->

<div class="common-div">
    {@render label()}
    <DragAndDrop handleFiles={handleFiles} />
    {@render children()}
</div>

<style>
</style>