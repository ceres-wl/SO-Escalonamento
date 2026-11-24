param(
    [Parameter()]
    [string]$remake = 'false',
    [string]$delete_prev = 'false'
)

function SO-build {
    param (
        [string]$fn_remake,
        [string]$fn_delete_prev,
        [string]$name
    )

    if ($fn_remake -eq 'true') {
        emcmake cmake -B build
    }
    cmake --build build
    mkdir -Force api/build
    Move-Item -Force "build/$($name).js" api/build
    Move-Item -Force "build/$($name).wasm" api/build
    Move-Item -Force "build/-l$($name).ts" api/build
    Move-Item -Force "api/build/-l$($name).ts" "api/build/$($name).ts"
    if ($fn_delete_prev -eq 'true') {
        Remove-Item -Recurse build/*
    }
}

Set-Location src/lib/pages/escalonamento/cpp
SO-build -fn_remake $remake -fn_delete_prev $delete_prev -name "Scheduler_wasm"

Set-Location ../../memoria/cpp
SO-build -fn_remake $remake -fn_delete_prev $delete_prev "Memory_wasm"

Set-Location ../../paginacao/cpp
SO-build -fn_remake $remake -fn_delete_prev $delete_prev "Pages_wasm"

Set-Location ../../../../..