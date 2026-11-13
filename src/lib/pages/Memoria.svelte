<script lang="ts">
    // Todos os comandos devem ser apis do cpp, 
    // Memória pode ser um vetor de struct criada no cpp tbm

    let cmd = $state("");

    function handleSubmit(e: SubmitEvent){
        e.preventDefault();
        // TODO parser de comandos

        // TODO chamar o comando da api
    }
</script>

<main>
    <form onsubmit={handleSubmit}>
        <!-- TODO decidir se coloco um label -->
        <input bind:value={cmd} type="text">
        <button>Enviar</button>
    </form>
    <!-- Alguma forma de visualização aqui-->
</main>