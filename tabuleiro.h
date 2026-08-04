/*
* tabuleiro.h
 * ------------------------------------------------------
 * Responsabilidade: Definir a estrutura de dados do tabuleiro
 * do jogo DONUTS (6x6), os tipos de movimentação de cada casa
 * (Horizontal, Vertical, Diagonal Principal, Diagonal Secundária)
 * e as funções de criação/inicialização do tabuleiro.
 * ------------------------------------------------------
 */

#ifndef TABULEIRO_H
#define TABULEIRO_H

#endif /* TABULEIRO_H */

typedef enum {
    HORIZONTAL,
    VERTICAL,
    DIAGONAL_PRINCIPAL,
    DIAGONAL_SECUNDARIA,
} TipoMovimento;

typedef struct {
    chat ocupante; // 'X', 'O' ou CASA_VAZIA
    TipoMovimento tipo; // direcao associada a casa
} Casa;

typedef struct {
    Casa casas[TAM_TABULEIRO][TAM_TABULEIRO];
    int linhas;
    int colunas;
} Tabuleiro;