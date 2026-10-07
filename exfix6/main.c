#include <stdio.h>
#include <stdlib.h>

#define TAM_BUFFER 1024

int verifica_files(FILE *feb, FILE *fst, FILE *fet, FILE *fsb) {

    if (feb != NULL && fst != NULL && fet != NULL && fsb != NULL)
        return 0;

    return 1;

}

void binario_p_texto(FILE *feb, FILE *fst) { // Usarei fread para ler em binário

    int n1, n2, n3; // 3 inteiros do arquivo binário

    while (!feof(feb)) { // Enquanto o arquivo nao chega ao fim...

        fread(&n1, sizeof(int), 1, feb); // fread( endereço que vai receber, tamanho, qtd, arquivo a ser lido )
        fread(&n2, sizeof(int), 1, feb);
        fread(&n3, sizeof(int), 1, feb);

        if (!feof(feb))
            fprintf(fst, "%d %d %d\n", n1, n2, n3); // Escrevendo os inteiros lidos de forma formatada

    }

}

void saida_p_entrada_txt(FILE *fst, FILE *fet) { // Copia os bytes de saida.txt para entrada.txt

    rewind(fst); // Voltando o ponteiro de leitura para o inicio do arquivo

    char buffer[TAM_BUFFER]; // buffer de caractares que guardará os bytes de saida.txt (de tamanho fixo)
    size_t qtd_lida;

    do { // o while é usado, pois pode ser q saida.txt tenha mais q 1024 bytes, ai ele vai lendo, descarrega o buffer com 1024 e entra no while dnv

        qtd_lida = fread(buffer, sizeof(char), TAM_BUFFER, fst); // Fread retorna a qtd de byes lidos
        fwrite(buffer, sizeof(char), qtd_lida, fet);

    } while (qtd_lida > 0); // Enquanto fread ainda lê o conteúdo (conteúdo n acabou)

}

void texto_p_binario(FILE *fet, FILE *fsb) {

    fseek(fet, 0, SEEK_SET); // Posicionando o ponteiro do arquivo para o começo (SEEK_SET), e deslocando 0 bytes

    char buffer[TAM_BUFFER];
    int n[3];

    while (fgets(buffer, TAM_BUFFER, fet) != NULL) {
        sscanf(buffer, "%d %d %d", &n[0], &n[1], &n[2]);
        fwrite(n, sizeof(int), 3, fsb);
    }

}

void descarrega_buffers(FILE *feb, FILE *fst, FILE *fet, FILE *fsb) {
    fflush(feb);
    fflush(fst);
    fflush(fet);
    fflush(fsb);
}

void fecha_arquivos(FILE *feb, FILE *fst, FILE *fet, FILE *fsb) {
    fclose(feb);
    fclose(fst);
    fclose(fet);
    fclose(fsb);
}

int main(int argc, char *argv[])
{
    if (argc != 5)
        return 1;

    FILE *F_entrada_bin = fopen(argv[1], "rb"); // Binário para leitura somente
    FILE *F_saida_txt = fopen(argv[2], "w+"); // Cria se não existir, escreve e lê, zera o conteúdo
    FILE *F_entrada_txt = fopen(argv[3], "a+"); // Leitura e escrita no final, preservando o conteúdo
    FILE *F_saida_bin = fopen(argv[4], "wb"); // Somente escrita para um binário, sobreescreve e cria o arquivo se n existir

    if (verifica_files(F_entrada_bin, F_saida_txt, F_entrada_txt, F_saida_bin))
        return 1;

    binario_p_texto(F_entrada_bin, F_saida_txt); // Primeira operação
    saida_p_entrada_txt(F_saida_txt, F_entrada_txt); // Segunda operação
    texto_p_binario(F_entrada_txt, F_saida_bin); // Terceira operação

    descarrega_buffers(F_entrada_bin, F_saida_txt, F_entrada_txt, F_saida_bin); // Descarregando todos os buffers
    fecha_arquivos(F_entrada_bin, F_saida_txt, F_entrada_txt, F_saida_bin); // Fechando todos os arquivos


    return 0;
}
