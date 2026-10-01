#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int valor;
    struct no *prox;
}No;

typedef struct fila{
    No *ini;
    No *fim;
}Fila;

Fila *inicializa(void) {
    Fila *fila = malloc(sizeof(Fila));
    fila->fim = NULL;
    fila->ini = NULL;
    return fila;
}

void enqueue(Fila *fila, int valor) {

    No *novoNo = malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->prox = NULL; // O novo nó passa a ser o elemento do final da fila

    if (fila->fim != NULL) { // Se a fila nao estiver vazia...
        fila->fim->prox = novoNo; // O último elemento da fila aponta para o novo nó
    } else { // Fila vazia
        fila->ini = novoNo; // Como a fila estava vazia, o novoNo tbm é o início da fila
    }

    fila->fim = novoNo; // Em todos os casos, o novoNo é o último elemento da fila

}

int dequeue(Fila *fila) {

    if (fila->fim != NULL){ // Se a fila não estiver vazia
        No *p = fila->ini;
        int valor = p->valor;

        fila->ini = p->prox; // O elemento do início passa a ser o próximo

        if (fila->ini == NULL) { // Se após a fila andar, a fila ficou vazia...
            fila->fim = NULL; // O fim também aponta para nulo
        }

        free(p);

        return valor;
    }

    return -1;

}

void libera_fila(Fila *fila) {

    No *p = fila->ini;
    while (p != NULL) {
        No *q = p->prox;
        free(p);
        p = q;
    }

    free(fila);

}

int main () {

    Fila *fila = inicializa();

    for(int i = 0; i < 10; i++) enqueue(fila, i);
    dequeue(fila);

    libera_fila(fila);

    return 0;
}
