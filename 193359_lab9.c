#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int info;
    struct No *esq;
    struct No *dir;
} No;

typedef struct node { // Nó auxiliar da pilha
    No *value;
    struct node *next;
} Node;

typedef struct stack {
    Node *beg;
} Stack;

typedef struct queue {
    Node *ini;
    Node *fim;
} Queue;

Stack *create_stack() {

    Stack *st = malloc(sizeof(Stack));

    if (st == NULL)
        return NULL;

    st->beg = NULL;

    return st;
}

int empty(Stack *ref_st) {
    return ref_st->beg == NULL;
}

No *pop(Stack *ref_st) {

    if (empty(ref_st))
        return NULL;

    Node *p = ref_st->beg;
    No *atual = p->value;

    ref_st->beg = p->next;
    free(p);

    return atual;
}

void push(Stack *ref_st, No *v) {

    Node *newNode = malloc(sizeof(Node));

    if (newNode == NULL)
        return;

    newNode->value = v;
    newNode->next = ref_st->beg;

    ref_st->beg = newNode;
}

void free_stack(Stack *ref_st) {

    while (!empty(ref_st))
        pop(ref_st);

    free(ref_st);
}

Queue *create_queue() {

    Queue *q = malloc(sizeof(Queue));

    if (q == NULL)
        return NULL;

    q->ini = NULL;
    q->fim = NULL;

    return q;
}

int empty_queue(Queue *q) {
    return q->ini == NULL;
}

void inserir(No **raiz, int valor) {

    if (*raiz == NULL) { // Condição de parada
        No *folha = malloc(sizeof(No));
        folha->info = valor;
        folha->esq = NULL;
        folha->dir = NULL;

        *raiz = folha;
        return;
    }

    if (valor < (*raiz)->info) {

        inserir(&(*raiz)->esq, valor);

    } else if (valor > (*raiz)->info) {

        inserir(&(*raiz)->dir, valor);

    }

}

void enqueue(Queue *q, No *v) {

    Node *newNode = malloc(sizeof(Node));

    if (newNode == NULL)
        return;

    newNode->value = v;
    newNode->next = NULL;

    if (empty_queue(q)) {
        q->ini = newNode;
        q->fim = newNode;
    } else {
        q->fim->next = newNode;
        q->fim = newNode;
    }
}

No *dequeue(Queue *q) {

    if (empty_queue(q))
        return NULL;

    Node *p = q->ini;
    No *atual = p->value;

    q->ini = p->next;

    if (q->ini == NULL)
        q->fim = NULL;

    free(p);

    return atual;
}

void free_queue(Queue *q) {

    while (!empty_queue(q))
        dequeue(q);

    free(q);
}

void preorder(No *raiz) {

    if (raiz == NULL)
        return;

    printf("%d", raiz->info);
    preorder(raiz->esq);
    preorder(raiz->dir);

}

void inorder(No *raiz) {

    if (raiz == NULL)
        return;

    inorder(raiz->esq);
    printf("%d", raiz->info);
    inorder(raiz->dir);

}

void postorder(No *raiz) {

    if (raiz == NULL)
        return;

    Stack *p1 = create_stack();
    Stack *p2 = create_stack();

    push(p1, raiz);

    while(!empty(p1)) {

        No *atual = pop(p1);

        push(p2, atual);

        if (atual->esq != NULL)
            push(p1, atual->esq);

        if (atual->dir != NULL)
            push(p1, atual->dir);

    }

    while(!empty(p2)) {
        No *atual = pop(p2);
        printf("%d", atual->info);
    }

    free_stack(p1);
    free_stack(p2);
}

void levelOrder(No *raiz) {

    if (raiz == NULL)
        return;

    Queue *q = create_queue();

    enqueue(q, raiz);

    while(!empty_queue(q)) {

        No *atual = dequeue(q);

        printf("%d", atual->info);

        if (atual->esq != NULL)
            enqueue(q, atual->esq);

        if (atual->dir != NULL)
            enqueue(q, atual->dir);
    }

    free_queue(q);

}

int main() {

    No *raiz = NULL;

    return 0;
}
