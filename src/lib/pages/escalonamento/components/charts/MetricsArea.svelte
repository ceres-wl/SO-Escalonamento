<script lang="ts">
    import CommonDiv from "../../../../components/CommonDiv.svelte";
import type { InfoToCopy, Metrics } from "../../types";
    import CopyIcon from "~icons/fa-solid/copy";

    interface Props{
        metrics: Metrics;
        infoToCopy: InfoToCopy;
    }

    let { metrics, infoToCopy }: Props = $props();
</script>

<!-- TODO estilozinho melhor pra isso-->
<section class="chart-div">
    <header>
        <h2>Métricas</h2>
        <div class="copy">
            <button onclick={() => infoToCopy && navigator.clipboard.writeText(infoToCopy.metricasStr) }>Copiar string com métricas <CopyIcon/></button>
            <button onclick={() => infoToCopy && navigator.clipboard.writeText(infoToCopy.diagramaStr)}>Copiar string com diagrama de tempo de execução <CopyIcon/></button>
        </div>
    </header>

    {#snippet metricDiv(header: string, metric: number)}
        <!-- HACK GAMBIARRA!!! -->
        <CommonDiv id="no-padding">
            <div class="metric-div">
                <header>{header}</header>
                <p>{metric}</p>
            </div>
        </CommonDiv>
    {/snippet}

    <div class="display-metrics">
        {@render metricDiv("Turnaround Time(tt)", metrics.turnaround)}
        {@render metricDiv("Waiting Time(tw)", metrics.waiting)}
        {@render metricDiv("Trocas de contexto", metrics.num_change)}
    </div>
</section>

<style>
    @import "/src/lib/components/charts/chartsDiv.css";

    .copy{
        display: flex;
        flex-direction: column;
        align-items: center;
        gap: 5px;
    }

    .metric-div{
        width: 100%;
        height: 100%;

        padding: 0.5rem;

        background-color: var(--color-secondary);
    }

    .display-metrics{
        display: flex;
        gap: 5px;
        padding: 5px;
    }

    :global(#no-padding){
        padding: 0;

        p{
            margin: 0;
        }
    }
</style>