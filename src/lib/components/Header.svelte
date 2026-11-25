<script lang="ts">
    import SchedulingIcon from '../../assets/scheduling_nobg.webp';

    interface Props{
        page: string;
        disableAnimation: boolean;
    }

    let { page, disableAnimation = $bindable() }: Props = $props();
</script>

<div class="header">
    <div class="flex-center">
        <img class="pixelated" src={SchedulingIcon} alt="Icone de temporizador">
        <h1>Simulação de {page}</h1>
    </div>
    
    <label> Desativar animações
        <input type="checkbox" bind:checked={disableAnimation}>
    </label>
</div>

<style>
    .header{
        display: flex;
        align-items: center;
        justify-content: space-between;

        color: white;

        h1{
            display: inline;
            font-size: 2rem;
        }
        img{
            height: 4rem;
            display: inline;
        }
    }
</style>