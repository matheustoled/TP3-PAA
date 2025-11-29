#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#include "./headers/frequencia.h"

int max(int a, int b) { return (a > b) ? a : b; }

// Função para codificar o texto
char *codifica(char *textoDescriptografado, long tamanhoTexto){

    char *textoCriptografado = (char *)malloc(tamanhoTexto + 1);
    if (textoCriptografado == NULL) {
        printf("Erro ao alocar memória para o texto criptografado.\n");
        exit(1);
    }

    srand(time(NULL));
    
    int deslocamento = rand() % 25 + 1;

    int i = 0, j = 0;
    char vetLetras[qtdLetras] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                                'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
    char vetAcentos[] = {',', '.', '"', '-', '?', '!', ';', ':', '_'};

    for(i = 0; i < tamanhoTexto; i++){
        char c = textoDescriptografado[i];
        int ehPontuacao = 0;

        for (j = 0; j < sizeof(vetAcentos); j++) {
            if (c == vetAcentos[j]) {
                ehPontuacao = 1;
                break;
            }
        }

        if (c >= 'A' && c <= 'Z') {
            for (j = 0; j < qtdLetras; j++){
                if(textoDescriptografado[i] == vetLetras[j]) {
                    textoCriptografado[i] = vetLetras[(j + deslocamento) % qtdLetras];
                }
            }
        }
        else if (ehPontuacao){
            textoCriptografado[i] = ' ';
        }
        else{
            textoCriptografado[i] = ' ';
        }
    }

    textoCriptografado[tamanhoTexto] = '\0';

    printf("\n--- Texto Criptografado ---\n");
    for (int i = 0; textoCriptografado[i] != '\0'; i++) {
        printf("%c", textoCriptografado[i]);
    }
    printf("\n");

    return textoCriptografado;
}

void apresentarEstado(char *textoCriptografado, char *chave, char *chaveCriptografada) {
    // Exibe o texto criptografado
    printf("\n--- Texto Criptografado ---\n");
    printf("%s\n", textoCriptografado);

    // Exibe a chave de criptografia
    printf("\n--- Chave ---\n");
    for (int i = 0; i < qtdLetras; i++) {
        printf("%c ", 'A' + i);
    }
    printf("\n");
    if(chaveCriptografada != NULL) {
        for (int i = 0; i < qtdLetras; i++) {
            printf("%c ", chaveCriptografada[i]);
        }
    }
    printf("\n");

    // Exibe o texto descriptografado utilizando a chave mapeada
    printf("\n--- Texto Descriptografado ---\n");
    if (chaveCriptografada != NULL){
        for (int i = 0; textoCriptografado[i] != '\0'; i++) {
            char c = textoCriptografado[i];

            if (c >= 'A' && c <= 'Z'){
                char decifrada = chaveCriptografada[c - 'A'];

                // Se essa letra já foi descoberta (mapeada), pinte!
                if (decifrada != '?') { 
                    printf("%s%c%s", ROSA, decifrada, RESET);
                } else {
                    // Letra ainda não descoberta
                    printf("%c", c);
                }
            }
            else{
                printf("%c", c);
            }
        }
        printf("\n");
    }
    else{
        printf("%s\n", textoCriptografado);
    }

    printf("\n");
}

// Função para alterar a chave de criptografia
void alterarChave(char *chave, char* chaveCriptografada, char *textoCriptografado){
    char original, mapeada;
    printf("\nInforme a letra original, seguida da letra para a qual foi mapeada:\n> ");
    scanf(" %c %c", &original, &mapeada);

    int idx = original - 'A';

    chave[idx] = mapeada;
    chaveCriptografada[idx] = mapeada;

    printf("Registrado: %c -> %c\n", original, mapeada);

    printf("\n--- Chave ---\n");
    for (int i = 0; i < qtdLetras; i++) {
        if (i == idx) {
            printf("%s%c%s ", ROSA, 'A' + i, RESET);
        } else {
            printf("%c ", 'A' + i);
        }
    }
    printf("\n");

    for (int i = 0; i < qtdLetras; i++) {
        char out = (chaveCriptografada[i] >= 'A' && chaveCriptografada[i] <= 'Z')
                    ? chaveCriptografada[i]
                    : '-';
        if (i == idx) {
            printf("%s%c%s ", ROSA, out, RESET);
        } else {
            printf("%c ", out);
        }
    }
    printf("\n");
}


// Função para exportar o resultado
void exportarResultado(char *chave, char *textoCriptografado, char *chaveCriptografada){
    char nomeArquivo[100];
    printf("Digite o nome do arquivo onde deseja salvar as informacoes:");
    scanf("%s", nomeArquivo);
    char caminhoCompleto[200];
    sprintf(caminhoCompleto, "./output/%s", nomeArquivo);
    FILE *arquivo = fopen(caminhoCompleto, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para exportar a chave.\n");
        return;
    }
    fprintf(arquivo,"\nTexto Criptografado:\n");
    fprintf(arquivo, "%s", textoCriptografado);

    fprintf(arquivo, "\nChave de criptografia:\n");
    for (int i = 0; i < qtdLetras; i++) {
        char letraDecodificada = chaveCriptografada[i];

        if (letraDecodificada < 'A' || letraDecodificada > 'Z') {
            letraDecodificada = '-';  // posição ainda não descoberta
        }
        fprintf(arquivo, "%c -> %c\n", 'A' + i, letraDecodificada);
    }

    fprintf(arquivo,"\nTexto Descriptografado:\n");
    if (chaveCriptografada != NULL){
        for (int i = 0; textoCriptografado[i] != '\0'; i++) {
            char c = textoCriptografado[i];

            if (c >= 'A' && c <= 'Z'){
                char decifrada = chaveCriptografada[c - 'A'];
                if (decifrada != '?') { 
                    fprintf(arquivo, "%c", decifrada);
                }
            }
            else{
                fprintf(arquivo, "%c", c);
            }
        }
        fprintf(arquivo, "\n");
    }
    else{
        fprintf(arquivo, "%s", textoCriptografado);
    }
}