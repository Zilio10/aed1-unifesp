#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int info;
    struct no *prox;
} No;

typedef struct cx {
    No **caixa; // Tipo No pq cada caixa vai receber o endereço de um nó.
    int N; // num de caixas (informado pelo usuário)
} Caixa;

No *inicializa() { // Retorna um ponteiro para No que nao aponta para nada - cabeça da lista
    return NULL;
}

Caixa *aloca_caixas(int N) {
    Caixa *refCaixa = malloc(sizeof(Caixa)); // Alocando memoria para um struct do tipo Caixa

    refCaixa->caixa = malloc(sizeof(No*) * N); // Dentro do struct, estou alocando memória para N caixas em que refCaixa->caixa conterá um ponteiro para um No
    refCaixa->N = N; // Setando o campo do struct Caixa com a qtd de caixas

    for (int i = 0; i < N; i++) {
        refCaixa->caixa[i] = inicializa(); // Inicializando a lista encadeada com NULL dentro de uma caixa
    }

    return refCaixa; // Retornando a referência de um struct do tipo Caixa
}

void insere(Caixa *refCaixa, int K) {

    int indice = h(K, refCaixa->N); // Obtendo a caixa em que K será inserido

    No *novoNo = malloc(sizeof(No));

    if (novoNo != NULL) {

        if (refCaixa->caixa[indice] == NULL) { // Lista está vazia
            novoNo->prox = NULL; // nó novo é o primeiro e ultimo elemento
            refCaixa->caixa[indice] = novoNo; // cabeça aponta para o novo nó
        } else { // Lista não está vazia
            novoNo->prox = refCaixa->caixa[indice]; // novoNo aponta para onde a head aponta
            refCaixa->caixa[indice] = novoNo; // head aponta para o novo no
        }

        novoNo->info = K; // K é guardado no Nó

    }

}

No *retira(Caixa *refCaixa, int K) { // A função retorna o endereço removido para uma posterior desalocação

    int indice = h(K, refCaixa->N); // Se existir o elemento, ele estará nesta caixa

    if (refCaixa->caixa[indice] == NULL) { // Lista está vazia
        return refCaixa->caixa[indice]; // Reotna o conteúdo nulo da cabeça
    } else { // Lista não está vazia

        No *p = refCaixa->caixa[indice]; // P recebe a cabeça
        if (p->info == K) { // Como a lista nao esta vazia e nao foi percorrido nenhum laço, a condição verifica se o primeiro elemento é = K
            refCaixa->caixa[indice] = p->prox; // a cabeça passa a ser o elemento para qual P aponta, Logo: P foi desencadeadoolha, se
            return p;
        } else { // Lista nao está vazia e não é o priemriro elemento

            No *ant = refCaixa->caixa[indice];
            p = ant->prox;

            while (p != NULL && p->info != K) { // Percorre a lista até o fim ou até encontrar o elemento K
                ant = p; // Preserva o anterior
                p = p->prox; // Incremento
            }

            if (p == NULL) { // Elemento não está na lista
                return NULL;
            } else { // elemento encontrado no meio ou final da lista

                ant->prox = p->prox; // anterior aponta para o próximo, desvinculando o atual (p)
                return p;
            }
        }
    }
}

int h(int K, int N) {
    return K % N;
}

int main() {

    No *cabeca = inicializa();

    return 0;
}
