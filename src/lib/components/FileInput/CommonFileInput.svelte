<script lang="ts">
    import CommonDiv from "../CommonDiv.svelte";
import DragAndDrop from "../form/DragAndDrop.svelte";

    let { handleFiles, label, children} = $props();
</script>

<CommonDiv>
    {@render label()}
    <DragAndDrop handleFiles={handleFiles} />
    {@render children()}
</CommonDiv>
