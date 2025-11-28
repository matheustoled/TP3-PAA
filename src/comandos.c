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

    for (i = 0; i < tamanhoTexto; i++){
        if ((textoDescriptografado[i] >= 'A' && textoDescriptografado[i] <= 'Z')) {
            for (j = 0; j < qtdLetras; j++){
                if(textoDescriptografado[i] == vetLetras[j]) {
                    textoCriptografado[i] = vetLetras[(j + deslocamento) % qtdLetras];
                }
            }
        } else {
            textoCriptografado[i] = textoDescriptografado[i];
        }
    }
    // printf("\n=== Texto Criptografado ===\n");
    // for (int i = 0; textoCriptografado[i] != '\0'; i++) {
    //     printf("%c", textoCriptografado[i]);
    // }
    // printf("\n");

    return textoCriptografado;
}

void apresentarEstado(char *textoCriptografado, char *chave, char *chaveCriptografada) {
    // Exibe o texto criptografado
    printf("=== Texto Criptografado ===\n");
    printf("%s\n", textoCriptografado);

    // Exibe a chave de criptografia
    printf("\n=== Chave ===\n");
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
    printf("\n=== Texto Descriptografado ===\n");
    if(chaveCriptografada == NULL) {
        printf("%s\n", textoCriptografado);
    } else if (chaveCriptografada != NULL) {
        for (int i = 0; textoCriptografado[i] != '\0'; i++) {
            char c = textoCriptografado[i];
            if (c >= 'A' && c <= 'Z') {
                printf("%c", chaveCriptografada[c - 'A']);
            } else {
                printf("%c", c);
            }
        }
    }
    printf("\n");
}

// Função para alterar a chave de criptografia
void alterarChave(char *chave) {
    char original, mapeada;
    printf("\nInforme a letra original e a letra mapeada (exemplo: A S): ");
    scanf(" %c %c", &original, &mapeada);

    // TODO: Fazer funcao de atualizacao da chave de criptografia
    chave[original - 'A'] = mapeada;
    printf("Registrado: %c -> %c\n", original, mapeada);
}

// TODO: Função para exportar o resultado
void exportarResultado(char *chave) {
    FILE *arquivo = fopen("chave_criptografica.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para exportar a chave.\n");
        return;
    }

    fprintf(arquivo, "Chave de criptografia:\n");
    for (int i = 0; i < qtdLetras; i++) {
        fprintf(arquivo, "%c -> %c\n", 'A' + i, chave[i] ? chave[i] : '-');
    }

    fclose(arquivo);
    printf("Resultado exportado para 'chave_criptografica.txt'.\n");
}