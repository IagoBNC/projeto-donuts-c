/*
* jogada.c
 * ------------------------------------------------------
 * Responsabilidade: Implementar a lógica de inserção de peças
 * no tabuleiro e a validação das jogadas (validaJogada), respeitando
 * as regras: posição dentro do tabuleiro, posição vazia, e direção
 * imposta pela última jogada do adversário.
 * ------------------------------------------------------
 */

#include "../include/jogada.h"
#include <ctype.h>
#include <stddef.h>
#include "../include/utils.h"

/*
 * Converte uma coordenada textual (ex.: "A1", "a 1") em índices de
 * matriz (linha, coluna), ambos base 0.
 *
 * Passos:
 *  1. Ignora espaços em branco à esquerda.
 *  2. Lê o primeiro caractere não-branco como a LETRA da linha,
 *     aceitando maiúscula ou minúscula.
 *  3. Ignora espaços em branco entre a letra e o número.
 *  4. Lê o restante como um número inteiro (coluna, base 1).
 *  5. Converte para índices base 0 e verifica se estão dentro dos
 *     limites do tabuleiro.
 */
int converteCoordenada(const char *texto, int *linha, int *coluna,
                        int totalLinhas, int totalColunas) {
    if (texto == NULL || linha == NULL || coluna == NULL) {
        return 0;
    }

    int i = 0;

    /* Pula espaços iniciais */
    while (texto[i] != '\0' && isspace((unsigned char) texto[i])) {
        i++;
    }

    /* Precisa haver uma letra para a linha */
    if (texto[i] == '\0' || !isalpha((unsigned char) texto[i])) {
        return 0;
    }
    char letraLinha = (char) toupper((unsigned char) texto[i]);
    i++;

    /* Pula espaços entre a letra e o número */
    while (texto[i] != '\0' && isspace((unsigned char) texto[i])) {
        i++;
    }

    /* Precisa haver ao menos um dígito para a coluna */
    if (texto[i] == '\0' || !isdigit((unsigned char) texto[i])) {
        return 0;
    }

    int numeroColuna = 0;
    while (texto[i] != '\0' && isdigit((unsigned char) texto[i])) {
        numeroColuna = numeroColuna * 10 + (texto[i] - '0');
        i++;
    }

    /* Pula espaços finais e verifica se não sobrou lixo na string */
    while (texto[i] != '\0' && isspace((unsigned char) texto[i])) {
        i++;
    }
    if (texto[i] != '\0') {
        return 0; /* caracteres inesperados após a coordenada */
    }

    int indiceLinha = letraLinha - 'A';
    int indiceColuna = numeroColuna - 1;

    if (indiceLinha < 0 || indiceLinha >= totalLinhas ||
        indiceColuna < 0 || indiceColuna >= totalColunas) {
        return 0; /* fora dos limites do tabuleiro */
    }

    *linha = indiceLinha;
    *coluna = indiceColuna;
    return 1;
}

/*
 * Insere a peça do jogador na posição informada do tabuleiro.
 * Não realiza validação de regras — apenas escreve o símbolo do
 * jogador na casa indicada.
 */
void insereJogada(Tabuleiro *tabuleiro, int linha, int coluna, char simboloJogador) {
    if (tabuleiro == NULL) {
        return;
    }
    if (linha < 0 || linha >= tabuleiro->linhas ||
        coluna < 0 || coluna >= tabuleiro->colunas) {
        return; /* posição fora do tabuleiro: nao faz nada */
    }
    tabuleiro->casas[linha][coluna].ocupante = simboloJogador;
}

/*
 * Verifica se existe, no tabuleiro, ao menos uma casa VAZIA cujo
 * tipo de movimentação seja igual a 'tipo'. Usada por validaJogada
 * para decidir se a regra de "Freedom" deve ser aplicada (quando
 * não existe nenhuma casa vazia com a direção imposta).
 * Função auxiliar interna (uso restrito a este arquivo).
 */
static int existeCasaVaziaComTipo(const Tabuleiro *tabuleiro, TipoMovimento tipo) {
    for (int linha = 0; linha < tabuleiro->linhas; linha++) {
        for (int coluna = 0; coluna < tabuleiro->colunas; coluna++) {
            const Casa *casa = &tabuleiro->casas[linha][coluna];
            if (casa->ocupante == CASA_VAZIA && casa->tipo == tipo) {
                return 1;
            }
        }
    }
    return 0;
}

/*
 * Valida uma jogada segundo as regras de posicionamento do DONUTS.
 * Ver documentação completa em jogada.h.
 */
int validaJogada(const Tabuleiro *tabuleiro, int linha, int coluna,
                  int haRestricao, TipoMovimento direcaoImposta) {
    if (tabuleiro == NULL) {
        return 0;
    }

    /* Regra ii: precisa estar dentro do tabuleiro */
    if (!dentroLimites(linha, coluna, tabuleiro->linhas, tabuleiro->colunas)) {
        return 0;
    }

    /* Regra i: precisa estar vazia */
    if (tabuleiro->casas[linha][coluna].ocupante != CASA_VAZIA) {
        return 0;
    }

    /* Regra iii: precisa respeitar a direção imposta pelo adversário,
       a menos que não exista nenhuma casa vazia com essa direção
       (regra de "Freedom", que libera qualquer casa vazia). */
    if (haRestricao) {
        if (existeCasaVaziaComTipo(tabuleiro, direcaoImposta)) {
            if (tabuleiro->casas[linha][coluna].tipo != direcaoImposta) {
                return 0;
            }
        }
        /* Caso contrário: Freedom ativa, qualquer casa vazia é válida
           (regras i e ii já garantidas acima). */
    }

    return 1;
}