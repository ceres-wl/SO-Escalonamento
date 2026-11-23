Set-Location src/lib/cpp/escalonamento

# Escalonamento
emcmake cmake -B build
cmake --build build
mkdir -Force api/build
Move-Item -Force build/Scheduler_wasm.js api/build
Move-Item -Force build/Scheduler_wasm.wasm api/build
# Não consegui fazer o cmake gerar com o nome certo, então tou renomeando aqui
Move-Item -Force "build/-lScheduler_wasm.ts" api/build
Move-Item -Force "api/build/-lScheduler_wasm.ts" api/build/Scheduler_wasm.ts
Remove-Item -Recurse build/*

Set-Location ../memoria

# Memória
emcmake cmake -B build
cmake --build build
mkdir -Force api/build
Move-Item -Force build/Memory_wasm.js api/build
Move-Item -Force build/Memory_wasm.wasm api/build
# Não consegui fazer o cmake gerar com o nome certo, então tou renomeando aqui
Move-Item -Force "build/-lMemory_wasm.ts" api/build
Move-Item -Force "api/build/-lMemory_wasm.ts" api/build/Memory_wasm.ts
Remove-Item -Recurse build/*

Set-Location ../paginacao

# Paginação
emcmake cmake -B build
cmake --build build
mkdir -Force api/build
Move-Item -Force build/Pages_wasm.js api/build
Move-Item -Force build/Pages_wasm.wasm api/build
# Não consegui fazer o cmake gerar com o nome certo, então tou renomeando aqui
Move-Item -Force "build/-lPages_wasm.ts" api/build
Move-Item -Force "api/build/-lPages_wasm.ts" api/build/Pages_wasm.ts
Remove-Item -Recurse build/*

Set-Location ../../../..