#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define NUM_FILOS 5

pthread_mutex_t forks[NUM_FILOS];

// srand -> semilla
// rand -> valor random}

void actions()
{
    sleep(1 + rand()%5);
}

void * life(void *ptId)
{
    long tid;
    tid = (long)ptId;

    srand(time(NULL) + tid);

    while(1)
    {
        // pensar
        printf("Para pensar %ld\n", tid);
        actions();
        printf("Hace hambre xd %ld\n", tid);
        if(tid % 2 == 0)
        {
            // indica que ya lo agarro y modifica el valor
            pthread_mutex_lock(&forks[tid]); // TENEDOR DE ENFRENTE
            printf("Agarro tenedor derecho %ld\n", tid);
            pthread_mutex_lock(&forks[(tid+1)%NUM_FILOS]); // TENEDOR DE ALADO
            printf("Ya tengo tenedor izquierdo %ld\n", tid);
            printf("A comer wuuu %ld\n", tid);
            actions();
            printf("Ya acabe ahora a regresar tenedores %ld\n", tid);
            pthread_mutex_unlock(&forks[tid]); // TENEDOR DE ENFRENTE
            pthread_mutex_unlock(&forks[(tid+1)%NUM_FILOS]); // TENEDOR DE ALADO
        }
        else
        {
            // indica que ya lo agarro y modifica el valor
            pthread_mutex_lock(&forks[(tid+1)%NUM_FILOS]);
            printf("Agarro tenedor izquierdo %ld\n", tid);
            pthread_mutex_lock(&forks[tid]);
            printf("Agarro tenedor derecho %ld\n", tid);

            printf("A comer wuuu %ld\n", tid);
            actions();
            printf("Ya acabe ahora a regresar tenedores %ld\n", tid);

            pthread_mutex_unlock(&forks[tid]);
            pthread_mutex_unlock(&forks[(tid+1)%NUM_FILOS]); // TENEDOR DE ALADO
        }
    }
}

int main(int argc, char *argv[])
{
   pthread_t threads[NUM_FILOS];
   int rc;
   long t;
   for(t=0;t<NUM_FILOS;t++){
     printf("In main: creating thread %ld\n", t);
     rc = pthread_create(&threads[t], NULL, life, (void *)t);
     if (rc){
       printf("ERROR; return code from pthread_create() is %d\n", rc);
       exit(-1);
       }
     }
    pthread_exit(NULL);
}

