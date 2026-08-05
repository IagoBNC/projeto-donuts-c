/*
* utils.c
 * ------------------------------------------------------
 * Responsabilidade: Implementar funções utilitárias gerais,
 * como conversão de coordenadas e leitura/validação segura de
 * entradas do usuário via terminal.
 * ------------------------------------------------------
 */

#include "utils.h"
#include <stdlib.h>
#include <time.h>

/*
 * Inicializa a semente do gerador de números pseudoaleatórios
 * usando o horário atual do sistema, garantindo distribuições
 * diferentes a cada execução do programa.
 */
void inicializaSeedAleatoria(void) {
    srand((unsigned int) time(NULL));
}

/*
 * Gera um número inteiro aleatório no intervalo fechado
 * [minimo, maximo], utilizando rand().
 */
int numeroAleatorio(int minimo, int maximo) {
    if (minimo > maximo) {
        /* Troca os valores caso tenham sido informados invertidos */
        int troca = minimo;
        minimo = maximo;
        maximo = troca;
    }
    return minimo + (rand() % (maximo - minimo + 1));
}