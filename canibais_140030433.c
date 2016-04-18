//
// Created by Rafael Dias, matrícula 14/0030433 on 06/04/16.
//

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <zconf.h>

#define THREADS 5

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t coz, can;

int comidinha = 0;

void* cozinheiro() {

    while(1) {
        pthread_mutex_lock(&lock);
        while(comidinha != 0) {
            pthread_cond_wait(&coz, &lock);
        }
        printf("Comidinha restante: %d\n", comidinha);
        printf("Fazendo a comidinha\n");
        sleep(1);
        comidinha = 20;
        printf("Comidinha agora: %d\n", comidinha);
        sleep(1);
        pthread_cond_broadcast(&can);
        pthread_mutex_unlock(&lock);
    }
}

void* canibal() {
    while(1) {
        pthread_mutex_lock(&lock);
        while (comidinha == 0) {
            pthread_cond_wait(&can, &lock);
        }
        comidinha--;
        printf("Comendo comidinha!!!\n");
        if (comidinha == 0) {
            pthread_cond_signal(&coz);
        }
        pthread_mutex_unlock(&lock);
    }
}

int main() {

    pthread_t cani[THREADS];
    pthread_t cozi;

    pthread_create(&cozi, NULL, cozinheiro, NULL);

    for (int i = 0; i < THREADS; i++) {
        pthread_create(&cani[i], NULL, canibal, NULL);
    }

    pthread_join(cozi, NULL);

    for (int i = 0; i < THREADS; i++) {
        pthread_join(cani[i], NULL);
    }

    return 0;
}