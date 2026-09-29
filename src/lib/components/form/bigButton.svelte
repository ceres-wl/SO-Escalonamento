<script lang="ts">
    import type { Snippet } from "svelte";

    interface Props{
        children: Snippet;
        onclick: (e: MouseEvent) => any | null | undefined;
    }

    let { children, onclick = () => {} }: Props = $props();
</script>

<button {onclick}>
    {@render children()}
</button>

<style>
    button{
        margin: 0.5rem 0;

        width: 50%;
        max-width: 20rem;

        font-size: 1.5rem;
        font-weight: bold;
    }
</style>