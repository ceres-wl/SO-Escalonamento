// TypeScript bindings for emscripten-generated code.  Automatically generated at compile time.
interface WasmModule {
}

export interface ClassHandle {
  isAliasOf(other: ClassHandle): boolean;
  delete(): void;
  deleteLater(): this;
  isDeleted(): boolean;
  // @ts-ignore - If targeting lower than ESNext, this symbol might not exist.
  [Symbol.dispose](): void;
  clone(): this;
}
export interface OpcaoValue<T extends number> {
  value: T;
}
export type Opcao = OpcaoValue<0>|OpcaoValue<1>|OpcaoValue<2>;

export interface VectorBloco extends ClassHandle, Iterable<Bloco> {
  push_back(_0: Bloco): void;
  resize(_0: number, _1: Bloco): void;
  size(): number;
  get(_0: number): Bloco | undefined;
  set(_0: number, _1: Bloco): boolean;
}

export type Bloco = {
  id: number,
  endereco: number,
  tamanho: number,
  livre: boolean
};

export type Memoria = {
  tam_total: number,
  mem: VectorBloco,
  id_atual: number,
  ptr_next_fit: number
};

export type SaidaFree = {
  sucesso: boolean,
  mem: Memoria
};

export type SaidaDefrag = {
  blocos_movidos: number,
  mem_deslocada: number,
  mem: Memoria
};

export type Saida = {
  id: number,
  ocupado: number,
  livre: number,
  buracos: number,
  maior_buraco_livre: number,
  uso_efetivo: number,
  conseguiu_alocar: boolean,
  mem: Memoria
};

interface EmbindModule {
  Opcao: {INIT: OpcaoValue<0>, END: OpcaoValue<1>, OPT: OpcaoValue<2>};
  VectorBloco: {
    new(): VectorBloco;
  };
  create_memoria(_0: number): Memoria;
  freeid(_0: Memoria, _1: number): SaidaFree;
  freeaddr(_0: Memoria, _1: number): SaidaFree;
  defrag(_0: Memoria, _1: Opcao): SaidaDefrag;
  FirstFit(_0: Memoria, _1: number): Saida;
  BestFit(_0: Memoria, _1: number): Saida;
  WorstFit(_0: Memoria, _1: number): Saida;
  NextFit(_0: Memoria, _1: number): Saida;
  gerar_saida(_0: Memoria, _1: boolean): Saida;
}

export type MainModule = WasmModule & EmbindModule;
export default function MainModuleFactory (options?: unknown): Promise<MainModule>;
