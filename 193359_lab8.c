#include <stdio.h>

void buscaElementos(int x, int n, int A[], int ini, int fim) {

    if (ini > fim) { // Condição de parada
        printf("nao ha intervalo valido");
        return; // recursividade para
    }

    int meio = (ini + fim) /2;

    if (meio + 1 >= n) { // Condição de parada
        printf("nao ha intervalo valido");
        return; // recursividade para
    }

    if (A[meio] < x && A[meio + 1] > x) { // Condição de parada, intervalo foi encontrado
        printf("%d %d", A[meio], A[meio + 1]);
        return;
    }

    if (x < A[meio]) {
        buscaElementos(x, n, A, ini, meio - 1); // A busca anda para a esquerda do vetor (fim anda)
    } else {
        buscaElementos(x, n, A, meio + 1, fim); // A busca anda para a direita do vetor (ini anda)
    }

}

int main() {

    int x, n;
    scanf("%d %d", &x, &n);

    int A[n], i;
    for(i = 0; i < n; i++)  {
        scanf("%d", &A[i]);
    }

    buscaElementos(x, n, A, 0, n-1);

    return 0;
}
