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
export interface VectorProc extends ClassHandle, Iterable<Proc> {
  push_back(_0: Proc): void;
  resize(_0: number, _1: Proc): void;
  size(): number;
  get(_0: number): Proc | undefined;
  set(_0: number, _1: Proc): boolean;
}

export interface VectorInt extends ClassHandle, Iterable<number> {
  push_back(_0: number): void;
  resize(_0: number, _1: number): void;
  size(): number;
  get(_0: number): number | undefined;
  set(_0: number, _1: number): boolean;
}

export type ProcInput = {
  id: number,
  inicio: number,
  duracao: number,
  prioridade_estatica: number
};

export type Proc = {
  id: number,
  inicio: number,
  duracao: number,
  prioridade_estatica: number,
  prioridade_dinamica: number,
  tempo_restante: number,
  tempo_espera: number,
  tempo_vida: number
};

export type Saida = {
  tt: number,
  tw: number,
  trocas_contexto: number,
  diagrama_tempo: VectorInt
};

interface EmbindModule {
  VectorProc: {
    new(): VectorProc;
  };
  get_procs(): VectorProc | null;
  VectorInt: {
    new(): VectorInt;
  };
  clear_procs(): void;
  set_config(_0: number, _1: number): void;
  add_proc(_0: ProcInput): void;
  FCFS(): Saida;
  SJF(): Saida;
  SRTF(): Saida;
  prio_c(): Saida;
  prio_p(): Saida;
  round_robin(): Saida;
  round_robin_aging(): Saida;
}

export type MainModule = WasmModule & EmbindModule;
export default function MainModuleFactory (options?: unknown): Promise<MainModule>;
