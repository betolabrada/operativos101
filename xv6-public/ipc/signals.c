#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int num = 1;

#define SIGNAL 10 // señal SIGUSR1

void signalHandler(int sgn)
{
    printf("que pedo signal: %d\n", sgn);
    num = num - 1;
    printf("num: %d\n", num);
}

int main()
{
    int pid;
    signal(SIGNAL, signalHandler);
    pid = fork();
    if ( pid == 0 )
    {
        // Soy el hijo
        printf("soy el hijo\n");
        // codigo que quiero que haga el hijo
        // for(;;){} // loop infinito
        while(num){}
        printf("ya me sali\n");
    }
    else
    {
        // race condition:
        // primer escenario, el padre se ejecuta primero, el padre manda la señal al hijo antes del if
        // entonces como no se ha declarado el manejador el proceso termina.
        // segundo escenario: declaramos la señal antes del fork, asi ambos tienen el manejador aunque solo
        // el hijo la va a utilizar

        // soy el jefe
        printf("Soy el proceso padre y mijo es: %d\n", pid);
        sleep(5);
        kill(pid, SIGNAL);

        for(;;){}
    }


}