#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
}Node;

typedef struct stack{
    struct node *beg; // Campo para o começo da pilha
}Stack;

Stack *create_stack() { // Aloca espaço para a pilha e seta o começo como NULL
    Stack *st = malloc(sizeof(Stack));
    st->beg = NULL;
    return st;
}

void push(Stack *ref_st, int v) {
    Node *newNode = malloc(sizeof(Node));
    newNode->value = v;

    if (ref_st->beg == NULL) { // Pilha vazia

        ref_st->beg = newNode; // Começo da pilha aponta para o novo nó
        newNode->next = NULL;

    } else { // Se a pilha não estiver vazia

        newNode->next = ref_st->beg;
        ref_st->beg = newNode;

    }
}

void pop(Stack *ref_st) {

    if (ref_st->beg != NULL) { // Se a pilha não estiver vazia
        Node *p = ref_st->beg; // Armazenando o nó apontado pelo começo da pilha
        ref_st->beg = p->next;
        free(p);
    }

}

int main () {

    Stack *pilha = create_stack();

    for (int i = 0; i < 10; i++) {
        push(pilha, i);
    }

    for (int i = 0; i < 10; i++) {
        pop(pilha);
    }

    free(pilha);

    return 0;
}
