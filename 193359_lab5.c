#include <stdio.h>
#include <stdlib.h>

typedef struct Operacao {
    char tipo;
    char caractere;
    int posicao;
    struct Operacao *prox;
} Operacao;

Operacao *cria_pilha() {
    Operacao *op = malloc(sizeof(Operacao));
    op->prox = NULL;
    op->posicao = 0;
    return op;
}

void push(Operacao *ref_op, char tipo, char caractere) {

    Operacao *novaOp = malloc(sizeof(Operacao));
    novaOp->tipo = tipo;
    novaOp->caractere = caractere;

    if (ref_op->prox == NULL) { // Pilha vazia
        ref_op->prox = novaOp;
        novaOp->prox = NULL;
        novaOp->posicao++;
    } else { // Pilha não está vazia
        novaOp->prox = ref_op->prox;
        ref_op->prox = novaOp;
        novaOp->posicao++;
    }

}

int main() {


    return 0;
}
