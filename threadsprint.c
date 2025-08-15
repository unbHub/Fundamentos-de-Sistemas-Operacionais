#include <stdio.h>
#include <pthread.h>

void* print_message(void* arg) {
    printf("Thread: %s\n", (char*)arg);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    char* message1 = "Hello";
    char* message2 = "World";

    pthread_create(&thread1, NULL, print_message, (void*)message1);
    pthread_create(&thread2, NULL, print_message, (void*)message2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
