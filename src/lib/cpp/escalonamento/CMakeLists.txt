cmake_minimum_required(VERSION 3.14)
project(Scheduler_wasm)

set(CMAKE_CXX_STANDARD 17)
set(NO_EXIT_RUNTIME 1)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_executable(Scheduler_wasm ${SRC_FILES})

target_link_libraries(Scheduler_wasm PUBLIC -lembind -sEXPORT_ES6 -O3 --emit-tsd Scheduler_wasm.ts)

#em++ -lembind -o src/lib/cpp/main.js src/lib/cpp/main.cpp -O3 -sEXPORT_ES6 --emit-tsd main.ts