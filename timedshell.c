#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <string.h>
#include <errno.h>

int main() {
    /*Declaração das variáveis utilizadas para armazenar o status de saída do 
    processo filho (exitStat) e os tempos de início (init), fim (end) e total (total) para medição do tempo.*/
    int exitStat;
    struct timeval init, end, total;
    
    /*Declaração dos arrays de caracteres para armazenar o comando (command) 
    e o argumento (argument) fornecidos na entrada.*/
    char comand[260], arg[260];

    //Captura do tempo total de execução do programa.
    gettimeofday(&total, NULL);
    /*    Loop para ler os comandos 
    e argumentos da entrada padrão até o final do arquivo (EOF).*/
    while(scanf("%s %s", comand, arg) != EOF){
        //    Criação de um processo filho.
        pid_t child = fork();
        //    Captura do tempo de início da execução do processo filho.
        gettimeofday(&init, NULL);
        //     Verificação se o processo é o filho.
        if(child == 0){
            /*    Substituição da imagem do processo filho pela execução do comando fornecido.*/
            /*A função execl() faz parte da família de funções exec em Unix-like sistemas operacionais e
            é usada para substituir a imagem do processo atual pela imagem de um novo processo. 
            Nesse caso, execl() espera o caminho do executável (command), o próprio comando (command), 
            os argumentos para o comando (argument) e um argumento nulo (NULL) para indicar o final da lista de argumentos.*/
            execl(comand,comand, arg, NULL);

            /*    Impressão de uma mensagem de erro caso a execução do comando falhe, 
            seguida do fechamento dos descritores de arquivo e saída do processo filho com o código de erro correspondente.*/
            printf("> Erro: %s\n", strerror(errno));

            /*A função fflush(stdout) é usada para limpar o buffer de saída (stdout). 
            Em muitos sistemas operacionais, a saída padrão é armazenada em um buffer 
            interno antes de ser exibida no terminal. fflush(stdout) força a exibição 
            imediata do conteúdo do buffer, garantindo que qualquer texto pendente seja 
            exibido antes de prosseguir com a execução do programa.*/
            fflush(stdout);

            /*A função fclose() é usada para fechar o fluxo de arquivo especificado. 
            Neste caso, stdin (entrada padrão) é fechado. Isso é feito após uma falha na execução do comando, 
            onde o programa não precisa mais ler da entrada padrão. Isso também pode ser uma precaução para evitar 
            que o processo filho leia mais da entrada, embora já tenha falhado.*/
            fclose(stdin);
            exit(errno);
        }
        //    Espera pelo término do processo filho e armazena seu status de saída.
        wait(&exitStat);
        //    Captura do tempo de término da execução do processo filho.
        gettimeofday(&end, NULL);
        //    Impressão do tempo de execução do processo filho e seu código de retorno.
        printf("> Demorou %.1lf segundos, retornou %d\n", ((end.tv_sec-init.tv_sec) + ((end.tv_usec-init.tv_usec)/1000000.0)), WEXITSTATUS(exitStat));
        //   Fim do loop de leitura dos comandos e argumentos.
        fflush(stdout);
    }
    //    Impressão do tempo total de execução do programa.
    printf(">> O tempo total foi de %.1lf segundos\n", ((end.tv_sec-total.tv_sec) + ((end.tv_usec-total.tv_usec)/1000000.0)));
    //    Limpeza do buffer de saída.
    fflush(stdout);
    exit(0);
}