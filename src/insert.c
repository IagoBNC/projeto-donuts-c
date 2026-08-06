/*
* insert.c
 * ------------------------------------------------------
 * Responsabilidade: Implementar a função fazInsert, que verifica
 * em todas as direções (horizontal, vertical, diagonal principal
 * e diagonal secundária) se a peça recém-inserida "flanqueia"
 * peças do adversário, virando-as para a cor do jogador atual.
 * ------------------------------------------------------
 */

#include "../include/insert.h"
#include <stddef.h>
#include "../include/utils.h"

/* Vetores das 8 direções possíveis a partir de uma casa:
   N, S, L, O, NE, NO, SE, SO. */
static const int DIRECOES[8][2] = {
    {-1,  0}, { 1,  0}, { 0,  1}, { 0, -1},
    {-1,  1}, {-1, -1}, { 1,  1}, { 1, -1}
};

/*
 * Executa o Insert a partir da posição (linha, coluna) recém-jogada
 * por 'jogador'. Para cada direção, verifica o padrão:
 *   posição 1 e 2 (a partir da peça nova) = peças do OPONENTE
 *   posição 3                              = peça do próprio jogador
 * Se o padrão ocorrer, as duas peças do oponente são viradas.
 */
int fazInsert(Tabuleiro *tabuleiro, int linha, int coluna, char jogador) {
    if (tabuleiro == NULL) {
        return 0;
    }

    char oponente = (jogador == 'X') ? 'O' : 'X';
    int totalViradas = 0;

    for (int d = 0; d < 8; d++) {
        int dl = DIRECOES[d][0];
        int dc = DIRECOES[d][1];

        int l1 = linha + dl,     c1 = coluna + dc;
        int l2 = linha + 2 * dl, c2 = coluna + 2 * dc;
        int l3 = linha + 3 * dl, c3 = coluna + 3 * dc;

        /* Se a terceira posição está dentro do tabuleiro, as duas
           primeiras também estão (estão mais próximas da origem). */
        if (!dentroLimites(l3, c3, tabuleiro->linhas, tabuleiro->colunas)) {
            continue;
        }

        int ehOponente1 = (tabuleiro->casas[l1][c1].ocupante == oponente);
        int ehOponente2 = (tabuleiro->casas[l2][c2].ocupante == oponente);
        int ehProprio3  = (tabuleiro->casas[l3][c3].ocupante == jogador);

        if (ehOponente1 && ehOponente2 && ehProprio3) {
            tabuleiro->casas[l1][c1].ocupante = jogador;
            tabuleiro->casas[l2][c2].ocupante = jogador;
            totalViradas += 2;
        }
    }

    return totalViradas;
}
