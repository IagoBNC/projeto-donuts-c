/*
* tabuleiro.h
 * ------------------------------------------------------
 * Responsabilidade: Definir a estrutura de dados do tabuleiro
 * do jogo DONUTS (6x6), os tipos de movimentação de cada casa
 * (Horizontal, Vertical, Diagonal Principal, Diagonal Secundária)
 * e as funções de criação/inicialização do tabuleiro.
 * ------------------------------------------------------
 */

#ifndef TABULEIRO_H
#define TABULEIRO_H

#define TAM_TABULEIRO 6 // Tabuleiro sempre (6x6)
#define CASA_VAZIA '.'  // Caractere que representa uma casa vazia
#define QTD_TIPOS 4 // Quantidade de tipos de movimentação distintos

/*
 * Enum que representa os 4 tipos de movimentação possíveis
 * em uma casa do tabuleiro. Cada tipo indica a direção que o
 * PRÓXIMO jogador é obrigado a seguir ao jogar.
 */
typedef enum {
    HORIZONTAL,
    VERTICAL,
    DIAGONAL_PRINCIPAL,   /* Diagonal no sentido \ (canto sup. esq. -> inf. dir.) */
    DIAGONAL_SECUNDARIA   /* Diagonal no sentido / (canto sup. dir. -> inf. esq.) */
} TipoMovimento;

/*
 * Struct que representa uma única casa do tabuleiro.
 * - ocupante: caractere do jogador que ocupa a casa ('X', 'O')
 *             ou CASA_VAZIA se estiver livre.
 * - tipo: tipo de movimentação (direção) associada a essa casa,
 *         definida na preparação do tabuleiro.
 */
typedef struct {
    char ocupante;
    TipoMovimento tipo;
} Casa;

/*
 * Struct que representa o tabuleiro completo do jogo.
 * - casas: matriz 6x6 de Casa.
 * - linhas / colunas: dimensões do tabuleiro (fixas em 6, mas
 *   mantidas explícitas para flexibilidade e clareza no código).
 */
typedef struct {
    Casa casas[TAM_TABULEIRO][TAM_TABULEIRO];
    int linhas;
    int colunas;
} Tabuleiro;

/*
 * Inicializa o tabuleiro:
 *  - Define linhas/colunas como TAM_TABULEIRO.
 *  - Marca todas as casas como vazias (CASA_VAZIA).
 *  - Distribui aleatoriamente os 4 tipos de movimentação pelas
 *    36 casas, garantindo exatamente 9 casas de cada tipo
 *    (36 casas / 4 tipos = 9 cada).
 * Parâmetros:
 *   tabuleiro - ponteiro para a struct Tabuleiro a ser inicializada.
 */
void inicializaTabuleiro(Tabuleiro *tabuleiro);

/*
 * Exibe o tabuleiro completo na tela, formatado com:
 *  - Colunas identificadas por números (1 a 6) no topo.
 *  - Linhas identificadas por letras (A a F) à esquerda.
 *  - Cada casa mostra o ocupante ('X' ou 'O') caso esteja
 *    ocupada, ou uma letra indicando o tipo de movimentação
 *    (H, V, P, S) caso esteja vazia.
 * Uma legenda dos símbolos é impressa logo abaixo do tabuleiro.
 * Parâmetros:
 *   tabuleiro - ponteiro constante para o Tabuleiro a ser exibido
 *               (const pois a função apenas lê os dados).
 */
void exibeTabuleiro(const Tabuleiro *tabuleiro);

/*
 * Conta o número total de casas ocupadas (peças) no tabuleiro,
 * usado para verificar a condição de fim de partida por limite
 * de turnos (30 peças).
 * Parâmetros:
 *   tabuleiro - ponteiro constante para o tabuleiro.
 * Retorno: quantidade total de peças no tabuleiro.
 */
int contaTotalPecas(const Tabuleiro *tabuleiro);

/*
 * Retorna o nome (em português) de um TipoMovimento, usado para
 * exibir mensagens amigáveis ao jogador (ex.: "Direcao imposta: Vertical").
 */
const char *nomeTipoMovimento(TipoMovimento tipo);

#endif /* TABULEIRO_H */

