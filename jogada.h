/*
* jogada.h
 * ------------------------------------------------------
 * Responsabilidade: Definir as funções relacionadas à jogada
 * do jogador: leitura de coordenadas, conversão de coordenadas
 * (letra/número) para índices de matriz, e validação da jogada
 * de acordo com as regras de posicionamento do DONUTS.
 * ------------------------------------------------------
 */

#ifndef JOGADA_H
#define JOGADA_H

#include "tabuleiro.h"

/*
 * Struct que representa uma jogada realizada por um jogador.
 * - linha / coluna: posição (em índices de matriz) onde a peça
 *   foi inserida.
 * - direcaoImposta: tipo de movimentação da casa jogada, que
 *   define a direção que o ADVERSÁRIO deverá seguir na próxima
 *   rodada (regra do "Freedom" se não houver espaço válido).
 * - houveLiberdade: indica se o jogador, ao realizar essa jogada,
 *   estava em situação de "Freedom" (sem posição válida na direção
 *   imposta pelo adversário), podendo jogar livremente.
 */
typedef struct {
    int linha;
    int coluna;
    TipoMovimento direcaoImposta;
    int houveLiberdade;
} Jogada;

#endif /* JOGADA_H */


