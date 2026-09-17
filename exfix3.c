#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int info;
    struct No *prox;
} No;

No *inicializa() {
    return NULL;
}

No *insere_comeco(No *cabeca, int valor) {

    No *novoNo = malloc(sizeof(No));
    novoNo->info = valor;

    if (cabeca == NULL) { // Lista vazia
        novoNo->prox = novoNo; // novoNo aponta para ele mesmo
        cabeca = novoNo; // cabeca passa a ser o novoNo
        return cabeca;

    } else { // Lista não está vazia
        novoNo->prox = cabeca->prox;
        cabeca->prox = novoNo;
    }

    return cabeca;

}

No *buscar_elemento(No *cabeca, int elemento) {

    if (cabeca == NULL) { // Lista vazia
        return NULL;
    } else { // Lista não está vazia

        No *p;
        for (p = cabeca->prox; p->info != elemento && p != cabeca; p = p->prox)  // Percorrendo lista

        if (p == cabeca && p->info != elemento) { // Lista foi percorrida e o elemento não foi encontrado
            return NULL;
        }

        if (p->info == elemento) { // Elemento encontrado
            return p;
        }
    }

    return NULL;
}

No *remover_no(No *cabeca, int elemento) {

}

int main () {

    No *cabeca = inicializa();

    cabeca = insere_comeco(cabeca, 3);

    No* noEncontrado = buscar_elemento(cabeca, 3);

    return 0;
}
