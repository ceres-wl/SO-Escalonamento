<script lang="ts">
    import CommonFileInput from "../../../components/FileInput/CommonFileInput.svelte";

    interface Props{
        cliInput: string;
        handleSubmit: () => void;
    }

    let { cliInput = $bindable(), handleSubmit }: Props = $props();

    async function handleFiles(files: FileList | null){
        if(!files || !files[0]) return;
        const txt = await files[0].text();

        const lines = txt.split("\n");

        // kinda HACKy but ok
        const oldCliInput = cliInput;
        for(let line of lines){
            cliInput = line.trim();
            handleSubmit();
        }
        cliInput = oldCliInput;
    }
</script>

<CommonFileInput {handleFiles}>
    {#snippet label()}
        <h2>Arquivo com comandos</h2>
    {/snippet}
</CommonFileInput>