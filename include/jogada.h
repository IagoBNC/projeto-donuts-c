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

/*
 * Converte uma coordenada em formato de texto (ex.: "A1", "a 1",
 * "F6") para índices de matriz (base 0).
 * Regras de formato aceitas:
 *   - Uma letra (maiúscula ou minúscula) representando a linha,
 *     seguida (com ou sem espaço) por um número representando a
 *     coluna.
 * Parâmetros:
 *   texto      - string de entrada digitada pelo usuário.
 *   linha      - ponteiro onde será gravado o índice de linha (0-based).
 *   coluna     - ponteiro onde será gravado o índice de coluna (0-based).
 *   totalLinhas- quantidade de linhas do tabuleiro (para validar limites).
 *   totalColunas- quantidade de colunas do tabuleiro (para validar limites).
 * Retorno:
 *   1 se o texto está em um formato válido E dentro dos limites do
 *   tabuleiro; 0 caso contrário (erro de formato ou fora dos limites).
 */
int converteCoordenada(const char *texto, int *linha, int *coluna,
                        int totalLinhas, int totalColunas);

/*
 * Insere a peça do jogador atual na posição indicada do tabuleiro.
 * ATENÇÃO: esta função NÃO valida a jogada (isso é responsabilidade
 * de validaJogada, implementada na Etapa 6); ela apenas realiza a
 * escrita da peça, assumindo que a posição já foi validada
 * previamente pelo chamador.
 * Parâmetros:
 *   tabuleiro      - ponteiro para o tabuleiro a ser modificado.
 *   linha, coluna  - posição (índices 0-based) onde a peça será inserida.
 *   simboloJogador - caractere do jogador ('X' ou 'O').
 */
void insereJogada(Tabuleiro *tabuleiro, int linha, int coluna, char simboloJogador);

/*
 * Valida se uma jogada é permitida, de acordo com as regras de
 * posicionamento do DONUTS:
 *   i)   a casa precisa estar vazia;
 *   ii)  a casa precisa estar dentro do tabuleiro;
 *   iii) a casa precisa ter o tipo de movimentação imposto pela
 *        última jogada do oponente (direcaoImposta) — EXCETO se
 *        não houver nenhuma casa vazia daquele tipo no tabuleiro,
 *        caso em que a regra "Freedom" libera qualquer casa vazia.
 * Parâmetros:
 *   tabuleiro      - ponteiro constante para o tabuleiro atual.
 *   linha, coluna  - posição (índices 0-based) a ser validada.
 *   haRestricao    - 0 se não há restrição de direção (ex.: primeira
 *                     jogada da partida); 1 caso contrário.
 *   direcaoImposta - tipo de movimentação exigido pela última jogada
 *                     do oponente (ignorado se haRestricao for 0).
 * Retorno:
 *   1 se a jogada é válida; 0 caso contrário.
 */
int validaJogada(const Tabuleiro *tabuleiro, int linha, int coluna,
                  int haRestricao, TipoMovimento direcaoImposta);

#endif /* JOGADA_H */


