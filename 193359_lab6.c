
#include <stdio.h>
#include <stdlib.h>

// TAD ===================================================================================

typedef struct tarefa Tarefa;
typedef struct fila Fila;

// Cria e retorna uma fila vazia
Fila *inicializa_fila();

// Adiciona uma tarefa na fila respeitando a prioridade ('U' antes de 'N')
void adiciona_tarefa(Fila *fila, int id, int n_pag, char prioridade);

// Remove a primeira tarefa da fila e imprime seus dados
void processa_tarefa(Fila *fila);

// Remove a tarefa com o id informado e imprime seus dados
void cancela_tarefa(Fila *fila, int id);

// Exibe as tarefas: ordem 0 = normal, ordem 1 = reversa
void exibir_tarefas(Fila *fila, int ordem);

// Libera toda a memória alocada pela fila
void libera_fila(Fila *fila);

// Funções auxiliares internas do TAD
void insere_urgente(Fila *fila, int id, int n_pag, char prioridade);
void insere_normal(Fila *fila, int id, int n_pag, char prioridade);

// Implementação ==========================================================================

struct tarefa {
    int id;
    int nPag;
    char prioridade;
    struct tarefa *prox;
    struct tarefa *ant;
};

struct fila {
    Tarefa *ini;
    Tarefa *fim;
};

Fila *inicializa_fila() {

    Fila *fila = malloc(sizeof(Fila));
    fila->fim = NULL;
    fila->ini = NULL;

    return fila;

}

void insere_urgente(Fila *fila, int id, int n_pag, char prioridade) {

    Tarefa *tarefa = malloc(sizeof(Tarefa));
    tarefa->id = id;
    tarefa->nPag = n_pag;
    tarefa->prioridade = prioridade;

    Tarefa *aux = fila->ini;

    // Percorre a fila até encontrar a primeira tarefa normal
    while (aux != NULL && aux->prioridade == 'U') {
        aux = aux->prox;
    }

    if (aux == NULL) {
        // Caso todas as tarefas existentes sejam urgentes, inserir no final
        tarefa->ant = fila->fim;
        tarefa->prox = NULL;
        fila->fim->prox = tarefa;
        fila->fim = tarefa;
    } else {
        // Já existem tarefas urgentes na fila
        tarefa->prox = aux;
        tarefa->ant = aux->ant;

        if (aux->ant != NULL) {
            aux->ant->prox = tarefa;
        } else {
            fila->ini = tarefa;
        }

        aux->ant = tarefa;
    }

}

void insere_normal(Fila *fila, int id, int n_pag, char prioridade) {

    Tarefa *tarefa = malloc(sizeof(Tarefa));
    tarefa->id = id;
    tarefa->nPag = n_pag;
    tarefa->prioridade = prioridade;

    tarefa->ant = fila->fim;
    tarefa->prox = NULL;
    fila->fim->prox = tarefa;
    fila->fim = tarefa;

}

void adiciona_tarefa(Fila *fila, int id, int n_pag, char prioridade) {

    if (fila->fim == NULL) { // Fila ta vazia

        Tarefa *tarefa = malloc(sizeof(Tarefa));
        tarefa->id = id;
        tarefa->nPag = n_pag;
        tarefa->prioridade = prioridade;

        fila->ini = tarefa;
        fila->fim = tarefa;
        tarefa->prox = NULL;
        tarefa->ant = NULL;

    } else {

        if (prioridade == 'N') {
            insere_normal(fila, id, n_pag, prioridade);
        } else {
            insere_urgente(fila, id, n_pag, prioridade);
        }

    }
}

void processa_tarefa(Fila *fila) {

    if (fila->fim != NULL) { // Fila não ta vazia

        Tarefa *aux = fila->ini;

        if (fila->ini == fila->fim) { // fila com 1 elemento
            fila->ini = NULL;
            fila->fim = NULL;
        } else {
            aux->prox->ant = NULL;
            fila->ini = aux->prox;
        }

        printf("%d %d %c\n", aux->id, aux->nPag, aux->prioridade);

        free(aux);

    } else {
        printf("\n");
    }

}

void cancela_tarefa(Fila *fila, int id) {

    if (fila->fim == NULL) { // Fila vazia
        printf("\n");
        return;
    }

    Tarefa *aux;

    for (aux = fila->ini; aux != NULL && aux->id != id; aux = aux->prox);

    if (aux == NULL) { // ID não encontrado
        printf("\n");
        return;
    }

    // unico elemento
    if (fila->ini == fila->fim) {
        fila->ini = NULL;
        fila->fim = NULL;
    }
    // primeiro elemento
    else if (aux == fila->ini) {
        fila->ini = aux->prox;
        fila->ini->ant = NULL;
    }
    // ultimo elemento
    else if (aux == fila->fim) {
        fila->fim = aux->ant;
        fila->fim->prox = NULL;
    }

    else {
        aux->ant->prox = aux->prox;
        aux->prox->ant = aux->ant;
    }

    printf("%d %d %c\n", aux->id, aux->nPag, aux->prioridade);

    free(aux);
}

void exibir_tarefas(Fila *fila, int ordem) {

    if (fila->ini == NULL) {
        printf("\n");
        return;
    }

    if (ordem == 0) { // Ordem normal

        Tarefa *aux = fila->ini;

        while (aux != NULL) {
            printf("%d %d %c\n", aux->id, aux->nPag, aux->prioridade);
            aux = aux->prox;
        }

    } else if (ordem == 1) {

        Tarefa *aux = fila->fim;

        while (aux != NULL) {
            printf("%d %d %c\n", aux->id, aux->nPag, aux->prioridade);
            aux = aux->ant;
        }

    } else {
        printf("\n");
    }

}

void libera_fila(Fila *fila) {

    Tarefa *aux = fila->ini;
    Tarefa *proxima;

    while (aux != NULL) {
        proxima = aux->prox;
        free(aux);
        aux = proxima;
    }

    free(fila);

}

int main() {

    Fila *fila = inicializa_fila();

    int nOperacoes;

    scanf("%d", &nOperacoes);

    for (int i = 0; i < nOperacoes; i++) {

        char operacao;

        scanf(" %c", &operacao);

        if (operacao == 'A') {

            int id;
            int nPag;
            char prioridade;

            scanf("%d %d %c", &id, &nPag, &prioridade);

            adiciona_tarefa(fila, id, nPag, prioridade);

        } else if (operacao == 'P') {

            processa_tarefa(fila);

        } else if (operacao == 'C') {

            int id;

            scanf("%d", &id);

            cancela_tarefa(fila, id);

        } else if (operacao == 'E') {

            int ordem;

            scanf("%d", &ordem);

            exibir_tarefas(fila, ordem);

        }

    }

    libera_fila(fila);

    return 0;
}
