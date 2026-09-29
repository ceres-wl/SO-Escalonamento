<script lang="ts">
    import FileUpload from '~icons/fa-solid/file-upload';
    import FileImport from '~icons/fa-solid/file-import';

    let dragging = $state(false);
    let dragCounter = 0;

    let { handleFiles, ...props } = $props();

    function handleDragIn(e: DragEvent){
        if(e.dataTransfer?.items && e.dataTransfer.items.length > 0){
            dragCounter++;
            dragging = true;
        }
    }
    function handleDragOut(e: DragEvent){
        e.preventDefault();
        dragCounter--;
        if(dragCounter <= 0) dragging = false;
    }
    function handleDrop(e: DragEvent){
        e.preventDefault();

        if(e.dataTransfer) handleFiles(e.dataTransfer.files);
        dragCounter = 0;
        dragging = false;
    }
    function handleDragOver(e: DragEvent){
        e.preventDefault();
    }
</script>

<div class="dragzone" ondragover={handleDragOver} ondragenter={handleDragIn} ondragleave={handleDragOut} ondrop={handleDrop} role="button" tabindex="0">
    <label>
        {#if dragging}
        <FileImport class="icon-insc" height="1rem" width="1rem"/>
        {:else}
        <FileUpload class="icon-insc" height="1rem" width="1rem"/>
        {/if}
        <!-- {#if dragging}
            <p>Solte para fazer o upload</p>
        {:else}
            <p>Escolha um arquivo ou arraste para essa região</p>
        {/if} -->
        <div class="center">
            <input id="file-select" type="file" onchange={(e) => {
                const target = e.target as HTMLInputElement;
                handleFiles(target.files);
            }} {...props}>
        </div>
    </label>
</div>

<style>
    .dragzone{
        display: flex;
        align-items: center;
        flex-direction: column;
        border: 2px dashed var(--color-accent);
    }

    :global(.icon-insc){
        width: 3rem;
        height: 3rem;
    }

    label{
        display: block;
        text-align: center;

        width: 100%;
        height: 100%;

        padding: 1.25rem;
    }

    :global(svg){
        pointer-events: none;
    }
</style>