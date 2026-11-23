cmake_minimum_required(VERSION 3.14)
project(Memory_wasm)

set(CMAKE_CXX_STANDARD 17)
set(NO_EXIT_RUNTIME 1)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_executable(Memory_wasm ${SRC_FILES})

target_link_libraries(Memory_wasm PUBLIC -lembind -sEXPORT_ES6 -O3 --emit-tsd Memory_wasm.ts)

#em++ -lembind -o src/lib/cpp/main.js src/lib/cpp/main.cpp -O3 -sEXPORT_ES6 --emit-tsd main.ts