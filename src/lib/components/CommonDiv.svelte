<script lang="ts">
// Dumbest component ive ever wrote but it is what it is
const { children, ...props } = $props();
</script>

<div {...props}>
    {@render children()}
</div>

<style>
div{
    background-color: var(--color-primary);
    width: 100%;
    height: 100%;

    overflow: auto;

    text-align: center;

    border: 1px solid black;
    padding: 5px;

    :global(p){
        font-size: 1.2rem;
        font-weight: bold;
        text-align: center;

        margin: 0.5rem 0;
    }
}
</style>