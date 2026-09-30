cd src/lib/cpp

emcmake cmake -B build &&
cmake --build build &&
mkdir api/build &&
mv build/Scheduler_wasm.js api/build &&
mv build/Scheduler_wasm.wasm api/build &&
# Não consegui fazer o cmake gerar com o nome certo, então tou renomeando aqui
mv "build/-lScheduler_wasm.ts" api/build &&
mv "api/build/-lScheduler_wasm.ts" api/build/Scheduler_wasm.ts &&
rm -rf build/*