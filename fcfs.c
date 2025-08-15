/* Escalonador FCFS
Um jovem chamado Felipe Carvalho Ferreira Silva estava codificando seu próprio sistema operacional e decidiu criar um
sistema de escalonamento chamado FCFS em homenagem às iniciais de seu nome. Entretanto, o jovem não entende muito
bem como fazer escalonamentos, então ele precisa de um exemplo de escalonador FSFC (First-Come-First-Served).
Simule um escalonador FCFS da seguinte forma:
• Os processos serão vistos como sequencias de 0 e 1.
• 0 significa uma instrução não blocante que leva 10 ms para se executar.
• 1 significa uma instrução blocante que joga o processo para o fim da fila.
• Ao ser interrompido em uma instrução blocante, a mesma intrução é transformada em não blocante, ou seja 0,
quando o processo volta para o fim da fila. Para simplificar a questão, assuma que esse procedimento demora 0 ms.
Ao executar todas as intruções de um processo, imprima na tela o número do processo e o tempo em que ele concluiu sua
execação. Sendo assim, os processos devem aparecer em ordem crescente de tempo de fim de execçãao. */
#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um processo
typedef struct {
    int id;
    int* instructions;
    int instruction_count;
    int current_instruction;
    int completion_time;
} Process;
// Função de comparação usada para ordenar os processos pelo tempo de conclusão
int compare(const void* a, const void* b) {
    Process* processA = (Process*)a;
    Process* processB = (Process*)b;
    return processA->completion_time - processB->completion_time;
}

int main() {
    int N;
    scanf("%d", &N);

    /* Lê o número de processos N e aloca memória para armazenar a 
    quantidade de instruções de cada processo e os processos em si. */
    int* instruction_counts = (int*)malloc(N * sizeof(int));
    Process* processes = (Process*)malloc(N * sizeof(Process));

    // Lê a quantidade de instruções de cada processo
    for (int i = 0; i < N; i++) {
        scanf("%d", &instruction_counts[i]);
    }

    // Lê as instruções de cada processo
    /* Para cada processo, lê a quantidade de instruções e depois lê as instruções reais, 
    armazenando-as na estrutura do processo. */
    for (int i = 0; i < N; i++) {
        processes[i].id = i + 1;
        processes[i].instruction_count = instruction_counts[i];
        processes[i].instructions = (int*)malloc(instruction_counts[i] * sizeof(int));
        processes[i].current_instruction = 0;
        processes[i].completion_time = 0;

        for (int j = 0; j < instruction_counts[i]; j++) {
            scanf("%d", &processes[i].instructions[j]);
        }
    }

    int current_time = 0;
    int completed_processes = 0;

    // Fila de processos
    Process* queue = (Process*)malloc(N * sizeof(Process));
    int queue_size = N;

    // Inicializa a fila com todos os processos
    for (int i = 0; i < N; i++) {
        queue[i] = processes[i];
    }

    // Executa os processos em ordem FCFS
    while (completed_processes < N) {
        Process current_process = queue[0];

        // Remove o processo atual da fila
        for (int i = 1; i < queue_size; i++) {
            queue[i - 1] = queue[i];
        }
        queue_size--;

        while (current_process.current_instruction < current_process.instruction_count) {
            int instr = current_process.instructions[current_process.current_instruction];

            if (instr == 0) {
                current_time += 10;
                current_process.current_instruction++;
            } else if (instr == 1) {
                current_process.instructions[current_process.current_instruction] = 0;  // Transforma 1 em 0
                queue[queue_size++] = current_process;  // Reinsere o processo no fim da fila
                break;
            }
        }

        if (current_process.current_instruction == current_process.instruction_count) {
            current_process.completion_time = current_time;
            processes[current_process.id - 1] = current_process; // Atualiza o processo original com o tempo de conclusão
            completed_processes++;
        }
    }

    // Ordena os processos pelo tempo de conclusão
    qsort(processes, N, sizeof(Process), compare);

    // Imprime os tempos de conclusão dos processos em ordem de tempo de conclusão
    for (int i = 0; i < N; i++) {
        printf("%d (%d)\n", processes[i].id, processes[i].completion_time);
    }

    // Libera a memória alocada
    for (int i = 0; i < N; i++) {
        free(processes[i].instructions);
    }
    free(processes);
    free(instruction_counts);
    free(queue);

    return 0;
}
