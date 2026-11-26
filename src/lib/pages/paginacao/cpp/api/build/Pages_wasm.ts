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
export interface ALGORITHMValue<T extends number> {
  value: T;
}
export type ALGORITHM = ALGORITHMValue<0>|ALGORITHMValue<1>|ALGORITHMValue<2>|ALGORITHMValue<3>|ALGORITHMValue<4>|ALGORITHMValue<5>|ALGORITHMValue<6>;

export interface vector<int> extends ClassHandle, Iterable<number> {
  push_back(_0: number): void;
  resize(_0: number, _1: number): void;
  size(): number;
  get(_0: number): number | undefined;
  set(_0: number, _1: number): boolean;
}

export interface vector<PairIB> extends ClassHandle, Iterable<PairIB> {
  push_back(_0: PairIB): void;
  resize(_0: number, _1: PairIB): void;
  size(): number;
  get(_0: number): PairIB | undefined;
  set(_0: number, _1: PairIB): boolean;
}

export interface vector<VerboseInfo> extends ClassHandle, Iterable<VerboseInfo> {
  push_back(_0: VerboseInfo): void;
  resize(_0: number, _1: VerboseInfo): void;
  size(): number;
  get(_0: number): VerboseInfo | undefined;
  set(_0: number, _1: VerboseInfo): boolean;
}

export type VerboseInfo = {
  passo: number,
  pag_ref: number,
  cur_frames: vector<int>,
  hit: boolean,
  removed: number,
  escrita: boolean
};

export type PairIB = {
  first: number,
  second: boolean
};

export type Saida = {
  algo: ALGORITHM,
  frames: number,
  referencias: number,
  page_fault: number,
  fault_ratio: number,
  evictions: number,
  disk_writes: number,
  frame_ids: vector<int>,
  page_ids: vector<int>,
  verb_info: vector<VerboseInfo>
};

interface EmbindModule {
  ALGORITHM: {FIFO: ALGORITHMValue<0>, LRU: ALGORITHMValue<1>, OTIMO: ALGORITHMValue<2>, CLOCK: ALGORITHMValue<3>, NRU: ALGORITHMValue<4>, LFU: ALGORITHMValue<5>, MFU: ALGORITHMValue<6>};
  vector<int>: {
    new(): vector<int>;
  };
  vector<PairIB>: {
    new(): vector<PairIB>;
  };
  vector<VerboseInfo>: {
    new(): vector<VerboseInfo>;
  };
  pager(_0: ALGORITHM, _1: number, _2: vector<PairIB>, _3: boolean): Saida;
}

export type MainModule = WasmModule & EmbindModule;
export default function MainModuleFactory (options?: unknown): Promise<MainModule>;
