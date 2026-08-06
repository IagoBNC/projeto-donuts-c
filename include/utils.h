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

#define TAM_MAX_ENTRADA 64  /* Tamanho máximo de uma linha de entrada do usuário */

/*
 * Inicializa a semente do gerador de números pseudoaleatórios
 * (rand()) com base no horário atual. Deve ser chamada uma única
 * vez, no início do programa (em main.c).
 */
void inicializaSeedAleatoria(void);

/*
 * Retorna um número inteiro aleatório dentro do intervalo
 * fechado [minimo, maximo].
 */
int numeroAleatorio(int minimo, int maximo);

/*
 * Limpa o buffer de entrada padrão (stdin), descartando os
 * caracteres restantes até encontrar uma quebra de linha ('\n')
 * ou o fim do arquivo (EOF).
 */
void limpaBufferEntrada(void);

/*
 * Lê uma linha de texto do teclado (stdin) de forma segura,
 * armazenando-a em 'buffer' (sem o caractere de quebra de linha).
 * Retorno: 1 se a leitura foi bem-sucedida, 0 em caso de erro/EOF.
 */
int lerLinha(char *buffer, int tamanho);

/*
 * Verifica se a posição (linha, coluna) está dentro dos limites
 * de uma matriz de dimensões totalLinhas x totalColunas.
 * Retorno: 1 se estiver dentro dos limites, 0 caso contrário.
 */
int dentroLimites(int linha, int coluna, int totalLinhas, int totalColunas);

#endif /* UTILS_H */

