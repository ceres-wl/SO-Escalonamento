<script lang="ts">
    import HorizontalBars from "../../../../components/charts/HorizontalBars.svelte";
    import type { DataPoint } from "../../../../types";
    import { memoria } from "../../context/memoria.svelte";
    import type { Memoria } from "../../cpp/api/build/Memory_wasm";
    
    // ideias de graficos melhores:
    // https://www.layerchart.com/docs/components/BarChart/single-stack-with-indicator
    // https://www.layerchart.com/docs/components/BarChart/single-dimension

    interface Props{
        mem: Memoria;
    }

    const { mem }: Props = $props();
    
    // TODO fazer cor do bloco ser definida baseado nele estar livre ou nn
    const data: Array<DataPoint> = $derived(Array.from(mem.mem)
        .map((bloco) =>{
            return {
                id: bloco.id.toString(),
                start: bloco.endereco,
                end: bloco.endereco+bloco.tamanho,
                label: bloco.tamanho.toString()
            }
        })
    );

    function getXDomain(data: Array<DataPoint>){
        return [
            0,
            memoria.tam_total
        ]
    }

    function getYDomain(data: Array<DataPoint>){
        return data.map((data) => data.id);
    }

</script>

<HorizontalBars 
    title="Blocos de memória"
    {data}
    {getXDomain}
    {getYDomain}
/>