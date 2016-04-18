//
// Created by Rafael Dias Silveira,
// matrícula 14/0030433, on 13/04/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <zconf.h>

#define N 100
#define TRUE 1
#define PROD 9
#define CONS 10

sem_t empty;
sem_t full;
sem_t mutex;

int item = N;


void* consumidor() {
    while(TRUE) {
        sem_wait(&full);
        sem_wait(&mutex);
        item--;
        printf("Consome 1. Total restante: %d\n", item);
        sem_post(&mutex);
        sem_post(&empty);
        sleep(3);
    }
    pthread_exit(0);
}

void* produtor() {
    while(TRUE) {
        sem_wait(&empty);
        sem_wait(&mutex);
        item++;
        printf("Produz 1. Total restante: %d\n", item);
        sem_post(&mutex);
        sem_post(&full);
        sleep(5);
    }
    pthread_exit(0);
}

int main() {

    pthread_t consumidores[CONS];
    pthread_t produtores[PROD];
    sem_init(&empty, 0, 0);
    sem_init(&full, 0, N);
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < CONS; i++) {
        pthread_create(&consumidores[i], NULL, consumidor, NULL);
    }

    for (int i = 0; i < PROD; i++) {
        pthread_create(&produtores[i], NULL, produtor, NULL);
    }

    for (int i = 0; i < CONS; i++) {
        pthread_join(consumidores[i], NULL);
    }

    for (int i = 0; i < PROD; i++) {
        pthread_join(produtores[i], NULL);
    }

    return 0;

}