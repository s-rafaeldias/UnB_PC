//
// Created by Rafael Dias Silveira,
// matrícula 14/0030433, on 11/04/16.
//

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <zconf.h>

#define SIZE 100
#define CONS 4
#define PROD 2

pthread_mutex_t turn = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cons, prod;

int itens = SIZE;

void* consumidor() {

    while(1) {
        pthread_mutex_lock(&turn);
        if (itens == 0) pthread_cond_broadcast(&prod);
        itens--;
        if (itens < SIZE) pthread_cond_wait(&cons, &turn);
        printf("Consumindo 1\n");
        sleep(1);
        pthread_mutex_unlock(&turn);
    }

}

void* produtor() {
    while(1) {
        pthread_mutex_lock(&turn);
        if (itens == SIZE) pthread_cond_wait(&prod, &turn);
        itens++;
        if (itens > 0) pthread_cond_broadcast(&cons);
        printf("Produzindo 1\n");
        pthread_mutex_unlock(&turn);
    }

}

int main() {

    pthread_t consumidores[CONS];
    pthread_t produtores[PROD];

    for (int i = 0; i < CONS; i++) {
        pthread_create(&consumidores[i], NULL, consumidor, NULL);
    }

    for (int i = 0; i < PROD; i++) {
        pthread_create(&produtores[i], NULL, produtor, NULL);
    }

    //
    for (int i = 0; i < CONS; i++) {
        pthread_join(consumidores[i], NULL);
    }

    for (int i = 0; i < PROD; i++) {
        pthread_join(produtores[i], NULL);
    }


    return 0;
}