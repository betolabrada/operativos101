/**************************
* FILE: hello.c
* DESCRIPTION:
*   A "hello world" Pthreads program.  Demonstrates thread creation and
*   termination.
* AUTHOR: Blaise Barney
* LAST REVISED: 08/09/11
**************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS	1000

int saldo =0;
pthread_mutex_t lockSaldo;

void *PrintHello(void *threadid)
{
   long tid;
   int localsaldo;
   pthread_mutex_lock(&lockSaldo);
   localsaldo = saldo;
   saldo = localsaldo + 100;
   pthread_mutex_unlock(&lockSaldo);
   tid = (long)threadid;
   printf("Hello World! It's me, thread #%ld!\n", tid);
   printf("forzar perder el cpu");
             //forzando el cpu
   //saldo +=100;
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
   pthread_t threads[NUM_THREADS];
   int rc;
   long t;
   for(t=0;t<NUM_THREADS;t++){
     printf("In main: creating thread %ld\n", t);
     rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
     if (rc){
       printf("ERROR; return code from pthread_create() is %d\n", rc);
       exit(-1);
       }
     }

     for (t =0;t <NUM_THREADS;t++){
         pthread_join(threads[t], NULL);
     }

     printf("Espero %d dolares tengo: %d\n",NUM_THREADS*100,saldo);


   /* Last thing that main() should do */
   pthread_exit(NULL);      //espera a que todos terminen para terminar el proceso.
}