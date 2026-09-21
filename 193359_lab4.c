#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int simbolo;
    struct No *prox;
    struct No *ant;
}No;

typedef struct Tambor {
    No *cabeca;
}Tambor;

typedef struct Maquina {
    int n_tambores;
    Tambor *tambores;
}Maquina;

Maquina *cria_maquina(int n_tambores) {

    Maquina *ref_maquina = malloc(sizeof(Maquina)); // Referência da máquina
    ref_maquina->n_tambores = n_tambores;

    ref_maquina->tambores = malloc(n_tambores * sizeof(Tambor)); // Alocando memória para n tambores

    for (int i = 0; i < n_tambores; i++) {
        ref_maquina->tambores[i].cabeca = NULL; // Em cada tambor (1 reel) inicializo a cabeça da lista encadeada
    }

    return ref_maquina;

}

void insere_simbolo(Tambor *ref_tambor, int simbolo) {

    No *cabeca = ref_tambor->cabeca;

    No *novoNo = malloc(sizeof(No));
    novoNo->simbolo = simbolo;
    if (cabeca == NULL) { // Lista vazia

        novoNo->prox = novoNo;
        novoNo->ant = novoNo;
        ref_tambor->cabeca = novoNo;

    } else { // Lista não está vazia

        novoNo->prox = cabeca->prox;
        novoNo->ant = cabeca;
        novoNo->prox->ant = novoNo;
        cabeca->prox = novoNo;

    }

}

void remove_simbolo(Tambor *ref_tambor, int simbolo) {

    if (ref_tambor->cabeca != NULL) {

        if (ref_tambor->cabeca->prox == ref_tambor->cabeca && ref_tambor->cabeca->simbolo == simbolo) { // Se a remoção ocorrer em uma lista de 1 nó
            free(ref_tambor->cabeca);
            ref_tambor->cabeca = NULL;
        } else {

            No *p;
            for (p = ref_tambor->cabeca->prox; p != ref_tambor->cabeca && p->simbolo != simbolo; p = p->prox); // Percorrendo a lista

            if (p->simbolo == simbolo) { // Se o símbolo foi encontrado

            p->ant->prox = p->prox;
            p->prox->ant = p->ant;

            if (p == ref_tambor->cabeca) ref_tambor->cabeca = p->ant; // Desolocando a cabeca no caso de sua remoção

            free(p);

            }
        }
    }
}

void desaloca_tambor(Tambor *ref_tambor) {

    if (ref_tambor->cabeca != NULL) {

        No *p = ref_tambor->cabeca->prox;
        while (p != ref_tambor->cabeca) {
            No *prox = p->prox;
            free(p);
            p = prox;
        }

        free(ref_tambor->cabeca);

    }
}

void desaloca_caixas(Maquina *ref_maquina) {

    for (int i = 0; i < ref_maquina->n_tambores; i++) desaloca_tambor(&ref_maquina->tambores[i]); // Desalocando as listas de símbolos de cada tambor

    free(ref_maquina->tambores); // Desalocando o vetor de tambores
    free(ref_maquina); // Desalocando máquina

}

void escolhe_simbolos(Maquina *ref_maq, int n_rotacoes[], int sentido[], int simbolo_escolhido[], int n) {

    for (int i = 0; i < n; i++) {
        No *p = ref_maq->tambores[i].cabeca;

        if (sentido[i] == 0) {
            int j = 0;
            while (j < n_rotacoes[i]) {
                p = p->ant;
                j++;
            }
        } else if (sentido[i] == 1) {
            int j = 0;
            while(j < n_rotacoes[i]) {
                p = p->prox;
                j++;
            }
        }
        simbolo_escolhido[i] = p->simbolo;

    }
}

int main () {
    int n;
    scanf("%d", &n); // Lendo o num de tambores da máquina
    Maquina *ref_maq = cria_maquina(n);

    int m;
    scanf("%d", &m); // Lendo o número de símbolos de cada tambor

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int simbolo;
            scanf("%d", &simbolo);
            insere_simbolo(&ref_maq->tambores[i], simbolo); // Inserindo os simbolos nos seus respectivos tambores
        }
    }

    int n_rotacoes[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &n_rotacoes[i]); // Rotação de cada tambor
    }

    int sentido[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &sentido[i]); // Sentido da rotação de cada tambor
    }

    int simbolo_escolhido[n];
    escolhe_simbolos(ref_maq, n_rotacoes, sentido, simbolo_escolhido, n);


    for (int i = 0; i < n; i++) {
        int simbolo;
        scanf("%d", &simbolo);
        remove_simbolo(&ref_maq->tambores[i], simbolo); // Removendo 1 símbolo de cada tambor (se existir)
    }
    int simbolo_escolhido_remocao[n];
    escolhe_simbolos(ref_maq, n_rotacoes, sentido, simbolo_escolhido_remocao, n);


    printf("-");
    for (int i = 0; i < n; i++) {
        printf("%d-", simbolo_escolhido[i]);
    }

    printf("\n");

    printf("-");
    for (int i = 0; i < n; i++) {
        printf("%d-", simbolo_escolhido_remocao[i]);
    }

    desaloca_caixas(ref_maq);
}

