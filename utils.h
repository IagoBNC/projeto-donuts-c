/*
* utils.h
 * ------------------------------------------------------
 * Responsabilidade: Definir funções utilitárias gerais do projeto:
 * conversão de coordenadas (ex: letra->índice, número->índice),
 * leitura segura de entrada do usuário, e outras funções auxiliares
 * compartilhadas entre os módulos.
 * ------------------------------------------------------
 */


#ifndef UTILS_H
#define UTILS_H

/*
 * Inicializa a semente do gerador de números pseudoaleatórios
 * (rand()) com base no horário atual. Deve ser chamada uma única
 * vez, no início do programa (em main.c).
 */
void inicializaSeedAleatoria(void);

/*
 * Retorna um número inteiro aleatório dentro do intervalo
 * fechado [minimo, maximo].
 * Parâmetros:
 *   minimo - menor valor possível (inclusive)
 *   maximo - maior valor possível (inclusive)
 * Retorno: inteiro aleatório no intervalo informado.
 */
int numeroAleatorio(int minimo, int maximo);

#endif /* UTILS_H */

