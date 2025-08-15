#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

// Função executada pela thread
void* thread_function(void* arg) {
    // Obtém o PID do processo atual
    pid_t pid = getpid();
    printf("Thread: PID do processo atual: %d\n", pid);

    // Obtém o PID do processo pai
    pid_t ppid = getppid();
    printf("Thread: PID do processo pai: %d\n", ppid);

    // Obtém o ID da thread atual
    pthread_t tid = pthread_self();
    printf("Thread: ID da thread atual: %ld\n", tid);

    // Obtém o número de núcleos de CPU disponíveis
    int num_cores = sysconf(_SC_NPROCESSORS_ONLN);
    printf("Thread: Número de núcleos de CPU disponíveis: %d\n", num_cores);

    return NULL;
}

int main() {
    // Obtém o PID do processo principal (pai)
    pid_t main_pid = getpid();
    printf("Processo principal: PID do processo principal: %d\n", main_pid);

    // Criação da thread
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, thread_function, NULL);

    // Aguarda a finalização da thread
    pthread_join(thread_id, NULL);

    return 0;
}
