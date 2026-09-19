<script>
    let processFile = $state(null);
    let configFile = $state(null);
</script>

<input bind:files={processFile} type="file" name="processos">
<input bind:files={configFile} type="file" name="config">