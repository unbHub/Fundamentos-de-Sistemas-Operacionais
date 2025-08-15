#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t mutex;
int recurso_compartilhado = 0;

void* funcao_thread(void* arg) {
    pthread_mutex_lock(&mutex); // Entra na seção crítica

    // Seção Crítica
    int id = *((int*)arg);
    recurso_compartilhado += 1;
    printf("Thread %d acessou o recurso compartilhado. Valor: %d\n", id, recurso_compartilhado);

    pthread_mutex_unlock(&mutex); // Sai da seção crítica
    free(arg); // Libera a memória alocada para o identificador da thread
    return NULL;
}

int main() {
    pthread_t threads[5];
    int i;

    pthread_mutex_init(&mutex, NULL);

    for (i = 0; i < 5; i++) {
        int *id = malloc(sizeof(int)); // Aloca memória para o identificador da thread
        if (id == NULL) {
            perror("Erro ao alocar memória");
            exit(EXIT_FAILURE);
        }
        *id = i;
        if (pthread_create(&threads[i], NULL, funcao_thread, id) != 0) {
            perror("Erro ao criar thread");
            free(id); // Libera a memória se a criação da thread falhar
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}
