<script lang="ts">
    import { Axis, BarChart, Polygon, Text, Tooltip } from "layerchart";
    import type { DataPoint } from "../../../../types";
    import type { Memoria } from "../../cpp/api/build/Memory_wasm";
    import { hashedHexColor, resetSeed } from "../../../../utils/randomColor";

    interface Props{
        mem: Memoria;
    }

    const { mem }: Props = $props();

    interface DataPointMem extends DataPoint{
        livre: boolean;
        tamanho: number;
    }
    
    const data: Array<DataPointMem> = $derived(Array.from(mem.mem)
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

    function getYDomain(data: Array<DataPoint>){
        return data.map((data) => data.id);
    }

</script>

<BarChart
	{data}
	x={['start', 'end']}
	y={(d) => 1}
	xBaseline={null}
	xNice={false}
	c="id"
    cDomain={getYDomain(data)}
	cRange={data.map((e) => e.livre?"#000000":hashedHexColor(e.id))}
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
		<Axis placement="bottom" tickLength={1} ticks={data.map((e) => e.start).concat([mem.tam_total])}>
			{#snippet tickLabel({ props })}
				<Text {...props} textAnchor={props.value === '40' ? 'end' : 'start'} />
			{/snippet}
		</Axis>
	{/snippet}

	{#snippet aboveMarks({ context })}
		<Polygon
			cx={context.xScale(mem.ptr_next_fit)}
			cy={-3}
			r={6}
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
        color: white;
    }
</style>