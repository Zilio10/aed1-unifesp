#include <stdio.h>
#include <stdlib.h>

typedef struct Operacao {
    char tipo;
    char caractere;
    int posicao;
    struct Operacao *prox;
}Operacao;

typedef struct Editor {
    char *texto;
    int n;
    Operacao *undo;
    Operacao *redo;
}Editor;

// Setando as estruturas
Operacao *cria_pilha() {
    Operacao *pilha = malloc(sizeof(Operacao));
    pilha->prox = NULL;

    return pilha;
}

Editor *cria_editor() {

    Editor *editor = malloc(sizeof(Editor));

    editor->texto = malloc(sizeof(char)); // Alocando memória dinâmica para o texto de uma qtd de caracteres indefinida
    editor->texto[0] = '\0'; // Cadeia de caracteres vazia

    editor->n = 0;
    editor->undo = cria_pilha();
    editor->redo = cria_pilha();

    return editor;
}

// Manipulação de texto
int insere_caractere(Editor *editor, char letra, int posicao) {

    if (posicao >= 0 && posicao <= editor->n) {

        editor->texto = realloc(editor->texto, (editor->n+2) * sizeof(char)); // Alocando mais um byte para o texto;

        for (int i = editor->n+1; i > posicao; i--) {
            editor->texto[i] = editor->texto[i-1];
        }
        editor->texto[posicao] = letra; // Texto já modificado
        editor->n++;

        return 1;

    }

    return 0;
}

char remove_caractere(Editor *editor, int posicao) {

    if (posicao >= 0 && posicao < editor->n) {

        char letraRemovida = editor->texto[posicao];

        for (int i = posicao; i < editor->n; i++) {
            editor->texto[i] = editor->texto[i+1];
        }
        editor->n--;
        editor->texto = realloc(editor->texto, (editor->n+1) * sizeof(char));

        return letraRemovida;
    }

    return '\0';

}

// Operações das pilhas
void push(Operacao *ref_pilha, char tipo, char caractere, int posicao) {

    Operacao *nova_op = malloc(sizeof(Operacao));
    nova_op->tipo = tipo;
    nova_op->caractere = caractere;
    nova_op->posicao = posicao;

    if (ref_pilha->prox == NULL) {
        ref_pilha->prox = nova_op;
        nova_op->prox = NULL;
    } else {
        nova_op->prox = ref_pilha->prox;
        ref_pilha->prox = nova_op;
    }
}

void pop(Operacao *ref_pilha) {
    if (ref_pilha->prox != NULL) {
        Operacao *aux = ref_pilha->prox;
        ref_pilha->prox = aux->prox;
        free(aux);
    }
}

void despopula_pilha(Operacao *ref_pilha) {

    while (ref_pilha->prox != NULL) { // Limpa toda a pilha
        pop(ref_pilha);
    }

}

// Operações do editor
void inserir(Editor *editor, char letra, int posicao) {

    if (insere_caractere(editor, letra, posicao)) { // Se o texto for alterado:
        push(editor->undo, 'I', letra, posicao); // Push na operação de inserir na pilha de undo
        despopula_pilha(editor->redo); // Despopolando pilha de redo
    }

}

void remover(Editor *editor, int posicao) {

    char letraRemovida = remove_caractere(editor, posicao);

    if (letraRemovida != '\0') { // Se alguma letra foi removida:
        push(editor->undo, 'R', letraRemovida, posicao); // Push na operação de inserir na pilha de undo
        despopula_pilha(editor->redo); // Despopolando pilha de redo
    }

}

void undo(Editor *editor) {

    if (editor->undo->prox != NULL) {
        char tipo = editor->undo->prox->tipo;
        char caractere = editor->undo->prox->caractere;
        int posicao = editor->undo->prox->posicao;

        if (tipo == 'I') { // If para operação contrária equivalente ao ctrl+Z
            remove_caractere(editor, posicao);
        } else {
            insere_caractere(editor, caractere, posicao);
        }

        push(editor->redo, tipo, caractere, posicao); // Inserindo operação na pilha redo
        pop(editor->undo); // Como o undo foi realizado, pop no undo
    }

}

void redo(Editor *editor) {

    if (editor->redo->prox != NULL) {
        char tipo = editor->redo->prox->tipo;
        char caractere = editor->redo->prox->caractere;
        int posicao = editor->redo->prox->posicao;

        if (tipo == 'I') { // Lógica direta
            insere_caractere(editor, caractere, posicao);
        } else {
            remove_caractere(editor, posicao);
        }

        push(editor->undo, tipo, caractere, posicao);
        pop(editor->redo);
    }

}

void desaloca_editor(Editor *editor) {

    // Desalocando as pilhas
    despopula_pilha(editor->undo);
    despopula_pilha(editor->redo);

    // Desalocando as referências
    free(editor->undo);
    free(editor->redo);

    // Desalocando o texto e a referência de editor
    free(editor->texto);
    free(editor);

}


int main() {

    Editor *editor = cria_editor();

    int n;
    scanf("%d", &n);

    editor->n = n; // Setando o tamanho do texto
    editor->texto = realloc(editor->texto, (n + 1) * sizeof(char)); // Realocando espaço para o texto

    if (n > 0) {
        scanf("%s", editor->texto);
    }

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {

        char comando;
        scanf(" %c", &comando);

        if (comando == 'U') {
            undo(editor);
        }
        else if (comando == 'E') {
            redo(editor);
        }
        else if (comando == 'R') {
            int posicao;
            scanf("%d", &posicao);

            remover(editor, posicao);
        }
        else if (comando == 'I') {
            char letra;
            int posicao;

            scanf(" %c %d", &letra, &posicao);

            inserir(editor, letra, posicao);
        }

        printf("%s\n", editor->texto);
    }

    desaloca_editor(editor);

    return 0;
}
