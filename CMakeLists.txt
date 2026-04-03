cmake_minimum_required(VERSION 4.2)
project(src)

set(CMAKE_CXX_STANDARD 20)

add_executable(src
    main.cpp
    src/ListaEnlazada.cpp
    src/ListaEnlazadaOrdenada.cpp
    src/ArbolAVL.cpp
)

target_include_directories(src PRIVATE include)
