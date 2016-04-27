//
// Created by Rafael Dias Silveira,
// matrícula 14/0030433, on 27/04/16.
//

// Última questão da prova, dessa vez implementado

#include <zconf.h>
#include <pthread.h>

#define USUARIOS 5
#define N 30

int cartas = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond_pombo = PTHREAD_COND_INITIALIZER;;
pthread_cond_t cond_user = PTHREAD_COND_INITIALIZER;;

void* pombo() {
    pthread_mutex_lock(&lock);
    if (cartas == N) {
        cartas = 0;
        pthread_cond_broadcast(&cond_user);
        pthread_cond_wait(&cond_pombo, &lock);
    }
    pthread_mutex_unlock(&lock);
}

void* user() {
    pthread_mutex_lock(&lock);
    if (cartas == N) {
        pthread_cond_signal(&cond_pombo);
        pthread_cond_wait(&cond_user, &lock);
    }
    cartas++;
    pthread_mutex_unlock(&lock);
}

int main() {

    pthread_t users[USUARIOS];
    pthread_t pombos;

    pthread_create(&pombos, NULL, pombo, NULL);

    for (int i = 0; i < USUARIOS; ++i) {
        pthread_create(&users[i], NULL, user, NULL);
    }

    pthread_join(&pombos, NULL);

    for (int i = 0; i < USUARIOS; ++i) {
        pthread_join(&users[i], NULL);
    }

    return 0;

}
