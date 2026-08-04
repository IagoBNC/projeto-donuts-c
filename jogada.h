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

#endif /* JOGADA_H */

typedef struct {
 int linhas;
 int colunas;
 TipoMovimento direcaoImposta;
 int houveLiberdade;
} Jogada;
