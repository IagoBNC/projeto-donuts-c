/*
* insert.h
 * ------------------------------------------------------
 * Responsabilidade: Definir a função responsável por executar
 * o "Insert" (captura de peças do oponente) após o posicionamento
 * de uma peça, conforme as regras oficiais do jogo DONUTS.
 * ------------------------------------------------------
 */


#ifndef INSERT_H
#define INSERT_H

#include "tabuleiro.h"

/*
 * Executa o "Insert" a partir da peça recém-inserida em
 * (linha, coluna) pertencente a 'jogador'.
 *
 * Regra: para cada uma das 8 direções ao redor da peça recém
 * colocada, se existirem exatamente duas peças do OPONENTE
 * imediatamente adjacentes seguidas por uma peça do próprio
 * jogador (formando o padrão: [jogador-novo] [oponente] [oponente]
 * [jogador]), as duas peças do oponente são viradas (flipadas)
 * para a cor do jogador atual.
 *
 * Parâmetros:
 *   tabuleiro     - ponteiro para o tabuleiro a ser modificado.
 *   linha, coluna - posição da peça recém-inserida (índices 0-based).
 *   jogador       - símbolo do jogador que acabou de jogar ('X' ou 'O').
 * Retorno:
 *   número total de peças do oponente que foram viradas (0 se
 *   nenhum Insert ocorreu).
 */
int fazInsert(Tabuleiro *tabuleiro, int linha, int coluna, char jogador);

#endif /* INSERT_H */
