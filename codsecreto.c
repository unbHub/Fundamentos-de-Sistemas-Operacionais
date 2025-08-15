#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

//variavel global -> status da senha
int senha = 0;

void trata(int s) {
	printf("Recebi %d\n",s);
	if(senha==0 && s==SIGINT)
		senha++;
	else if (senha==1 && s==SIGUSR2)
		senha++;
	else if(senha==2 && s==SIGTERM) {
		senha++;
		printf("Senha acionada\n");
	}
	else if(s==SIGINT)
		senha = 1; //retorna a senha para 1
	else if(senha=3 && s==SIGUSR1) {
		printf("Tchau\n");
		exit(0);
	}
	else 
		senha =0;
}
int main(void) {
	//instala e modifica o tratador para cada um dos sinais
	signal(SIGINT, trata);
	signal(SIGTERM, trata);
	signal(SIGUSR1, trata);
	signal(SIGUSR2, trata);

	//processo não pode morrer, apenas com senha 
	while(1)
		pause();

}

