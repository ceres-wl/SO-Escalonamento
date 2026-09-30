<script lang="ts">
    import DragAndDrop from "../form/DragAndDrop.svelte";

    let { handleFiles, label, children} = $props();
</script>

<div class="common-div">
    {@render label()}
    <DragAndDrop handleFiles={handleFiles} />
    {@render children()}
</div>
