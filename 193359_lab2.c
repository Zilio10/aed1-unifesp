#include <stdio.h>
#include <stdlib.h>

int **alocar_matriz(int M, int N) {

    int **matriz = malloc(sizeof(int*) * M);

    for(int i = 0; i < M; i++) {
        matriz[i] = malloc(sizeof(int)* N);
    }

    return matriz;
}

int **transpor_matriz(int **matrizOrigem, int M, int N) {

    int **matrizT = alocar_matriz(N, M);
    for(int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matrizT[i][j] = matrizOrigem[j][i];
        }
    }

    return matrizT;
}

void imprimir_matriz(int **matrizT, int N, int M) {

     for(int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", matrizT[i][j]);
        }
        printf("\n");
     }

}

void liberar_matriz(int **matriz, int M) {

    for (int i = 0; i < M; i++) {
        free(matriz[i]);
    }

    free(matriz);

}

int main() {

    int M, N;
    scanf("%d %d", &M, &N);

    int **matriz = alocar_matriz(M, N);
    for(int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){
           scanf("%d", &matriz[i][j]);
        }
    }

    int **matrizT = transpor_matriz(matriz, M, N);
    imprimir_matriz(matrizT, N, M);

    liberar_matriz(matriz, M);
    liberar_matriz(matrizT, N);

    return 0;
}
