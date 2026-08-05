/*
* main.c
 * ------------------------------------------------------
 * Responsabilidade: Ponto de entrada do programa. Responsável por
 * orquestrar o fluxo geral do jogo DONUTS: inicializar o tabuleiro,
 * conduzir o laço principal de turnos (jogada -> insert -> verificação
 * de vitória) e exibir o resultado final da partida.
 * ------------------------------------------------------
 */

#include <stdio.h>
#include "tabuleiro.h"
#include "jogada.h"
#include "insert.h"
#include "vitoria.h"
#include "utils.h"

int main(void) {
    Tabuleiro tabuleiro;

    inicializaSeedAleatoria();
    inicializaTabuleiro(&tabuleiro);

    /* Verificação de sanidade (temporária): conta quantas casas
       de cada tipo foram geradas, para confirmar que a distribuição
       de 9/9/9/9 está correta. A exibição visual do tabuleiro será
       implementada na Etapa 4. */
    int contagem[QTD_TIPOS] = {0, 0, 0, 0};
    for (int i = 0; i < tabuleiro.linhas; i++) {
        for (int j = 0; j < tabuleiro.colunas; j++) {
            contagem[tabuleiro.casas[i][j].tipo]++;
        }
    }

    printf("Tabuleiro inicializado (%dx%d).\n", tabuleiro.linhas, tabuleiro.colunas);
    printf("Distribuicao de tipos -> Horizontal: %d | Vertical: %d | Diagonal Principal: %d | Diagonal Secundaria: %d\n",
           contagem[HORIZONTAL], contagem[VERTICAL],
           contagem[DIAGONAL_PRINCIPAL], contagem[DIAGONAL_SECUNDARIA]);

    exibeTabuleiro(&tabuleiro);

    return 0;
}

