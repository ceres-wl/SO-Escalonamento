# SO-Escalonamento

Um simulador de escalonamento de processos, com interface HTML e algoritmos escritos em c++. Esse projeto foi criado para a disciplina de Sistemas Operacionais do curso de Ciência da Computação da UFC.

Os seguintes algoritmos de escalonamento estão implementados:

- First Come, First Served;
- Shortest Job First;
- Shortest Remaining Time First;
- PrioC
- PrioP
- Round Robin
- Round Robin com prioridade e aging

Acesse a página do projeto em <https://ceres-wl.github.io/SO-Escalonamento/>

## Desenvolvimento

### Dependências

Pra buildar o cpp, você vai precisar instalar o [emscripten](https://emscripten.org/docs/getting_started/downloads.html#installation-instructions-using-the-emsdk-recommended).

É um projeto svelte, precisa do [nodejs e npm](https://nodejs.org/pt-br/download) também.

### Rodando

Para que os escalonadores funcionem, você precisa compilar o código c++ para WebAssembly, o comando buildcpp.sh faz isso, ele foi criado para linux, se você estiver usando um sistema operacional windows provavelmente terá que compilar entrando em *src/lib/cpp* e rodando a versão do esmcripten do cmake manualmente.

Iniciar o servidor de desenvolvimento:

```bash
npm run dev
```

Buildar a página HTML:

```bash
npm run build
```
