
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *current_dir = getenv("PWD");
    if (current_dir)
        printf("Diretório atual: %s\n", current_dir);
    else
        printf("Variável PWD não encontrada.\n");

    return 0;
}
