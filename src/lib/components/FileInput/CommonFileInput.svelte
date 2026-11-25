<script lang="ts">
    import type { Snippet } from "svelte";
    import CommonDiv from "../CommonDiv.svelte";
    import DragAndDrop from "../form/DragAndDrop.svelte";

    interface Props{
        handleFiles: (f: FileList | null) => void,
        label: Snippet
        children?: Snippet
    }

    let { handleFiles, label, children }: Props = $props();
</script>

<CommonDiv>
    {@render label()}
    <DragAndDrop handleFiles={handleFiles} />
    {#if children}
    {@render children()}
    {/if}
</CommonDiv>
