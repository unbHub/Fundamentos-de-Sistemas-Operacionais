#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

void fazoqopaifaz(){
    printf("%d Sou o pai\n", getpid());
}
void fazoqofilhofaz(){
    printf("%d Sou o filho\n", getpid());
    //filho do 1º processo pai tem +2 filhos
    pid_t processo;
    processo = fork();
    //se p>0 estou no processo pai
    if(processo>0) {
        fork();
    }
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