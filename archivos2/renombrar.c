#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *file1 = argv[1];
    char *file2 = argv[2];
    char *pwd = getcwd(NULL,0);
    char path1[strlen(file1) + strlen(pwd) + 2]; // por / y null char '\0'
    char path2[strlen(file2) + strlen(pwd) + 2];
    sprintf(path1, "%s/%s",pwd,file1);
    sprintf(path2, "%s/%s",pwd,file2);


    // printf("pwd %s\n", path1);
    // printf("pwd %s\n", path2);

    int linkeado = link(path1, path2);

    if (linkeado == 0)
    {
        printf("linked successfully\n");
    }
    else 
    {
        printf("Hay un problema con linkeo\n");
    }

    int unlinkeado = unlink(path1);

    if (unlinkeado == 0)
    {
        printf("Renombrado exitosamente %s a %s \n", file1, file2);
    }
    else {
        printf("Hay un problema\n");
    }
    

    
}