#include <stdio.h>
#include <stdlib.h>

int palindromo(char palavra[], int inicio, int fim) {
    if (inicio >= fim)
        return 1;

    if (palavra[inicio] != palavra[fim])
        return 0;

    return palindromo(palavra, inicio + 1, fim - 1);
}

int main() {
    int n, m, i, j;
    char *palavra;
    char *resultado;

    if (scanf("%d %d", &n, &m) != 2)
        return 0;

    getchar();

    palavra = malloc((m + 2) * sizeof(char));
    resultado = malloc((n + 1) * sizeof(char));

    if (palavra == NULL || resultado == NULL) {
        free(palavra);
        free(resultado);
        return 1;
    }

    for (i = 0; i < n; i++) {
        if (fgets(palavra, m + 2, stdin) == NULL)
            break;

        j = 0;

        while (palavra[j] != '\0' && palavra[j] != '\n' && palavra[j] != '\r') {
            j++;
        }

        palavra[j] = '\0';

        resultado[i] = palindromo(palavra, 0, j - 1) ? '1' : '0';
    }

    resultado[i] = '\0';

    fputs(resultado, stdout);

    free(palavra);
    free(resultado);

    return 0;
}
