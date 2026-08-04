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

#endif /* VITORIA_H */

typedef struct {
    int visitado[TAM_TABULEIRO][TAM_TABULEIRO];
} MapaVisitados;