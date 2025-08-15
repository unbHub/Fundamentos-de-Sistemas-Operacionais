#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Variáveis globais
int count;
pthread_mutex_t mut;

// Estrutura de argumento para as threads
struct thread_arg {
    int vezes;
};

// Simulação da função work
/* int work(int id) {
    // Simulação de trabalho demorado
    printf("Work id: %d\n", id);
    return 0;
} */

// Função executada por cada thread
void *thread_func(void *arg) {
    struct thread_arg *targ = (struct thread_arg *)arg;
    int vezes = targ->vezes;

    for (int i = 0; i < vezes; i++) {
        int id;

        // Protege a atualização do contador global com um mutex
        pthread_mutex_lock(&mut);
        id = count;
        count++;
        pthread_mutex_unlock(&mut);

        // Chama a função work com o id único
        work(id);
    }

    return NULL;
}

void do_all_work(int n) {
    // Inicializa o mutex
    pthread_mutex_init(&mut, NULL);

    // Determina o número de threads a serem criadas (exemplo: 4 threads)
    int num_threads = 4;
    pthread_t threads[num_threads];
    struct thread_arg args[num_threads];

    // Inicializa o contador global
    count = 0;

    // Cria e inicia as threads
    for (int i = 0; i < num_threads; i++) {
        args[i].vezes = n / num_threads + (i < n % num_threads ? 1 : 0);
        pthread_create(&threads[i], NULL, thread_func, &args[i]);
    }

    // Aguarda a conclusão de todas as threads
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroi o mutex
    pthread_mutex_destroy(&mut);
}

/* int main() {
    int n = 10; // Número total de trabalhos
    do_all_work(n);

    return 0;
} */
