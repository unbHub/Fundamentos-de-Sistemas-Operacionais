/*
1. Primeiramente o seu processo deve ser capaz de tratar sinais SIGUSR1 ou SIGUSR2
2. Depois de instalar os tratadores de sinais o seu processo deve aguardar algum dos 
sinais acima;
3. Assim que receber o sinal, o seu processo deve criar um processo ZUMBI e aguardar 
por outro sinal (qualquer um dos dois do passo 1)
4. Depois que seu processo receber mais um sinal, ele deverá ser capaz de eliminar 
o zumbi e deverá novamente esperar por outro sinal (qualquer um do passo 1)
5. Depois que seu processo receber esse último sinal ele deverá sair com exit status 0.


Inicia; Aguarda Sinal; Cria processo zumbi; aguarda sinal; destrói processo zumbi; 
aguarda sinal; encerra com sucesso.
– Você tem que estar pronto para receber, ao todo, 3 sinais (podendo ser SIGUSR1 ou SIGUSR2).

Sinais são um mecanismo de comunicação entre processos ou entre um processo e o sistema operacional. 
Eles são mensagens simples que podem ser enviadas a um processo para notificar eventos ou condições. 
Os sinais podem ser usados para interagir com um programa em execução, controlando seu comportamento.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t child_pid = 0;  // Variável para armazenar o PID do processo filho

// Tratador de sinal para SIGUSR1 e SIGUSR2
void handle_signal(int sig) {

    static int sig_count = 0;  // Contador para acompanhar os sinais recebidos
    sig_count++;

    // Primeiro sinal recebido: cria um processo zumbi
    if (sig_count == 1) {
        child_pid = fork();
        // if (child_pid == -1) {
        //     perror("Erro ao criar processo filho");
        //     exit(EXIT_FAILURE);
        // } 
        if (child_pid == 0) {
            // Processo filho
            exit(0);  // Termina imediatamente, criando um zumbi
        }
    }
    // Segundo sinal recebido: elimina o processo zumbi
    else if (sig_count == 2) {
        if (child_pid > 0) {
            int status;
            waitpid(child_pid, &status, 0);  // Espera o filho e reaproveita o processo zumbi
            child_pid = 0;  // Zera o PID do filho
        }
    }
    // Terceiro sinal recebido: encerra o processo pai com sucesso
    else if (sig_count == 3) {
        exit(0);
    }
}

int main() {
    // Configura os tratadores de sinal para SIGUSR1 e SIGUSR2
    struct sigaction sa;

    // O sinal recebido será tratado pela função handle_signal
    sa.sa_handler = handle_signal;

    // Esta linha define as opções ou flags do tratador de sinal. 
    // A flag SA_RESTART indica que as chamadas de sistema interrompidas 
    // por um sinal devem ser reiniciadas automaticamente após a execução 
    // do tratador de sinal. Isso é útil para evitar interrupções não 
    // planejadas em chamadas de sistema.
    sa.sa_flags = SA_RESTART;

    // A função sigaction é usada para especificar o tratador de sinal que deve 
    // ser invocado quando o programa recebe um sinal. O terceiro argumento (NULL) 
    // é uma estrutura sigaction para salvar o estado anterior do tratador de sinal, 
    // mas como isso não é necessário neste caso, passamos NULL.
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    // O processo pai continua aguardando sinais indefinidamente
    while (1) {
        pause();  // Suspende a execução até receber um sinal
    }

    return 0;
}
