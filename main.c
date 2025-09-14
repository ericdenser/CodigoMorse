#include <stdio.h>
#include <string.h>

#define TAMANHO_MAXIMO 200

int main() {
    char codigoMorse[TAMANHO_MAXIMO];


    printf("Informe o código morse: ");
    fgets(codigoMorse, TAMANHO_MAXIMO, stdin);
    codigoMorse[strcspn(codigoMorse, "\n")] = 0;

    int tamanho = strlen(codigoMorse);
    printf("%d", tamanho);
    printf("%s", codigoMorse);

}