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

export interface VectorInt extends ClassHandle, Iterable<number> {
  push_back(_0: number): void;
  resize(_0: number, _1: number): void;
  size(): number;
  get(_0: number): number | undefined;
  set(_0: number, _1: number): boolean;
}

export interface VectorPairIB extends ClassHandle, Iterable<PairIB> {
  push_back(_0: PairIB): void;
  resize(_0: number, _1: PairIB): void;
  size(): number;
  get(_0: number): PairIB | undefined;
  set(_0: number, _1: PairIB): boolean;
}

export interface VectorVerboseInfo extends ClassHandle, Iterable<VerboseInfo> {
  push_back(_0: VerboseInfo): void;
  resize(_0: number, _1: VerboseInfo): void;
  size(): number;
  get(_0: number): VerboseInfo | undefined;
  set(_0: number, _1: VerboseInfo): boolean;
}

export type VerboseInfo = {
  passo: number,
  pag_ref: number,
  cur_frames: VectorInt,
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
  frame_ids: VectorInt,
  page_ids: VectorInt,
  verb_info: VectorVerboseInfo
};

interface EmbindModule {
  ALGORITHM: {FIFO: ALGORITHMValue<0>, LRU: ALGORITHMValue<1>, OTIMO: ALGORITHMValue<2>, CLOCK: ALGORITHMValue<3>, NRU: ALGORITHMValue<4>, LFU: ALGORITHMValue<5>, MFU: ALGORITHMValue<6>};
  VectorInt: {
    new(): VectorInt;
  };
  VectorPairIB: {
    new(): VectorPairIB;
  };
  VectorVerboseInfo: {
    new(): VectorVerboseInfo;
  };
  pager(_0: ALGORITHM, _1: number, _2: VectorPairIB, _3: boolean): Saida;
}

export type MainModule = WasmModule & EmbindModule;
export default function MainModuleFactory (options?: unknown): Promise<MainModule>;
