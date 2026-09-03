#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int info;
    struct no *prox;
} No;

typedef struct cx {
    No **caixa; // Tipo No pq cada caixa vai receber o endereço de um nó.
    int N;
} Caixa;

No *inicializa() {
    return NULL;
}

Caixa **aloca_caixas(int N) {
    Caixa **caixas = malloc(sizeof(No*) * N); // Reservando espaço para armazenar ponteiros q apontam para um nó

    for (int i = 0; i < N; i++) {
        caixas[i] = inicializa(); // Inicializando as listas encadeadas
    }

    return caixas;
}

int h (int k, int n) {
    return k % n;
}

int main() {
    No *cabeca = inicializa();

    return 0;
}
