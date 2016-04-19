//
// Created by Rafael Dias Silveira,
// matrícula 14/0030433, on 18/04/16.
//

#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <zconf.h>

#define EQUIPE 10
#define PILOTO 2
#define CARROS 5
#define TRUE 1

sem_t pista; // Semáforo para o acesso a pista de corrida
sem_t equipes[EQUIPE]; // Semáforo para a equipe

void* piloto(void* id) {

    int i = *((int*) id);
    int equipe = i%10;
    int voltas = rand()%5;

    while(TRUE) {
        sem_wait(&equipes[equipe]);
        sem_wait(&pista); // Decrementa uma permissão para acesso ao semaforo
        for (int j = 0; j < voltas; j++) {
            printf("O piloto %d da equipe %d está na pista, na volta de número %d\n", i, equipe,
                   j);
            sleep(5);
        }
        sem_post(&pista); // Incremeta uma permissão para acesso ao semaforo
        sem_post(&equipes[equipe]); // Incrementa uma permissão para acesso ao semaforo
        sleep(20);
    }
}


int main() {

    int* id;

    pthread_t pilotos[PILOTO*EQUIPE];
    sem_init(&pista, 0, CARROS);

    for (int i = 0; i < EQUIPE; i++) {
        sem_init(&equipes[i], 0, 1);
    }

    for (int i = 0; i < EQUIPE*PILOTO; i++) {
        id = (int *) malloc(sizeof(int));
        *id = i;
        pthread_create(&pilotos[i], NULL, piloto, (void*)id);
    }

    for (int i = 0; i < PILOTO*EQUIPE; i++) {
        pthread_join(pilotos[i], NULL);
    }

    return 0;
}