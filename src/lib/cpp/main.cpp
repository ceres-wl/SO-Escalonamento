#include <iostream>
#include <emscripten/emscripten.h>

// Não tirar isso aqui!!
#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif

EXTERN EMSCRIPTEN_KEEPALIVE float add(float a, float b) {
    return a + b;
}

EXTERN EMSCRIPTEN_KEEPALIVE void helloWorld() {
    std::cout << "Hello world" << std::endl;
}