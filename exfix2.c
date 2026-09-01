#include <stdio.h>
#include <stdlib.h>

typedef struct Node {

    int info;
    struct Node *next;

} List;

List *insertValue(List *head, int element, int value) {

    List *newNode = (List*)malloc(sizeof(List));
    newNode->info = value;

    if (head == NULL) { // Lista vazia

        newNode->next = NULL;
        head = newNode;
        return head;

    } else { // Lista não está vazia

        List *p;
        for (p = head; p != NULL && p->info != element; p = p->next); // Para quando info == element

        if (p != NULL) { // Elemento foi encontrado

            newNode->next = p->next;
            p->next = newNode;

        } else { // Elemento não foi encontrado

            free(newNode);

        }
    }

    return head;
}

void printList(List *head) {
    List *p;
    if (head != NULL) {
        for (p = head; p != NULL; p = p->next) {
            printf("%d \n", p->info);
        }
    } else {
        printf("Lista vazia");
    }
}

void freeList(List *head) {

    List *p = head;
    while (p != NULL) {
        List *aux = p->next;
        free(p);
        p = aux;
    }
}

int main() {

    List *l = NULL;

    l = insertValue(l, 1, 100);
    l = insertValue(l, 100, 200);

    printList(l);

    freeList(l);

    return 0;
}



