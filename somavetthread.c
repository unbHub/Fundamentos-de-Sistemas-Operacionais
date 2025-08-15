#include <stdio.h>
#include <pthread.h>

int thread(int inicio, int fim, int* vet, int* vet2, int*vet3) {
    int i;
    for (i=inicio;i<fim;i++) {
        vet3[i] = vet[i] + vet2[i];
    }
    return 0;
}
int main(){
    int vetor[100], vetor2[100], vetor3[100];
    create_thread(thread, 0, 50, vetor, vetor2, vetor3);
    create_thread(thread, 50, 100, vetor, vetor2, vetor3);
    return 0;
}