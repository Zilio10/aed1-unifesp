#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int info;
    struct No *esq;
    struct No *dir;
}No;

void inserir (No **raiz, int valor) {

    if (*raiz == NULL) { // Condição de parada
        No *novo = malloc(sizeof(No));
        novo->info = valor;
        novo->esq = NULL;
        novo->dir = NULL;

        *raiz = novo; // Inserindo o nó na árvore
        return;
    }

    if (valor < (*raiz)->info) {

        inserir(&(*raiz)->esq, valor); // Recursividade - Se é menor vai para a esquerda

    } else if (valor > (*raiz)->info) {

        inserir(&(*raiz)->dir, valor); // Recursividade - Se é maior vai para a direita

    }

}

void preorder(No *raiz) {

    if (raiz == NULL)
        return;

    printf("%d", raiz->info); // Agindo na raiz primeiramente
    preorder(raiz->esq);
    preorder(raiz->dir);

}

void inorder(No *raiz) {

    if (raiz == NULL)
        return;

    preorder(raiz->esq);
    printf("%d", raiz->info);
    preorder(raiz->dir);

}

void postorder(No *raiz) {

    if (raiz == NULL)
        return;

    preorder(raiz->esq);
    preorder(raiz->dir);
    printf("%d", raiz->info);

}

int altura(No *raiz) {

    if (raiz == NULL)
        return -1;

    int altEsq = altura(raiz->esq);
    int altDir = altura(raiz->dir);

    if (altEsq > altDir) {
        return 1 + altEsq;
    } else {
        return 1 + altDir;
    }

} // Retorno vai ser smp do tipo: max(n,n) + 1 => Em que n = retorno(raiz)

int main() {

    No *raiz = NULL; // Inicializando a raíz da árvore

    int v, i;
    for (i = 0; i < 7; i++) {
        scanf("%d", &v);
        inserir(&raiz, v);
    }

    preorder(raiz);
    //inorder(raiz);
    //postorder(raiz);

    int h = altura(raiz);
    printf("%d", altura);

    return 0;
}
