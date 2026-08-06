/*
* vitoria.c
 * ------------------------------------------------------
 * Responsabilidade: Implementar verificaVitoria (checagem de 5
 * peças consecutivas em qualquer direção) e o algoritmo de busca
 * (DFS/BFS) da maior região ortogonalmente conectada de peças de
 * cada jogador, usado no critério de fim de partida por limite de
 * turnos/peças.
 * ------------------------------------------------------
 */

#include "../include/vitoria.h"
#include <stddef.h>
#include "../include/utils.h"

#define VITORIA_MINIMA 5 /* Quantidade de pecas em linha necessaria para vencer */

/* Vetores das 4 direções de linha possíveis (uma "metade" de cada
   eixo é suficiente, pois a contagem percorre para os dois lados
   a partir da célula inicial). */
static const int DIRECOES_LINHA[4][2] = {
    {0, 1},   /* Horizontal  */
    {1, 0},   /* Vertical    */
    {1, 1},   /* Diagonal Principal  (\) */
    {1, -1}   /* Diagonal Secundaria (/) */
};

/* Vetores das 4 direções ortogonais (cima, baixo, esquerda, direita),
   usadas na busca de região conectada (sem diagonais). */
static const int DIRECOES_ORTOGONAIS[4][2] = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1}
};

/*
 * Conta quantas peças consecutivas de 'jogador' existem a partir
 * de (linha, coluna), somando a contagem nos dois sentidos da
 * direção (dl, dc) e (-dl, -dc). A própria célula inicial é
 * contada uma vez.
 * Função auxiliar interna (uso restrito a este arquivo).
 */
static int contaSequencia(const Tabuleiro *tabuleiro, int linha, int coluna,
                           int dl, int dc, char jogador) {
    int total = 1; /* conta a propria celula inicial */

    /* Sentido positivo (dl, dc) */
    int l = linha + dl, c = coluna + dc;
    while (dentroLimites(l, c, tabuleiro->linhas, tabuleiro->colunas) &&
           tabuleiro->casas[l][c].ocupante == jogador) {
        total++;
        l += dl;
        c += dc;
    }

    /* Sentido negativo (-dl, -dc) */
    l = linha - dl;
    c = coluna - dc;
    while (dentroLimites(l, c, tabuleiro->linhas, tabuleiro->colunas) &&
           tabuleiro->casas[l][c].ocupante == jogador) {
        total++;
        l -= dl;
        c -= dc;
    }

    return total;
}

/*
 * Verifica se 'jogador' possui 5+ peças em linha em qualquer uma
 * das 4 direções, percorrendo todas as casas do tabuleiro.
 */
int verificaVitoria(const Tabuleiro *tabuleiro, char jogador) {
    if (tabuleiro == NULL) {
        return 0;
    }

    for (int linha = 0; linha < tabuleiro->linhas; linha++) {
        for (int coluna = 0; coluna < tabuleiro->colunas; coluna++) {
            if (tabuleiro->casas[linha][coluna].ocupante != jogador) {
                continue;
            }
            for (int d = 0; d < 4; d++) {
                int dl = DIRECOES_LINHA[d][0];
                int dc = DIRECOES_LINHA[d][1];
                if (contaSequencia(tabuleiro, linha, coluna, dl, dc, jogador) >= VITORIA_MINIMA) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

/*
 * Calcula o tamanho da maior região ortogonalmente conectada de
 * peças de 'jogador', usando busca em largura (BFS) a partir de
 * cada peça ainda não visitada.
 */
int contaMaiorRegiao(const Tabuleiro *tabuleiro, char jogador) {
    if (tabuleiro == NULL) {
        return 0;
    }

    MapaVisitados mapa = {{{0}}};
    int maiorRegiao = 0;

    /* Filas (arrays) para o BFS: no maximo TAM_TABULEIRO*TAM_TABULEIRO
       posicoes podem entrar na fila. */
    int filaLinha[TAM_TABULEIRO * TAM_TABULEIRO];
    int filaColuna[TAM_TABULEIRO * TAM_TABULEIRO];

    for (int linhaInicial = 0; linhaInicial < tabuleiro->linhas; linhaInicial++) {
        for (int colunaInicial = 0; colunaInicial < tabuleiro->colunas; colunaInicial++) {

            if (tabuleiro->casas[linhaInicial][colunaInicial].ocupante != jogador ||
                mapa.visitado[linhaInicial][colunaInicial]) {
                continue;
            }

            /* Inicia um novo BFS a partir dessa peça ainda nao visitada */
            int inicioFila = 0, fimFila = 0;
            filaLinha[fimFila] = linhaInicial;
            filaColuna[fimFila] = colunaInicial;
            fimFila++;
            mapa.visitado[linhaInicial][colunaInicial] = 1;

            int tamanhoRegiao = 0;

            while (inicioFila < fimFila) {
                int linhaAtual = filaLinha[inicioFila];
                int colunaAtual = filaColuna[inicioFila];
                inicioFila++;
                tamanhoRegiao++;

                for (int d = 0; d < 4; d++) {
                    int novaLinha = linhaAtual + DIRECOES_ORTOGONAIS[d][0];
                    int novaColuna = colunaAtual + DIRECOES_ORTOGONAIS[d][1];

                    if (dentroLimites(novaLinha, novaColuna, tabuleiro->linhas, tabuleiro->colunas) &&
                        !mapa.visitado[novaLinha][novaColuna] &&
                        tabuleiro->casas[novaLinha][novaColuna].ocupante == jogador) {

                        mapa.visitado[novaLinha][novaColuna] = 1;
                        filaLinha[fimFila] = novaLinha;
                        filaColuna[fimFila] = novaColuna;
                        fimFila++;
                    }
                }
            }

            if (tamanhoRegiao > maiorRegiao) {
                maiorRegiao = tamanhoRegiao;
            }
        }
    }

    return maiorRegiao;
}