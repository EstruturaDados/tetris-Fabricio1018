#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Capacidade máxima da fila
#define CAPACIDADE 5

// Struct que representa uma peça do Tetris Stack
typedef struct {
    char nome; // Tipo: 'I', 'O', 'T', 'L'
    int id;    // Identificador único
} Peca;

// Struct da fila circular
typedef struct {
    Peca itens[CAPACIDADE];
    int inicio; // Índice do primeiro elemento
    int fim;    // Índice onde o próximo elemento será inserido
    int tamanho;
} Fila;


// ---------- Protótipos ----------
void inicializarFila(Fila *f);
int filaCheia(Fila *f);
int filaVazia(Fila *f);
Peca gerarPeca();
void enqueue(Fila *f, Peca nova);
Peca dequeue(Fila *f);
void exibirFila(Fila *f);


// ---------- Função principal ----------
int main() {
    Fila fila;
    inicializarFila(&fila);

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));
    
    // Preenche a fila com 5 peças iniciais
    for (int i = 0; i < CAPACIDADE; i++) {
        enqueue(&fila, gerarPeca());
    }

    int opcao;

    do {
        printf("\n===============================\n");
        printf("     Fila de Pecas Futuras\n");
        printf("===============================\n");
        exibirFila(&fila);

        printf("\nOpcoes:\n");
        printf("1 - Jogar peca\n");
        printf("2 - Inserir nova peca\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (!filaVazia(&fila)) {
                    Peca removida = dequeue(&fila);
                    printf("\nPeca jogada: [%c %d]\n", removida.nome, removida.id);
                } else {
                    printf("\nA fila esta vazia!\n");
                }
                break;

            case 2:
                if (!filaCheia(&fila)) {
                    Peca nova = gerarPeca();
                    enqueue(&fila, nova);
                    printf("\nNova peca inserida: [%c %d]\n", nova.nome, nova.id);
                } else {
                    printf("\nA fila esta cheia! Nao e possivel inserir nova peca.\n");
                }
                break;

            case 0:
                printf("\nSaindo...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}


// ---------- Implementações ----------

// Inicializa a fila vazia
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->tamanho == CAPACIDADE;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->tamanho == 0;
}

// Gera uma nova peça automaticamente
Peca gerarPeca() {
    static int contadorID = 0;
    char tipos[] = {'I', 'O', 'T', 'L'};
    int indice = rand() % 4;

    Peca p;
    p.nome = tipos[indice];
    p.id = contadorID++;
    return p;
}

// Insere peça no final da fila
void enqueue(Fila *f, Peca nova) {
    if (filaCheia(f)) return;

    f->itens[f->fim] = nova;
    f->fim = (f->fim + 1) % CAPACIDADE;
    f->tamanho++;
}

// Remove peça do início da fila
Peca dequeue(Fila *f) {
    Peca removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % CAPACIDADE;
    f->tamanho--;
    return removida;
}

// Exibe a fila
void exibirFila(Fila *f) {
    printf("\nFila de Pecas:\n");
    if (filaVazia(f)) {
        printf("[vazia]\n");
        return;
    }
    
    int i = f->inicio;
    for (int c = 0; c < f->tamanho; c++) {
        printf("[%c %d] ", f->itens[i].nome, f->itens[i].id);
        i = (i + 1) % CAPACIDADE;
    }
    printf("\n");
}
