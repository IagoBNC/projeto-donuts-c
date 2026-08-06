/*
* main.c
 * ------------------------------------------------------
 * Responsabilidade: Ponto de entrada do programa. Responsável por
 * orquestrar o fluxo geral do jogo DONUTS: inicializar o tabuleiro,
 * conduzir o laço principal de turnos (jogada -> insert -> verificação
 * de vitória) e exibir o resultado final da partida.
 * ------------------------------------------------------
 */

#include <stdio.h>
#include "../include/tabuleiro.h"
#include "../include/jogada.h"
#include "../include/insert.h"
#include "../include/vitoria.h"
#include "../include/utils.h"

#define TOTAL_MAXIMO_PECAS 30 /* Fim de partida por limite de turnos/pecas */

/*
 * Solicita e lê, de forma validada, a próxima jogada do jogador
 * atual. Repete a solicitação enquanto a entrada não for válida
 * segundo converteCoordenada + validaJogada.
 *
 * Parâmetros:
 *   tabuleiro      - tabuleiro atual (somente leitura).
 *   jogadorAtual   - símbolo do jogador da vez ('X' ou 'O').
 *   haRestricao    - 1 se há uma direção imposta pela jogada anterior.
 *   direcaoImposta - direção imposta (válida apenas se haRestricao==1).
 *   linha, coluna  - ponteiros onde a posição escolhida será gravada.
 *
 * Retorno:
 *   1 se uma jogada válida foi lida; 0 se a entrada terminou (EOF)
 *   antes que uma jogada válida fosse fornecida.
 */
static int leJogadaValida(const Tabuleiro *tabuleiro, char jogadorAtual,
                           int haRestricao, TipoMovimento direcaoImposta,
                           int *linha, int *coluna) {
    char entrada[TAM_MAX_ENTRADA];

    while (1) {
        printf("Jogador %c, digite a coordenada (ex.: A1): ", jogadorAtual);

        if (!lerLinha(entrada, TAM_MAX_ENTRADA)) {
            printf("\nEntrada encerrada.\n");
            return 0;
        }

        if (!converteCoordenada(entrada, linha, coluna, tabuleiro->linhas, tabuleiro->colunas)) {
            printf("Formato invalido ou fora do tabuleiro. Use o formato LetraNumero (ex.: A1).\n");
            continue;
        }

        if (!validaJogada(tabuleiro, *linha, *coluna, haRestricao, direcaoImposta)) {
            printf("Jogada invalida: a casa esta ocupada ou nao respeita a direcao imposta.\n");
            continue;
        }

        return 1;
    }
}

/*
 * Exibe o resultado final da partida quando o encerramento ocorre
 * pelo limite de peças (30 no tabuleiro), comparando a maior
 * região ortogonalmente conectada de cada jogador.
 */
static void exibeResultadoPorRegiao(const Tabuleiro *tabuleiro) {
    int regiaoX = contaMaiorRegiao(tabuleiro, 'X');
    int regiaoO = contaMaiorRegiao(tabuleiro, 'O');

    printf("\nLimite de %d pecas no tabuleiro atingido!\n", TOTAL_MAXIMO_PECAS);
    printf("Maior regiao conectada -> X: %d | O: %d\n", regiaoX, regiaoO);

    if (regiaoX > regiaoO) {
        printf("Jogador X venceu pela maior regiao conectada!\n");
    } else if (regiaoO > regiaoX) {
        printf("Jogador O venceu pela maior regiao conectada!\n");
    } else {
        printf("Empate! As duas maiores regioes tem o mesmo tamanho.\n");
    }
}

int main(void) {
    Tabuleiro tabuleiro;

    inicializaSeedAleatoria();
    inicializaTabuleiro(&tabuleiro);

    char jogadorAtual = 'X';
    int haRestricao = 0;                       /* primeira jogada: sem restricao */
    TipoMovimento direcaoImposta = HORIZONTAL;  /* valor inicial ignorado (haRestricao == 0) */
    int turno = 1;

    printf("=== DONUTS (INSERT) - MC0004 UFCA ===\n");
    printf("Jogador X sempre comeca. Boa sorte!\n");

    while (1) {
        exibeTabuleiro(&tabuleiro);

        printf("\n--- Turno %d ---\n", turno);
        if (haRestricao) {
            printf("Direcao imposta pela jogada anterior: %s\n", nomeTipoMovimento(direcaoImposta));
        } else {
            printf("Primeira jogada da partida: sem restricao de direcao.\n");
        }

        int linha, coluna;
        if (!leJogadaValida(&tabuleiro, jogadorAtual, haRestricao, direcaoImposta, &linha, &coluna)) {
            printf("Partida encerrada antes do fim (entrada finalizada).\n");
            break;
        }

        insereJogada(&tabuleiro, linha, coluna, jogadorAtual);

        int pecasViradas = fazInsert(&tabuleiro, linha, coluna, jogadorAtual);
        if (pecasViradas > 0) {
            printf("Insert! %d peca(s) do oponente foram viradas para %c.\n",
                   pecasViradas, jogadorAtual);
        }

        /* Verifica vitoria por 5+ pecas em linha */
        if (verificaVitoria(&tabuleiro, jogadorAtual)) {
            exibeTabuleiro(&tabuleiro);
            printf("\nParabens! Jogador %c venceu formando 5 ou mais pecas em linha!\n", jogadorAtual);
            break;
        }

        /* Verifica fim de partida por limite de pecas no tabuleiro */
        if (contaTotalPecas(&tabuleiro) >= TOTAL_MAXIMO_PECAS) {
            exibeResultadoPorRegiao(&tabuleiro);
            break;
        }

        /* Prepara a proxima rodada: a direcao imposta ao adversario
           e o tipo de movimentacao da casa que acabou de ser jogada */
        direcaoImposta = tabuleiro.casas[linha][coluna].tipo;
        haRestricao = 1;

        jogadorAtual = (jogadorAtual == 'X') ? 'O' : 'X';
        turno++;
    }

    return 0;
}
