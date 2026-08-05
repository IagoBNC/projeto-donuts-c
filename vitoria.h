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
 * durante a busca (DFS/BFS) da maior região conectada de peças.
 * Mantida separada da struct Casa para não misturar dados
 * permanentes do jogo com dados temporários de algoritmo.
 */
typedef struct {
    int visitado[TAM_TABULEIRO][TAM_TABULEIRO];
} MapaVisitados;

#endif /* VITORIA_H */


