//
// Created by Rafael Dias Silveira,
// matrícula 14/0030433, on 27/04/16.
//

// Última questão da prova, dessa vez implementado

#include <zconf.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define USUARIOS 2
#define N 30

int cartas = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond_pombo = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_user = PTHREAD_COND_INITIALIZER;

void* pombo() {
    while(1) {
        pthread_mutex_lock(&lock);
        if (cartas >= 0) {
            printf("Vai dar o wait no pombo\n");
            pthread_cond_wait(&cond_pombo, &lock);
        }
        cartas = 0;
        printf("Valor de cartas após o pombo: %d\n", cartas);
        sleep(3);
        pthread_cond_broadcast(&cond_user);
        pthread_mutex_unlock(&lock);
    }
}

void* user() {
    while(1) {
        pthread_mutex_lock(&lock);
        if (cartas >= N) {
            printf("Entrou no if do user com %d cartas\n", cartas);
            pthread_cond_broadcast(&cond_pombo);
            pthread_cond_wait(&cond_user, &lock);
        }
        cartas++;
        pthread_mutex_unlock(&lock);
    }
}

int main() {

    pthread_t users[USUARIOS];
    pthread_t pombos;

    pthread_create(&pombos, NULL, pombo, NULL);

    for (int i = 0; i < USUARIOS; ++i) {
        pthread_create(&users[i], NULL, user, NULL);
    }

    pthread_join(pombos, NULL);

    for (int i = 0; i < USUARIOS; ++i) {
        pthread_join(users[i], NULL);
    }

    return 0;

}
