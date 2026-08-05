cmake_minimum_required(VERSION 3.20)

project(projeto_donuts_c C)

set(CMAKE_C_STANDARD 99)

add_executable(projeto_donuts
        main.c
        tabuleiro.c
        jogada.c
        insert.c
        vitoria.c
        utils.c
)