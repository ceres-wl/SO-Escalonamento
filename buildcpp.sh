cd src/lib/cpp/escalonamento

# Escalonamento
emcmake cmake -B build &&
cmake --build build &&
mkdir api/build &&
mv build/Scheduler_wasm.js api/build &&
mv build/Scheduler_wasm.wasm api/build &&
# Não consegui fazer o cmake gerar com o nome certo, então tou renomeando aqui
mv "build/-lScheduler_wasm.ts" api/build &&
mv "api/build/-lScheduler_wasm.ts" api/build/Scheduler_wasm.ts &&
rm -rf build/*

cd ../memoria

# Memória
emcmake cmake -B build &&
cmake --build build &&
mkdir api/build &&
mv build/Memory_wasm.js api/build &&
mv build/Memory_wasm.wasm api/build &&
# Não consegui fazer o cmake gerar com o nome certo, então tou renomeando aqui
mv "build/-lMemory_wasm.ts" api/build &&
mv "api/build/-lMemory_wasm.ts" api/build/Memory_wasm.ts &&
rm -rf build/*

cd ../paginacao

# Paginação
emcmake cmake -B build &&
cmake --build build &&
mkdir api/build &&
mv build/Pages_wasm.js api/build &&
mv build/Pages_wasm.wasm api/build &&
# Não consegui fazer o cmake gerar com o nome certo, então tou renomeando aqui
mv "build/-lPages_wasm.ts" api/build &&
mv "api/build/-lPages_wasm.ts" api/build/Pages_wasm.ts &&
rm -rf build/*