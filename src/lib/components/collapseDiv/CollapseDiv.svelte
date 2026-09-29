<script lang="ts">
    import type { Snippet } from "svelte";
    import { slide } from "svelte/transition";
    import Arrow from '~icons/fa-solid/angle-down';
    import { getDisableAnimation } from "../../context/disableAnimation";

    interface Props{
        header: Snippet;
        children: Snippet;
    }

    let { header, children }: Props = $props();

    let collapsed = $state(true);
</script>

<div class="collapse-div common-div">
    <button onclick={() => collapsed = !collapsed}>
        <header>
            {@render header()}
            <div class={collapsed?null:"rotate"}>
                <Arrow/>
            </div>
        </header>
    </button>
    {#if !collapsed}
    <div transition:slide={{duration: getDisableAnimation()()?0:500}}>
        {@render children()}
    </div>
    {/if}
</div>

<style>
    button{
        all: unset;
        cursor: pointer;
        width: 100%;
    }

    .collapse-div{
        width: 100%;
        height: 100%;

        header{
            display: flex;
            align-items: center;
            justify-content: space-between;
            padding: 0 2.5rem;

            border-bottom: 1px solid var(--color-secondary);

            &:hover{
                background-color: var(--color-secondary);
            }
        }
    }

    .rotate{
        transform: rotate(0.5turn);
    }
</style>