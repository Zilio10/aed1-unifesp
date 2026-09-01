#include <stdio.h>
#include <stdlib.h>

float* alocar_vetor(int N) {

    float *ptr = malloc(sizeof(float) * N);

    return ptr;

}

float calcular_media(float *vetor, int N) {

    float soma = 0;

    for (int i = 0; i < N; i++) {
        soma += vetor[i];
    }

    return soma/N;

}

int main() {

    int N;

    scanf("%d", &N);
    float *vetor = alocar_vetor(N);

    for (int i = 0; i < N; i++) {
        scanf("%f", &vetor[i]); // &vetor[i] == vetor + i, que contém o endereço de memória do valor reservado por malloc
    }

    float media = calcular_media(vetor, N);
    printf("Media: %.2f\n", media);

    free(vetor);

}
