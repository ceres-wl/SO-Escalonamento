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
export type Proc = {
  inicio: number,
  duracao: number,
  prioridade_estatica: number
};

export interface vector<Proc> extends ClassHandle, Iterable<Proc> {
  push_back(_0: Proc): void;
  resize(_0: number, _1: Proc): void;
  size(): number;
  get(_0: number): Proc | undefined;
  set(_0: number, _1: Proc): boolean;
}

interface EmbindModule {
  add_proc(_0: Proc): void;
  vector<Proc>: {
    new(): vector<Proc>;
  };
  get_procs(): vector<Proc> | null;
}

export type MainModule = WasmModule & EmbindModule;
export default function MainModuleFactory (options?: unknown): Promise<MainModule>;
