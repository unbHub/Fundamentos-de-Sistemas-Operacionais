#include <stdio.h>
#include <unistd.h>  // Para getpid()

int main() {
    pid_t pid = getpid();  // Obtém o PID do processo atual
    printf("PID do processo atual: %d\n", pid);

    int pid1 = fork();  // Cria um novo processo

    if (pid1 == 0) {
        printf("processo filho %d\n", getpid());  // Executado pelo processo filho
    } else if (pid1 > 0) {
        //sleep(1);
        printf("processo pai %d\n", getpid());  // Executado pelo processo pai
    }

    return 0;
}
