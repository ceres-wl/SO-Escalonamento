// TypeScript bindings for emscripten-generated code.  Automatically generated at compile time.
interface WasmModule {
  _add(_0: number, _1: number): number;
  _helloWorld(): void;
}

export type MainModule = WasmModule;
export default function MainModuleFactory (options?: unknown): Promise<MainModule>;
