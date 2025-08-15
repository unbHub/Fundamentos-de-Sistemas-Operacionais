#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

/* Aqui, é declarada uma variável global exitfilho que será usada para indicar o 
estado de término do processo filho. Além disso, é definida uma função de 
tratamento de sinais chamada trata, que é invocada quando um sinal (SIGUSR1 ou SIGUSR2) 
é recebido. Esta função atualiza a variável exitfilho com o valor do sinal recebido. */
int exitfilho = 0;

void trata(int s){
	exitfilho = s;
}
/* No main(), são registrados os tratadores de sinais para SIGUSR1 e SIGUSR2 usando a função signal(). 
Em seguida, o programa entra em um estado de pausa (pause()), aguardando a chegada de um sinal. */
int main(void){

	signal(SIGUSR1,trata);
	signal(SIGUSR2, trata);

	pause();

	/* Quando um sinal é recebido e o programa retoma a execução, ele verifica se está no processo filho. 
	Se estiver no processo filho (o retorno de fork() é zero), ele imediatamente sai (exit(0)), encerrando o processo filho. */
	if(fork()==0) //se já estiver no processo filho
		exit(0); //morre

	/* O processo pai, depois de verificar que não está no processo filho, continua na execução e entra em um estado de pausa (pause()), 
	aguardando a chegada de um sinal. Nesse ponto, ele não trata os sinais enviados pelo filho, o que pode resultar em um processo zumbi. */
	pause(); //nao pega o sinal do filho, continua zumbi

	/* Após o segundo sinal ser recebido, o programa chama a função wait(NULL), 
	que aguarda o término de qualquer processo filho e limpa o processo filho zumbi. */
	wait(NULL); //elimina zumbi

/* 	Finalmente, após limpar qualquer processo filho zumbi, o processo pai entra em um estado de pausa (pause()) novamente, 
	aguardando a chegada de outro sinal. Quando o último sinal é recebido, o programa sai com sucesso (exit(0)).
 */
	pause(); 
	exit(0);

/* 	Esse programa demonstra uma técnica para evitar a criação de processos zumbis e gerenciar o término do processo filho usando sinais.
 */
}
