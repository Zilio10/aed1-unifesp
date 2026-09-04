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

int h(int K, int N) {
    return K % N;
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
            refCaixa->caixa[indice] = p->prox; // a cabeça passa a ser o elemento para qual P aponta, Logo: P foi desencadeada
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

void imprime(Caixa *cx) {

    for (int i = 0; i < cx->N; i++) {
        No *p = cx->caixa[i];
        while (p != NULL) {
            printf("%d ", p->info);
            p = p->prox;
        }
        printf("\n");
    }

}

void desaloca_lista(No *cabeca) {

    No* p = cabeca;
    while(p != NULL) { // Enquanto não chegar ao final da lista
        cabeca = p->prox; // cabeca guarda o endereco do nó posterior
        free(p); // nó atual é liberado
        p = cabeca; // nó atual recebe o nó posterior
    }

}

void desaloca_caixas(Caixa *cx) {
    for (int i = 0; i < cx->N; i++) {
        desaloca_lista(cx->caixa[i]); // Desalocando de fato as listas encadeadas
    }

    free(cx->caixa); // Desalocando o vetor de ponteiros
    free(cx); // Desalocando o struct
}

int main() {

    int N , m, K, L;

    scanf("%d", &N); // Num de caixas
    Caixa *refCaixa = aloca_caixas(N); // Alocando caixas

    scanf("%d", &m); // Qtd de inteiros

    for (int i = 0; i < m; i++) {
        scanf("%d", &K);
        insere(refCaixa, K); // inserindo os valores nas caixas
    }

    scanf("%d", &L); // inteiro para ser buscado
    No* resRetira = retira(refCaixa, L); // retirando o elemento L (ou não)
    if (resRetira == NULL) {
        printf("-1");
    } else {
        printf("%d", resRetira->info);
        free(resRetira);
    }
    printf("\n");

    imprime(refCaixa);

    desaloca_caixas(refCaixa);

    return 0;
}
