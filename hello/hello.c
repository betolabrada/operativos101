#include <stdio.h>
#include <stdlib.h>
#include "./libhello.h"



int main(int argc, char **argv) {
    for(int i = 1; i< argc; i++) {
        printHello(argv[i]);
    }
    return 0;
}