/* Substituição de páginas: FIFO
O objetivo deste exercício é escrever uma aplicação que simule o funcionamento de algoritmos de substituição de páginas
usados em sistemas operacionais.
Neste exercício, a sua aplicação receberá uma sequência de números inteiros da entrada padrão:
• o primeiro parâmetro representa a quantidade de quadros de memória disponíveis na RAM;
• o segundo parâmetro representa a quantidade de páginas referenciadas durante a execução de um processo;
• os demais números representam a sequência de referências a páginas, sempre um número separado por linha.
Como saída, a aplicação deverá indicar a quantidade de faltas de páginas (page faults) necessárias para acomodar as
páginas nos quadros disponíveis. Neste exercício, utilizaremos a heurística FIFO para reposicionar as páginas.
 */
#include <stdio.h>
#include <stdlib.h>

// Função para verificar se uma página está na memória
int isInMemory(int *frames, int size, int page) {
    for (int i = 0; i < size; i++) {
        if (frames[i] == page) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int Q, N;

    // Leitura do número de quadros de memória e do número de referências
    scanf("%d", &Q);
    scanf("%d", &N);

    int *frames = (int *)malloc(Q * sizeof(int)); // Aloca memória para os quadros
    int *pages = (int *)malloc(N * sizeof(int)); // Aloca memória para as páginas referenciadas

    // Inicialização dos quadros de memória com -1 para indicar que estão vazios
    for (int i = 0; i < Q; i++) {
        frames[i] = -1;
    }

    // Leitura das páginas referenciadas
    for (int i = 0; i < N; i++) {
        scanf("%d", &pages[i]);
    }

    int page_faults = 0; // Contador de page faults
    int index = 0; // Índice para substituir a página no quadro

    // Processa cada página referenciada
    for (int i = 0; i < N; i++) {
        int page = pages[i];

        // Verifica se a página já está na memória
        if (!isInMemory(frames, Q, page)) {
            frames[index] = page; // Insere a nova página na memória
            index = (index + 1) % Q; // Atualiza o índice de substituição
            page_faults++; // Incrementa o contador de page faults
        }
    }

    // Imprime a quantidade de page faults
    printf("%d\n", page_faults);

    // Libera a memória alocada
    free(frames);
    free(pages);

    return 0;
}
