//
// Created by Rafael Dias on 06/04/16.
//
/*

  A administração de um grande parque deseja controlar
através de um sistema computacional as entradas e saídas
deste parque a fim de saber, a qualquer momento, quantas
pessoas encontram-se no interior do parque. Sabendo que
existem duas catracas, uma para entra e outra para sair,
construa um protótipo do software a ser usado neste
programa

 */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex_entrada;
pthread_mutex_t mutex_saida;

pthread_mutex_t parque;

int fora = 150;
int dentro = 100;

void* entra_pessoa(void* a) {



}

void* sai_pessoa(void* a) {



}

int main(int argc, char * argv[]) {



    return 0;
}