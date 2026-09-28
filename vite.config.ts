import { svelte } from '@sveltejs/vite-plugin-svelte'
import { defineConfig } from 'vite'
import Icons from 'unplugin-icons/vite';

// https://vite.dev/config/
export default defineConfig({
  plugins: [
    svelte(),
    Icons({ compiler: "svelte"})
  ],
  base: '/SO-Escalonamento/'
})
