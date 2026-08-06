/*
* vitoria.h
* ------------------------------------------------------
* Responsabilidade: Definir as funções relacionadas à verificação
* de vitória: checagem de 5 peças em linha (verificaVitoria) e
* busca da maior região conectada de peças (usada no critério de
* desempate após 30 peças no tabuleiro).
* ------------------------------------------------------
*/

#ifndef VITORIA_H
#define VITORIA_H

#include "tabuleiro.h"

/*
 * Struct usada para marcar quais casas já foram visitadas
 * durante a busca (BFS) da maior região conectada de peças.
 * Mantida separada da struct Casa para não misturar dados
 * permanentes do jogo com dados temporários de algoritmo.
 */
typedef struct {
    int visitado[TAM_TABULEIRO][TAM_TABULEIRO];
} MapaVisitados;

/*
 * Verifica se 'jogador' possui 5 ou mais peças consecutivas em
 * alguma direção (horizontal, vertical, diagonal principal ou
 * diagonal secundária) no tabuleiro.
 * Parâmetros:
 *   tabuleiro - ponteiro constante para o tabuleiro atual.
 *   jogador   - símbolo do jogador a ser verificado ('X' ou 'O').
 * Retorno:
 *   1 se o jogador venceu (5+ em linha); 0 caso contrário.
 */
int verificaVitoria(const Tabuleiro *tabuleiro, char jogador);

/*
 * Calcula o tamanho da maior região ORTOGONALMENTE conectada
 * (cima, baixo, esquerda, direita — sem diagonais) de peças de
 * 'jogador', usando busca em largura (BFS). Utilizada no critério
 * de desempate quando a partida termina por limite de 30 peças.
 * Parâmetros:
 *   tabuleiro - ponteiro constante para o tabuleiro atual.
 *   jogador   - símbolo do jogador a ser verificado ('X' ou 'O').
 * Retorno:
 *   tamanho (quantidade de peças) da maior região conectada.
 */
int contaMaiorRegiao(const Tabuleiro *tabuleiro, char jogador);

#endif /* VITORIA_H */


