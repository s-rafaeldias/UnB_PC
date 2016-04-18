//
// Created by Rafael Dias on 06/04/16.
//

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define NLeste 10
#define NOeste 10

pthread_mutex_t mutex_leste;
pthread_mutex_t mutex_oeste;
pthread_mutex_t entrada;

pthread_mutex_t turno;

int leste = 0;
int oeste = 0;

void * macaco_leste(void * a){
    int i = *((int *) a);
    while(1){
        pthread_mutex_lock(&turno);
        pthread_mutex_lock(&mutex_leste);
        leste++;
        if(leste == 1){
            pthread_mutex_lock(&entrada);
        }
        pthread_mutex_unlock(&mutex_leste);
        pthread_mutex_unlock(&turno);
        printf("Macaco %d passado do leste para oeste \n",i);
        sleep(1);
        pthread_mutex_lock(&mutex_leste);
        leste--;
        printf("Macaco %d terminou de passar de leste para oeste ; num: %d\n" ,i,leste);
        if(leste == 0){
            pthread_mutex_unlock(&entrada);
        }
        pthread_mutex_unlock(&mutex_leste);
    }
    pthread_exit(0);
}

void * macaco_oeste(void * a)
{
    int i = *((int *) a);
    while(1){
        pthread_mutex_lock(&turno);
        pthread_mutex_lock(&mutex_oeste);
        oeste++;
        if(oeste == 1){
            pthread_mutex_lock(&entrada);
        }
        pthread_mutex_unlock(&mutex_oeste);
        pthread_mutex_unlock(&turno);
        printf("Macaco %d passado do oeste para leste \n",i);
        sleep(1);
        pthread_mutex_lock(&mutex_oeste);
        oeste--;
        printf("Macaco %d terminou de passar de oeste para leste; num: %d\n" ,i,oeste);
        if(oeste == 0){
            pthread_mutex_unlock(&entrada);
        }
        pthread_mutex_unlock(&mutex_oeste);


    }
    pthread_exit(0);
}

int main(int argc, char * argv[])
{
    pthread_t m_o[NOeste+NLeste];


    pthread_mutex_init(&mutex_leste, NULL);
    pthread_mutex_init(&mutex_oeste, NULL);
    pthread_mutex_init(&entrada, NULL);
    pthread_mutex_init(&turno, NULL);


    int *id;
    int i = 0;
    for(i = 0; i < NOeste+NLeste; ++i)
    {
        id = (int *) malloc(sizeof(int));
        *id = i;
        if(i%2 == 0){
            if(pthread_create(&m_o[i], NULL, &macaco_oeste, (void*)id))
            {

                printf("NÃo pode criar a thread %d\n", i);
                return -1;
            }
        }else{
            if(pthread_create(&m_o[i], NULL, &macaco_leste, (void*)id))
            {
                printf("NÃo pode criar a thread %d\n", i);
                return -1;
            }
        }
        id++;
    }



    for(i = 0; i < NOeste+NLeste; ++i)
    {
        if(pthread_join(m_o[i], NULL))
        {
            printf("Could not join thread %d\n", i);
            return -1;
        }
    }


    printf("TERMINOU!\n");

    return 0;
}
