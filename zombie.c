#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
void fazoqofilhofaz();

void fazoqopaifaz(){
    printf("%d Sou o pai\n", getpid());
    pid_t processo;
    int ret;
    processo=fork();
    //processo > 0 estou no pai
    if(processo==0) 
        fazoqofilhofaz();
    //processo= wait(NULL);
    //printf("Filho %d terminou, tbm vou\n", processo);
    processo= wait(&ret); //termina o filho
    printf("Filho %d terminou com %d, tbm vou\n", processo, WEXITSTATUS(ret));
    processo= wait(&ret);
    printf("Filho %d terminou com %d, tbm vou\n", processo, WEXITSTATUS(ret));
    exit(0);
}
void fazoqofilhofaz(){
    printf("%d: Sou o filho e meu pai eh %d\n", getpid(), getppid());
    sleep(1);
    printf("%d: Sou o filho e meu pai eh %d\n", getpid(), getppid());
    exit(0);
    //printf("ainda vivo????\n");
}

int main(void) {

    pid_t processo;
    //duplica o processo, criando um processo pai e filho mas são idênticos nesse ponto
    processo = fork();
    if(processo>0){
        fazoqopaifaz();
    }
    else if(processo==0){
        fazoqofilhofaz();
    }
    else{
        printf("FORK falhou\n");
    }
}