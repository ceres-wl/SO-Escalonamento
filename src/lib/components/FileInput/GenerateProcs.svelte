<script lang="ts">
    import { addProcesso } from '../../context/listaProcesso.svelte';
    import CollapseDiv from '../collapseDiv/CollapseDiv.svelte';
    import BigButton from '../form/bigButton.svelte';

    interface Props{
        simulated: boolean
    }

    let { simulated = $bindable() }: Props = $props();

    interface Range{
        min: number,
        max: number
    }

    let inicio: Range = $state({min: 0, max: 1});
    let duracao: Range = $state({min: 1, max: 1});
    let prioridade: Range = $state({min: 0, max: 1});

    let numeroProcs = $state(1);

    function handleGerar(e: SubmitEvent){
        e.preventDefault();
        simulated = false;

        for(let i = 0; i < numeroProcs; i++){
            const randomInicio = Math.floor(inicio.min + Math.random()*(inicio.max+1));
            const randomDuracao = Math.floor(duracao.min + Math.random()*(duracao.max+1));
            const randomPrioridade = Math.floor(prioridade.min + Math.random()*(prioridade.max+1));

            addProcesso({
                inicio: randomInicio,
                duracao: randomDuracao,
                prioridade_estatica: randomPrioridade
            });
        }
    }
</script>

<!-- TODO ajeitar o estilo dessa coisa -->

<CollapseDiv>
    {#snippet header()}
        <h2>Gerar processos aleatoriamente</h2>
    {/snippet}
    <form onsubmit={handleGerar}>
        <BigButton onclick={() =>{}}>Gerar</BigButton>
        <div>
            {#snippet range(legend: string, range: Range, min = 0)}
            <fieldset>
                <legend>{legend}</legend>
                <label>Minimo
                    <input type="number" bind:value={range.min} {min} id={"generate"+legend+"min"}>
                </label>
                <label>Máximo
                    <input type="number" bind:value={range.max} {min} id={"generate"+legend+"max"}>
                </label>
            </fieldset>
            {/snippet}
        
            {@render range("Inicio", inicio)}
            {@render range("Duração", duracao, 1)}
            {@render range("Prioridade", prioridade)}

            <fieldset>
                <legend>
                    <label for="generate-proc-num">Número de processos gerados</label>
                </legend>
                <input type="number" bind:value={numeroProcs} min="1" id="generate-proc-num">
            </fieldset>
        
        </div>
    </form>
</CollapseDiv>

<style>
    form{
        & > div{
            display: flex;
            flex-wrap: wrap;

            align-items: center;
            justify-content: space-between;

            fieldset{
                min-width: 49%;
            }
        }
    }
</style>