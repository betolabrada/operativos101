
#include <stdio.h>
#include <unistd.h>

// generar numeros del 2 al 100;

int main(int argc, char **argv)
{
    char prueba[10];
    char arr[10];

    // caso base
    sprintf(arr,"-1");

    for (int i = 2; i <= 100; i++)
    {
        sprintf(prueba, "%d", i);
        write(1, prueba, sizeof(prueba));
    }
    write(1, arr, sizeof(arr));
    return 0;
}