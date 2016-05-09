//
// Created by Rafael Dias Silveira,
// matrícula 14/0030433, on 09/05/16.
//

// Usar threads para calculo de somatorio de termos de matrizes

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define L 10
#define C 10

int matriz[L][C];
int array[L];
int soma_matriz = 0;

pthread_barrier_t barrier;


void preenche_matriz() {
    for (int i = 0; i < C; i++) {
        for (int j = 0; j < L; j++) {
            matriz[i][j] = rand()%10;
        }
    }
}

void* soma_linha(void* id){

    int linha = *((int*) id);

    for (int i = 0; i < C; i++) {
        array[linha] += matriz[linha][i];
    }
    printf("Valor da soma da linha %d: %d\n", linha, array[linha]);

    pthread_barrier_wait(&barrier);

}

void soma_porra_toda() {


    for (int i = 0; i < L; i++) {
        soma_matriz += array[i];
    }

}

int main() {

    int* id;

    pthread_t somador_linha[L];
    pthread_barrier_init(&barrier, NULL, L);

    preenche_matriz();

    for (int i = 0; i < L; i++) {
        id = (int*) malloc(sizeof(int));
        *id = i;
        pthread_create(&somador_linha[i], NULL, soma_linha, (void*)id);
    }

    for (int i = 0; i < L; i++) {
        pthread_join(somador_linha[i], NULL);
    }

    soma_porra_toda();

    printf("Soma das matrizes: %d\n", soma_matriz);

    return 0;
}