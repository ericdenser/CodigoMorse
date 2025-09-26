/*
 * PROJETO 1 - ALGORITMOS E PROGRAMAÇÃO II
 * Tradutor de Código Morse
 *
 * Grupo:
 * - Eric Denser Alencar - RA: 10737272
 *
*/

#include <stdio.h>
#include <string.h>

#define TAMANHO_MAXIMO 200

const char alfabetoLetras[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

const char *morseAlfabeto[] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", 
    "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", 
    "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." };

char traduzCodigo(const char *codigo) {
    for(int i = 0; i < 26; i++) { // loop principal, percorre cada um dos 26 possiveis códigos Morse
        int saoIguais = 1; // assumimos que sao iguais
        int k = 0; // indice k usado para comparar as strings caractere por caractere.

        //continua enquanto nao chegamos ao fim de ambas as strings
        while (codigo[k] != '\0' || morseAlfabeto[i][k] != '\0') {

            //se caracteres forem diferentes
            if (codigo[k] != morseAlfabeto[i][k]) {
                saoIguais = 0; // nao retorna letra
                break; // sai do loop atual
            }
            k++; // caso ambos caracteres sejam iguais, incrementa k e continua loop
        }
        if (saoIguais) {
            return alfabetoLetras[i];
        }
    }
}

void buscarPossiveisLetras(const char *codigo, char *possiveisLetras) {
    possiveisLetras[0] = '['; // inicia vetor abrindo colchete
    int possiveisLetrasIdx = 1; // primeiro indice comeca em 1 (0 é o colchete)

    for(int i = 0; i < 26; i++) { // loop principal, percorre cada um dos 26 códigos Morse
        int candidato = 1; // assumimos que pode ser uma possivel letra
        int k = 0; // indice k usado para comparar as strings caractere por caractere.

        while (codigo[k] != '\0') { // enquanto o vetor nao tiver encerrado

            //se o código do alfabeto for mais curto ou se os caracteres forem diferentes
            if (morseAlfabeto[i][k] == '\0' || codigo[k] != morseAlfabeto[i][k]) { 
                candidato = 0; // nao pode ser um candidato 
                break; // sai do loop atual, vai para proxima iteracao
            }
            k++; // caso ambos caracteres sejam iguais, incrementa k e continua loop atual
        }
        if (candidato) { // se apos todas comparacoes, continua sendo candidato
            possiveisLetras[possiveisLetrasIdx] = alfabetoLetras[i]; // armazena letra candidata no vetor 
            possiveisLetrasIdx++; // avanca indice do vetor
        }
    }
    possiveisLetras[possiveisLetrasIdx] = ']'; // fecha colchete no ultimo indice
    possiveisLetras[possiveisLetrasIdx + 1] = '\0'; // encerra vetor
}

void processaCodigoMorse(char *codigoMorse, char *codigoTraduzido, int tamanhoCodigo) {
    char letraAtual [10]; // vetor para validar letra por letra
    char possiveisLetras [30]; // vetor para armazenar possiveis letras
    int count = 0; // contador para o vetor 'letraAtual'
    int espacosConsecutivos = 0; // contador para espacos consecutivos

    codigoTraduzido[0] = '\0'; // inicia o vetor do codigo traduzido vazio

    for (int i = 0; i <= tamanhoCodigo; i++) { // loop principal passando por todos caracteres do codigo morse

        if (codigoMorse[i] == ' ' || codigoMorse[i] == '\0' || codigoMorse[i] == '*') { // caso pelo menos uma das condicoes seja verdadeira

            // se count for maior que 0, vetor 'letraAtual' armazenou pelo menos 1 caractere, ou primeira entrada foi um *
             if (count > 0 || (codigoMorse[i] == '*' && i < tamanhoCodigo) ) {

                // finaliza vetor para formar uma string valida
                letraAtual[count] = '\0';

                if (codigoMorse[i] == '*') { // se o gatilho foi *
                   
                    if (codigoMorse[i+1] == '\0' || codigoMorse[i+1] == ' ') {

                        buscarPossiveisLetras(letraAtual, possiveisLetras);
                        strcat(codigoTraduzido, possiveisLetras);

                    } else {
                        char codigoTemporario[10]; // rascunho para montar uma sequência de código morse 
                        char letrasEncontradas[10] = "";// armazenará as 2 possibilidades (* sendo . ou -)
                        int encontradasCount = 0; // contador para saber quantas letras válidas encontrou
                        int idxSufixo;// indice para fazer as comparacoes

                                

                        // 1 possibilidade (* sendo .)
                        strcpy(codigoTemporario, letraAtual); // copia o prefixo
                        strcat(codigoTemporario, ".");       // adiciona o '.'
                        idxSufixo = i + 1; // avanca 1 pois i atual era o *

                        int len = strlen(codigoTemporario);
                        
                        while (codigoMorse[idxSufixo] != '\0' && codigoMorse[idxSufixo] != ' ') {
                            codigoTemporario[len++] = codigoMorse[idxSufixo++];
                        }
                        codigoTemporario[len] = '\0'; // saiu do loop, finaliza vetor

                        // traduz a primeira possibilidade
                        char letra1 = traduzCodigo(codigoTemporario);

                        // 2 possibilidade (* sendo -)
                        strcpy(codigoTemporario, letraAtual); // copia o prefixo
                        strcat(codigoTemporario, "-");       // adiciona o '-'
                        idxSufixo = i + 1; // reinicia o indice do sufixo para a segunda busca

                        len = strlen(codigoTemporario);

                        while (codigoMorse[idxSufixo] != '\0' && codigoMorse[idxSufixo] != ' ') {
                            codigoTemporario[len++] = codigoMorse[idxSufixo++];
                        }
                        codigoTemporario[len] = '\0';

                        //traduz a segunda possiblidade
                        char letra2 = traduzCodigo(codigoTemporario);
                        
                        letrasEncontradas[encontradasCount++] = letra1;
                        letrasEncontradas[encontradasCount++] = letra2;
                        letrasEncontradas[encontradasCount] = '\0';
                        
                        if (encontradasCount > 0) {
                            char resultadoFinal[30];
                            sprintf(resultadoFinal, "[%s]", letrasEncontradas);
                            strcat(codigoTraduzido, resultadoFinal);
                        }
                        i = idxSufixo - 1;//volta o i
                    }
                    count = 0; // zera para a próxima letra
            
                } else { // senão, é uma tradução normal
                    char letraTraduzida = traduzCodigo(letraAtual); // traduz o trecho de codigo morse que vale como 1 letra

                    int ultimoIndice = strlen(codigoTraduzido); 
                    codigoTraduzido[ultimoIndice] = letraTraduzida; // armazena a letra traduzida no ultimo indice do vetor resultante
                    codigoTraduzido[ultimoIndice + 1] = '\0'; // encerra vetor

                }   
                count = 0; // reinicia contador
            }

            if (codigoMorse[i] == ' ') {
                espacosConsecutivos++;
                // Se for o segundo espaço seguido, adiciona um espaço na saída
                if (espacosConsecutivos == 2) {
                    strcat(codigoTraduzido, " ");
                }
            }
        } else { // se for '.' ou '-'
            espacosConsecutivos = 0; //nenhum espaco
            if (count < 4) { // nenhum codigo tem mais de 4 caracteres
                letraAtual[count] = codigoMorse[i]; // passa o caractere atual do codigo para nosso vetor que sera traduzido
                count++;
            }
        } 
    }
}

int main() {
    char codigoMorse[TAMANHO_MAXIMO]; // vetor para codigo morse de entrada
    char codigoTraduzido[TAMANHO_MAXIMO]; // vetor para o codigo final traduzido

    printf("Informe o codigo morse: ");
    fgets(codigoMorse, TAMANHO_MAXIMO, stdin); // armazena a entrada do teclado
    codigoMorse[strcspn(codigoMorse, "\n")] = 0; //remove caractere de nova linha

    processaCodigoMorse(codigoMorse, codigoTraduzido, strlen(codigoMorse)); // executa funcao
    printf("%s", codigoTraduzido);

    return 0;
}