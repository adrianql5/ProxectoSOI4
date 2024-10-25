#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* thread_function(void* arg) {
    int thread_num = *(int*)arg;
    printf("Hilo %d: Iniciando\n", thread_num);

    sleep(1);

    printf("Hilo %d: Terminando\n", thread_num);
    return NULL;
}

void* exit_thread_function(void* arg) {
    printf("Hilo de salida: Iniciando\n");

    sleep(2);

    printf("Hilo de salida: Llamando a exit\n");
    exit(0);
    return NULL;
}

int main() {
    pthread_t threads[3];
    int thread_args[3];

    for (int i = 0; i < 3; i++) {
        thread_args[i] = i + 1;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_args[i]) != 0) {
            perror("Error creando hilo");
            exit(1);
        }
    }


    pthread_t exit_thread;
    if (pthread_create(&exit_thread, NULL, exit_thread_function, NULL) != 0) {
        perror("Error creando hilo de salida");
        exit(1);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_join(exit_thread, NULL);

    return 0;
}

