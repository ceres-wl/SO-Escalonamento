<script lang="ts">
    import type { InfoToCopy, Metrics } from "../../types";
    import CopyIcon from "~icons/fa-solid/copy";

    interface Props{
        metrics: Metrics;
        infoToCopy: InfoToCopy;
    }

    let { metrics, infoToCopy }: Props = $props();
</script>

<!-- TODO estilozinho melhor pra isso-->
<section class="main">
    <header>
        <h2>Métricas</h2>
        <div class="copy">
            <button onclick={() => infoToCopy && navigator.clipboard.writeText(infoToCopy.metricasStr) }>Copiar string com métricas <CopyIcon/></button>
            <button onclick={() => infoToCopy && navigator.clipboard.writeText(infoToCopy.diagramaStr)}>Copiar string com diagrama de tempo de execução <CopyIcon/></button>
        </div>
    </header>

    {#snippet metricDiv(header: string, metric: number)}
        <div class="metric-div common-div">
            <header>{header}</header>
            <p>{metric}</p>
        </div>
    {/snippet}

    <div class="display-metrics">
        {@render metricDiv("Turnaround Time(tt)", metrics.turnaround)}
        {@render metricDiv("Waiting Time(tw)", metrics.waiting)}
        {@render metricDiv("Trocas de contexto", metrics.num_change)}
    </div>
</section>

<style>
    .main > header{
        display: flex;
        align-items: center;
        justify-content: space-around;

        h2{
            font-size: 3rem;
            margin: 0;
        }
    }

    .copy{
        display: flex;
        flex-direction: column;
        gap: 5px;
    }

    .metric-div{
        background-color: var(--color-secondary);
    }

    .display-metrics{
        display: flex;
        gap: 5px;
        padding: 5px;
    }
</style>