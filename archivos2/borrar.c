#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *file1 = argv[1];
    char *pwd = getcwd(NULL,0);
    char path1[strlen(file1) + strlen(pwd) + 2]; // por / y null char '\0'
    sprintf(path1, "%s/%s",pwd,file1);


    // printf("pwd %s\n", path1);


    int deleteFile = unlink(path1);

    if (deleteFile == 0)
    {
        printf("Archivo %s borrado exitosamente\n", file1);
    }
    else 
    {
        printf("Hay un problema\n");
    }
    return 0;
}