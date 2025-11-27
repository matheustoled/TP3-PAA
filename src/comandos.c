#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./headers/comandos.h"

// Função para codificar o texto
char *codifica(char *textoDescriptografado, long tamanhoTexto){

    char *textoCriptografado = (char *)malloc(tamanhoTexto + 1);
    if (textoCriptografado == NULL) {
        printf("Erro ao alocar memória para o texto criptografado.\n");
        exit(1);
    }

    int i = 0, j = 0;
    char vetLetras[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                           'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

    for (i = 0; i < tamanhoTexto; i++){
        if ((textoDescriptografado[i] >= 'A' && textoDescriptografado[i] <= 'Z')) {
            for (j = 0; j < qtdLetras; j++){
                if(textoDescriptografado[i] == vetLetras[j]) {
                    textoCriptografado[i] = vetLetras[(j + 3) % 26];
                }
            }
        } else {
            textoCriptografado[i] = textoDescriptografado[i];
        }
    }
    printf("\n=== Texto Descriptografado ===\n");
    printf("\nTexto Criptografado (Debug): %s\n", textoDescriptografado);
    printf("\n=== Texto Criptografado ===\n");
    for (int i = 0; textoCriptografado[i] != '\0'; i++) {
        printf("%c", textoCriptografado[i]);
    }
    printf("\n");

    return textoCriptografado;
}

// Função para decodificar o texto
void decodifica(){
    
}

// Função para apresentar o estado atual da criptoanálise
// void apresentarEstado(char *textoDescriptografado, char *chave) {
//     printf("=== Texto descriptografado ===\n");
//     printf("%s\n", textoDescriptografado);
//     
//     printf("\n=== Chave ===\n");
//     for (int i = 0; i < 26; i++) {
//         printf("%c -> %c\n", 'A' + i, chave[i] ? chave[i] : '-');
//     }
// }

// Função para realizar a análise de frequência
void analiseFrequencia(char *textoDescriptografado) {
    //TODO: Fazer funcao de calculo de frequencia de letras
    printf("\nAnálise de Frequência - Não implementado ainda.\n");
}

// Função para buscar padrão exato no texto criptografado
void casamentoExato(char *textoDescriptografado) {
    char padrao[100];
    printf("\nDigite o padrão para busca exata: ");
    scanf("%s", padrao);

    //TODO: Fazer funcao de algoritmo de casamento de padroes, como KMP
    printf("Busca exata de '%s' no texto: Não implementado ainda.\n", padrao);
}

// Função para casamento aproximado
void casamentoAproximado(char *textoDescriptografado) {
    char padrao[100];
    int tolerancia;
    printf("\nDigite o padrão para busca aproximada: ");
    scanf("%s", padrao);
    printf("Digite a tolerância (número de erros permitidos): ");
    scanf("%d", &tolerancia);

    // TODO: Implementação do algoritmo casamento aproximado
    printf("Busca aproximada de '%s' com tolerância %d: Não implementado ainda.\n", padrao, tolerancia);
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
    for (int i = 0; i < 26; i++) {
        fprintf(arquivo, "%c -> %c\n", 'A' + i, chave[i] ? chave[i] : '-');
    }

    fclose(arquivo);
    printf("Resultado exportado para 'chave_criptografica.txt'.\n");
}