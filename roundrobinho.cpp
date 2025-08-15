#include <iostream>
#include <vector>

using namespace std;

// Estrutura para representar um processo
struct Processo {
    int pid;
    int tempo_execucao;
    int tempo_restante;
};

int main() {
    int num_processos;
    int quantum;
    
    cin >> num_processos;
    cin >> quantum;
    
    //Criação de um vetor chamado processos com capacidade para armazenar num_processos elementos do tipo Processo.
    vector<Processo> processos(num_processos);
    
    // Preencher informações dos processos
    for (int i = 0; i < num_processos; ++i) {
        cin >> processos[i].pid >> processos[i].tempo_execucao;
        processos[i].tempo_restante = processos[i].tempo_execucao * 1000; // Converter para ms
    }
    
    // Escalonamento dos processos
    int tempo_total = 0;
    while (!processos.empty()) {
        for (size_t i = 0; i < processos.size(); ++i) {
            if (processos[i].tempo_restante > 0) {
                int tempo_executado = min(quantum, processos[i].tempo_restante);
                processos[i].tempo_restante -= tempo_executado;
                tempo_total += tempo_executado;
                if (processos[i].tempo_restante <= 0) {
                    // Processo concluído
                    cout << processos[i].pid << " (" << tempo_total << ")" << endl;
                    processos.erase(processos.begin() + i);
                    --i; // Ajustar o índice após a remoção do processo
                }
            }
        }
    }

    return 0;
}
