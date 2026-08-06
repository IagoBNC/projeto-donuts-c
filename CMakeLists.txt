cmake_minimum_required(VERSION 3.20)

project(projeto_donuts_c C)

set(CMAKE_C_STANDARD 99)

add_executable(projeto_donuts
        src/main.c
        src/tabuleiro.c
        src/jogada.c
        src/insert.c
        src/vitoria.c
        src/utils.c
)
target_include_directories(projeto_donuts PRIVATE include)