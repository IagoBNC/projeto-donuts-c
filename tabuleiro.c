/*
* tabuleiro.c
 * ------------------------------------------------------
 * Responsabilidade: Implementar a criação, inicialização e
 * exibição do tabuleiro do jogo DONUTS, incluindo a distribuição
 * aleatória dos tipos de movimentação (9 de cada tipo).
 * ------------------------------------------------------
 */

#include <stdio.h>
#include <stddef.h>
#include "tabuleiro.h"
#include "utils.h"

/*
 * Embaralha um vetor de TipoMovimento utilizando o algoritmo
 * de Fisher-Yates, garantindo distribuição uniforme aleatória.
 * Função auxiliar interna (uso restrito a este arquivo).
 */
static void embaralhaTipos(TipoMovimento vetor[], int tamanho) {
    for (int i = tamanho - 1; i > 0; i--) {
        int j = numeroAleatorio(0, i);
        TipoMovimento temp = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = temp;
    }
}

/*
 * Inicializa o tabuleiro do jogo DONUTS.
 *
 * Passos:
 *  1. Define as dimensões (linhas e colunas) como TAM_TABULEIRO.
 *  2. Monta um vetor temporário com as 36 casas, sendo 9 de cada
 *     um dos 4 tipos de movimentação (HORIZONTAL, VERTICAL,
 *     DIAGONAL_PRINCIPAL, DIAGONAL_SECUNDARIA).
 *  3. Embaralha esse vetor aleatoriamente.
 *  4. Percorre o tabuleiro 6x6, atribuindo a cada casa um tipo do
 *     vetor embaralhado e marcando-a como vazia.
 */
void inicializaTabuleiro(Tabuleiro *tabuleiro) {
    if (tabuleiro == NULL) {
        return;
    }

    tabuleiro->linhas = TAM_TABULEIRO;
    tabuleiro->colunas = TAM_TABULEIRO;

    int totalCasas = TAM_TABULEIRO * TAM_TABULEIRO; /* 36 */
    int casasPorTipo = totalCasas / QTD_TIPOS;       /* 9 */

    TipoMovimento tiposDisponiveis[TAM_TABULEIRO * TAM_TABULEIRO];
    int indice = 0;

    /* Preenche o vetor com 9 ocorrências de cada tipo */
    for (int tipo = 0; tipo < QTD_TIPOS; tipo++) {
        for (int i = 0; i < casasPorTipo; i++) {
            tiposDisponiveis[indice] = (TipoMovimento) tipo;
            indice++;
        }
    }

    /* Embaralha os tipos para distribuição aleatória no tabuleiro */
    embaralhaTipos(tiposDisponiveis, totalCasas);

    /* Atribui os tipos embaralhados às casas do tabuleiro, que
       iniciam todas vazias */
    indice = 0;
    for (int linha = 0; linha < tabuleiro->linhas; linha++) {
        for (int coluna = 0; coluna < tabuleiro->colunas; coluna++) {
            tabuleiro->casas[linha][coluna].tipo = tiposDisponiveis[indice];
            tabuleiro->casas[linha][coluna].ocupante = CASA_VAZIA;
            indice++;
        }
    }
}

/*
 * Converte um TipoMovimento no caractere usado para representá-lo
 * visualmente no tabuleiro quando a casa está vazia:
 *   HORIZONTAL          -> 'H'
 *   VERTICAL             -> 'V'
 *   DIAGONAL_PRINCIPAL   -> 'P'
 *   DIAGONAL_SECUNDARIA  -> 'S'
 * Função auxiliar interna (uso restrito a este arquivo).
 */
static char caractereDoTipo(TipoMovimento tipo) {
    switch (tipo) {
        case HORIZONTAL:           return 'H';
        case VERTICAL:              return 'V';
        case DIAGONAL_PRINCIPAL:    return 'P';
        case DIAGONAL_SECUNDARIA:   return 'S';
        default:                    return '?';
    }
}

/*
 * Exibe o tabuleiro na tela.
 *
 * Formato:
 *     1   2   3   4   5   6
 *   +---+---+---+---+---+---+
 * A | . | . | . | . | . | . |
 *   +---+---+---+---+---+---+
 * ...
 *
 * Cada casa vazia mostra a letra do seu tipo de movimentação
 * (H/V/P/S); casas ocupadas mostram 'X' ou 'O'.
 */
void exibeTabuleiro(const Tabuleiro *tabuleiro) {
    if (tabuleiro == NULL) {
        return;
    }

    /* Cabeçalho com os números das colunas */
    printf("\n    ");
    for (int coluna = 0; coluna < tabuleiro->colunas; coluna++) {
        printf(" %d  ", coluna + 1);
    }
    printf("\n");

    /* Linha separadora superior */
    printf("   +");
    for (int coluna = 0; coluna < tabuleiro->colunas; coluna++) {
        printf("---+");
    }
    printf("\n");

    /* Conteúdo do tabuleiro, linha a linha */
    for (int linha = 0; linha < tabuleiro->linhas; linha++) {
        printf(" %c |", 'A' + linha);
        for (int coluna = 0; coluna < tabuleiro->colunas; coluna++) {
            Casa casa = tabuleiro->casas[linha][coluna];
            char simbolo = (casa.ocupante != CASA_VAZIA)
                                ? casa.ocupante
                                : caractereDoTipo(casa.tipo);
            printf(" %c |", simbolo);
        }
        printf("\n   +");
        for (int coluna = 0; coluna < tabuleiro->colunas; coluna++) {
            printf("---+");
        }
        printf("\n");
    }

    /* Legenda para o jogador entender os símbolos das casas vazias */
    printf("Legenda (casas vazias): H = Horizontal | V = Vertical | "
           "P = Diagonal Principal | S = Diagonal Secundaria\n");
}

