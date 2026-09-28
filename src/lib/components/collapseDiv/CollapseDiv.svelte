<script lang="ts">
    import type { Snippet } from "svelte";
    import Arrow from '~icons/fa-solid/angle-down';

    interface Props{
        header: Snippet;
        children: Snippet;
        collapsed: boolean;
    }

    let { header, collapsed = $bindable(true), children }: Props = $props();
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
    <div>
        {#if !collapsed}
        {@render children()}
        {/if}
    </div>
</div>

<style>
    button{
        all: unset;
        cursor: pointer;
            width: 100%;
    }

    .collapse-div{
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