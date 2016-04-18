//
// Created by Rafael Dias on 06/04/16.
//
/*

  A administração de um grande parque deseja controlar
através de um sistema computacional as entradas e saídas
deste parque a fim de saber, a qualquer momento, quantas
pessoas encontram-se no interior do parque. Sabendo que
existem duas catracas, uma para entrar e outra para sair,
construa um protótipo do software a ser usado neste
programa

 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>

#define QNT_THREAD 3

pthread_mutex_t turn = PTHREAD_MUTEX_INITIALIZER;

int fora = 150;
int dentro = 100;
int consultas;
int fim = 0;

void* entra_pessoa() {
    while (1) {
        pthread_mutex_lock(&turn);
        if (fora > 0) {
            fora--;
            dentro++;
        }
        pthread_mutex_unlock(&turn);
        if (fim == 1) pthread_exit(0);
    }
}

void* sai_pessoa() {
    while (1) {
        pthread_mutex_lock(&turn);
        if (dentro > 0) {
            fora++;
            dentro--;
        }
        pthread_mutex_unlock(&turn);
        if (fim == 1) pthread_exit(0);
    }
}

void* conta_pessoas() {
    for (int i = 0; i < consultas; i++) {
        sleep(1);
        pthread_mutex_lock(&turn);

        printf("Quantidade de pessoas dentro do parque: %d\n", dentro);

        pthread_mutex_unlock(&turn);
    }

    fim = 1;
}

int main(int argc, char * argv[]) {

    int i = 0;

    printf("Defina o número de consultas: ");
    scanf("%d", &consultas);

    // Inicializa, sem startar as threads
    pthread_t threads[QNT_THREAD];

    pthread_create(&threads[i], NULL, sai_pessoa, NULL);
    i++;
    pthread_create(&threads[i], NULL, entra_pessoa, NULL);
    i++;
    pthread_create(&threads[i], NULL, conta_pessoas, NULL);

    for (int i = 0; i < QNT_THREAD; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}