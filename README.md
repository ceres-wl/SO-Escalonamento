# SO-Escalonamento

## Dependencias

Pra buildar o cpp, você vai precisar instalar o [emscripten](https://emscripten.org/docs/getting_started/downloads.html#installation-instructions-using-the-emsdk-recommended).

É um projeto svelte, precisa do [nodejs e npm](https://nodejs.org/pt-br/download) também.

## Como rodar

Iniciar o servidor de desenvolvimento:

```bash
npm run dev
```

Se você atualizar algo nos arquivos cpp, rode o seguinte comando para recompilar o webassembly:

```bash
npm run build-wasm
```

Se quiser só buildar *(builda uma página HTML)*:

```bash
npm run build
```
