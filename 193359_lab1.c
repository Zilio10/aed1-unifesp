#include <stdio.h>
#define TAM 501


int comparaString(char str1[], char str2[]){
    int i = 0;

    while ((str1[i] != '\0' && str1[i] != '\n') &&
       (str2[i] != '\0' && str2[i] != '\n'))
{
    if (str1[i] != str2[i])
    {
        return 0;
    }

    i++;
}

    if ((str1[i] == '\0' || str1[i] == '\n') &&
        (str2[i] == '\0' || str2[i] == '\n'))
    {
        return 1;
    }

    return 0;

}

int calculaValor(char str[]) {
    int i = 0;
    int letras = 0, num = 0, especiais = 0;

    while (str[i] != '\0' && str[i] != '\n'){

        if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <='z')) {
            letras++;
        } else if (str[i] >= '0' && str[i] <= '9') {
            num++;
        } else {
            especiais++;
        }

        i++;
    }

    return (letras - num) * especiais;
}

int main(){
    char str1[TAM];
    char str2[TAM];

    fgets(str1, TAM, stdin);
    fgets(str2, TAM, stdin);

    printf("%d ", calculaValor(str1));
    printf("%d ", calculaValor(str2));
    printf("%d", comparaString(str1, str2));


    return 0;
}
