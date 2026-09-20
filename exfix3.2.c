#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int info;
    struct No *prox;
    struct No *ant;
} No;

No *inicializa() {
    return NULL;
}

No *insere_comeco(No *cabeca, int valor) {

    No *novoNo = malloc(sizeof(No));
    novoNo->info = valor;

    if (cabeca == NULL) { // Lista vazia
        novoNo->prox = novoNo; // novoNo aponta para ele mesmo
        novoNo->ant = novoNo;
        cabeca = novoNo; // cabeca passa a ser o novoNo
        return cabeca;

    } else { // Lista não está vazia
        novoNo->prox = cabeca->prox;
        novoNo->ant = cabeca;
        cabeca->prox = novoNo;
        novoNo->prox->ant = novoNo; // O novoNo aponta para o segundo elemento da lista, o anterior do segundo No aponta agora p o novoNo (primeiro no da lista)
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

    if (cabeca == NULL) { // Lista vazia, nenhum elemento removido
        return cabeca;
    }

    if (cabeca->prox == cabeca && cabeca->info == elemento) { // Lista tem apenas 1 elemento
        free(cabeca);
        cabeca = NULL;
        return cabeca;
    }

    No *p;
    for(p = cabeca->prox; p != cabeca && p->info != elemento; p = p->prox)

    if (p->info != elemento) return cabeca; // Se o elemento não foi encontrado

    p->ant->prox = p->prox;
    p->prox->ant = p->ant;
    if (p == cabeca) cabeca = p->ant; // Se o elemento estiver na cabeca, movemos a cabeca
    free(p);

    return cabeca;
}

int main () {

    No *cabeca = inicializa();

    cabeca = insere_comeco(cabeca, 3);

    No* noEncontrado = buscar_elemento(cabeca, 3);

    cabeca = remover_no(cabeca, 3);

    free(noEncontrado);
    free(cabeca);

    return 0;
}
