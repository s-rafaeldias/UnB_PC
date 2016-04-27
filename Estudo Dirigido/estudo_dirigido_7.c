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
pthread_cond_t cond_pombo;

pthread_cond_t cond_user;

void* pombo() {
    pthread_mutex_lock(&lock);

    pthread_mutex_unlock(&lock);
}

void* user() {
    pthread_mutex_lock(&lock);
    if (cartas == 30) {
        pthread_cond_signal(&cond_pombo);
        pthread_cond_wait(&cond_user, &lock);
    }
    pthread_mutex_unlock(&lock);
}

int main() {

}
