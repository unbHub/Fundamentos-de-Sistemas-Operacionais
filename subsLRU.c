/* Substituição de páginas: LRU
O objetivo deste exercício é escrever uma aplicação que simule o funcionamento do algoritmo LRU (Least Recently Used)
de substituição de páginas usados em sistemas operacionais.
Neste exercício, a sua aplicação receberá uma sequência de números inteiros da entrada padrão:
• o primeiro parâmetro representa a quantidade de quadros de memória disponíveis na RAM;
• o segundo parâmetro representa a quantidade de páginas referenciadas durante a execução de um processo;
• os demais números representam a sequência de referências a páginas, sempre um número separado por linha.
Como saída, a aplicação deverá indicar a quantidade de faltas de páginas (page faults) necessárias para acomodar as
páginas nos quadros disponíveis.
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int page;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int size;
} LinkedList;

// Função para criar um novo nó
Node* createNode(int page) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->page = page;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Função para inicializar uma lista ligada
LinkedList* createList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

// Função para mover um nó para a cabeça da lista
void moveToHead(LinkedList* list, Node* node) {
    if (list->head == node) {
        return;
    }

    if (list->tail == node) {
        list->tail = node->prev;
        list->tail->next = NULL;
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    node->next = list->head;
    node->prev = NULL;
    list->head->prev = node;
    list->head = node;
}

// Função para remover o último nó da lista
int removeTail(LinkedList* list) {
    if (list->tail == NULL) {
        return -1;
    }

    Node* node = list->tail;
    int page = node->page;

    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }

    free(node);
    list->size--;
    return page;
}

// Função para adicionar um nó à cabeça da lista
void addToHead(LinkedList* list, Node* node) {
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
    list->size++;
}

int main() {
    int Q, N;
    scanf("%d", &Q);
    scanf("%d", &N);

    int* pages = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &pages[i]);
    }

    LinkedList* list = createList();
    int* frames = (int*)malloc(Q * sizeof(int));
    for (int i = 0; i < Q; i++) {
        frames[i] = -1;
    }

    int page_faults = 0;
    for (int i = 0; i < N; i++) {
        int page = pages[i];
        int found = 0;

        Node* node = list->head;
        while (node != NULL) {
            if (node->page == page) {
                moveToHead(list, node);
                found = 1;
                break;
            }
            node = node->next;
        }

        if (!found) {
            page_faults++;

            if (list->size == Q) {
                int removedPage = removeTail(list);
                for (int j = 0; j < Q; j++) {
                    if (frames[j] == removedPage) {
                        frames[j] = -1;
                        break;
                    }
                }
            }

            Node* newNode = createNode(page);
            addToHead(list, newNode);

            for (int j = 0; j < Q; j++) {
                if (frames[j] == -1) {
                    frames[j] = page;
                    break;
                }
            }
        }
    }

    printf("%d\n", page_faults);

    free(frames);
    free(pages);
    free(list);
    return 0;
}
