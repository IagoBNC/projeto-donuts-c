/*
* utils.c
 * ------------------------------------------------------
 * Responsabilidade: Implementar funções utilitárias gerais,
 * como conversão de coordenadas e leitura/validação segura de
 * entradas do usuário via terminal.
 * ------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/utils.h"

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

/*
 * Descarta os caracteres restantes no buffer de entrada (stdin)
 * até encontrar '\n' ou EOF. Usada para evitar que "sobras" de
 * uma leitura anterior interfiram na próxima.
 */
void limpaBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* descarta o caractere */
    }
}

/*
 * Lê uma linha do teclado de forma segura usando fgets, removendo
 * o caractere de quebra de linha ('\n') ao final, caso presente.
 * Caso a linha digitada seja maior que o buffer, o restante é
 * descartado do stdin para não corromper leituras futuras.
 */
int lerLinha(char *buffer, int tamanho) {
    if (buffer == NULL || tamanho <= 0) {
        return 0;
    }

    if (fgets(buffer, tamanho, stdin) == NULL) {
        return 0; /* erro de leitura ou EOF */
    }

    /* Verifica se a linha foi lida por completo (contém '\n') */
    size_t comprimento = strlen(buffer);
    if (comprimento > 0 && buffer[comprimento - 1] == '\n') {
        buffer[comprimento - 1] = '\0';
    } else {
        /* Linha maior que o buffer: descarta o restante do stdin */
        limpaBufferEntrada();
    }

    return 1;
}

/*
 * Verifica se a posição (linha, coluna) está dentro dos limites
 * válidos de uma matriz totalLinhas x totalColunas.
 */
int dentroLimites(int linha, int coluna, int totalLinhas, int totalColunas) {
    return (linha >= 0 && linha < totalLinhas && coluna >= 0 && coluna < totalColunas);
}