<script lang="ts">
    import { Axis, BarChart, Polygon, Text, Tooltip } from "layerchart";
    import type { DataPoint } from "../../../../types";
    import { hashedHexColor, resetSeed } from "../../../../utils/randomColor";
    import { memoria } from "../../context/memoria.svelte";

    interface DataPointMem extends DataPoint{
        livre: boolean;
        tamanho: number;
    }
    
    const data: Array<DataPointMem> = $derived(Array.from(memoria.mem)
        .map((bloco) =>{
            return {
                id: bloco.id.toString(),
                start: bloco.endereco,
                end: bloco.endereco+bloco.tamanho,
                livre: bloco.livre,
                tamanho: bloco.tamanho,
                label: bloco.id.toString()
            }
        })
    );

    $effect(() =>{
        data;
        resetSeed();
    });

    function getColorDomain(data: Array<DataPoint>){
        const set: Set<string> = new Set();
        for(let point of data) set.add(point.id);
        const cDomain = Array.from(set.values());
        const cRange = cDomain.map((e) => e=="0"?"#000000":hashedHexColor(e));
            
        return {
            c: "id",
            cDomain,
            cRange
        }
    }

</script>

<BarChart
	{data}
	x={['start', 'end']}
	y={(d) => 1}
	xBaseline={null}
	xNice={false}
    {...getColorDomain(data)}
	bandPadding={0}
	padding={{ top: 12, bottom: 12 }}
	orientation="horizontal"
	props={{
		tooltip: {
			context: { mode: 'bisect-band' }
		}
	}}
	height={80}
    labels={{
        value: (d) => d.label ?? null,
        placement: 'center',
        fill: 'white'
    }}
>
	{#snippet axis({ context })}
		<Axis placement="bottom" tickLength={1} ticks={data.map((e) => e.start).concat([memoria.tam_total])}>
			{#snippet tickLabel({ props })}
				<Text {...props} textAnchor={props.value === '40' ? 'end' : 'start'} />
			{/snippet}
		</Axis>
	{/snippet}

	{#snippet aboveMarks({ context })}
		<Polygon
			cx={context.xScale(memoria.ptr_next_fit)}
			cy={-4}
			r={8}
			points={3}
			rotate={90}
			class="mark"
		/>
	{/snippet}

	{#snippet tooltip({ context })}
		<Tooltip.Root>
			{#snippet children({ data }: {data: DataPointMem})}
				<Tooltip.List>
					<Tooltip.Item label="id:" value={data.label} />
					<Tooltip.Item label="Tamanho:" value="{data.tamanho} byte(s)" />
					<Tooltip.Item label="Intervalo:" value="{data.start} - {data.end}" />
					<Tooltip.Item label="Livre:" value={data.livre?"Sim":"Não"} />
				</Tooltip.List>
			{/snippet}
		</Tooltip.Root>
	{/snippet}
</BarChart>

<style>
    :global(.mark){
        color: black;
        stroke: var(--color-accent);
        stroke-width: 2px;
    }
</style>