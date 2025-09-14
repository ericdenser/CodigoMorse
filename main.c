#include <stdio.h>
#include <string.h>

#define TAMANHO_MAXIMO 200

const char alfabetoLetras[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

const char *morseAlfabeto[] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", 
    "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", 
    "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." };

char traduzCodigo(const char *codigo) {
    for(int i = 0; i < 26; i++) { // loop principal, percorre cada um dos 26 códigos Morse
        int saoIguais = 1; // assumimos que sao iguais
        int k = 0; // indice k usado para comparar as strings caractere por caractere.

        //enquanto algum dos vetores ainda nao tiver terminado
        while (codigo[k] != '\0' || morseAlfabeto[i][k] != '\0') {

            //compara caracteres
            if (codigo[k] != morseAlfabeto[i][k]) {
                saoIguais = 0; // nao retorna letra
                break; // sai do loop atual, vai para proxima iteracao
            }
            k++; // caso ambos caracteres sejam iguais, incrementa k e continua loop
        }
        if (saoIguais) {
            return alfabetoLetras[i];
        }
    }
}

void processaCodigoMorse(char *codigoMorse, char *codigoTraduzido, int tamanhoCodigo) {
    char letraAtual [5];
    //char possiveisLetras [26];
    int count = 0;
    int indiceTraduzido = 0;

    for (int i = 0; i <= tamanhoCodigo; i++) {

        if (codigoMorse[i] == ' ' || codigoMorse[i] == '\0') {

            if (count > 0) {
                letraAtual[count] = '\0';

                codigoTraduzido[indiceTraduzido] = traduzCodigo(letraAtual);

                if (codigoMorse[i + 1] == ' ') {
                    codigoTraduzido[indiceTraduzido + 1] = ' ';
                    indiceTraduzido += 2;
                } else {
                    indiceTraduzido++;
                }

                count = 0;
            }

        } else {
            if (count < 4) {
                letraAtual[count] = codigoMorse[i];

                count++;
            }
        }
        
    }
    codigoTraduzido[indiceTraduzido] = '\0';
}

int main() {
    char codigoMorse[TAMANHO_MAXIMO];
    char codigoTraduzido[TAMANHO_MAXIMO];

    printf("Informe o código morse: ");
    fgets(codigoMorse, TAMANHO_MAXIMO, stdin); // armazena a entrada do teclado
    codigoMorse[strcspn(codigoMorse, "\n")] = 0; //remove caractere de nova linha

    processaCodigoMorse(codigoMorse, codigoTraduzido, strlen(codigoMorse));
    printf("%s", codigoTraduzido);

}