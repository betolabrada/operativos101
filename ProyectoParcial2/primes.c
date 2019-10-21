#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int prime;
char bufferMenosUno [10];

void evaluaPrimo(int number){
    if (number % prime != 0){
        char numberc [10];
        sprintf(numberc, "%d\t" ,number);
        write(1,numberc,sizeof(numberc));
    }
}


int main(int argc, char **argv){

    // buffer para numero primo
    char bufferPrimo [10];
    // escribir -1 en buffer menos uno
    sprintf(bufferMenosUno,"-1");
    // leemos lo que hay de primos
    read(0,bufferPrimo,sizeof(bufferPrimo));
    // convert a int
    prime = atoi(bufferPrimo);
    // si es menos uno el programa termina
    if (prime == -1){
        write(1,bufferMenosUno,sizeof(bufferMenosUno));
        return 0;
    }
    fprintf(stderr, "%s \n", bufferPrimo);
    while(1){

        // buffer numero a evaluar
        char numberc [10];
        read(0,numberc,sizeof(numberc));
        int number = atoi(numberc);

        if (number == -1){
            write(1,bufferMenosUno,sizeof(bufferMenosUno));
            return 0;
        }
        else{
            evaluaPrimo(number);
        }


    }

    return 0;
}