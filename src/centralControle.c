#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "./headers/frequencia.h"

void removerAcentos(char *str) {
    char temp[strlen(str) + 1];
    int j = 0;
    int i = 0;

    while (str[i] != '\0') {
        unsigned char c = str[i];

        if (c < 128) {
            if (c >= 'a' && c <= 'z') {
                temp[j++] = c - 32;
            }
            else if (c == ' ' || c == '.' || c == ',' || c == ':' || c == ';' ||
                     c == '?' || c == '!' || c == '"' || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                temp[j++] = c;
            }
            else {
                i++;
                continue;
            }
        } 
        else if (c == 0xC3) {
            unsigned char n = str[i + 1];
            switch (n) {
                case 0xA0: case 0xA1: case 0xA2: case 0xA3: case 0xA4:  // á, à, â, ã, á
                    temp[j++] = 'A'; break;
                case 0xA8: case 0xA9: case 0xAA: case 0xAB:  // é, è, ê, ë
                    temp[j++] = 'E'; break;
                case 0xAC: case 0xAD: case 0xAE: case 0xAF:  // í, ì, î, ï
                    temp[j++] = 'I'; break;
                case 0xB2: case 0xB3: case 0xB4: case 0xB5: case 0xB6:  // ó, ò, ô, õ, ó
                    temp[j++] = 'O'; break;
                case 0xB9: case 0xBA: case 0xBB: case 0xBC:  // ú, ù, û, ü
                    temp[j++] = 'U'; break;
                case 0xA7:  // ç
                    temp[j++] = 'C'; break;
                case 0xB1:  // ñ
                    temp[j++] = 'N'; break;
                default:
                    temp[j++] = str[i];
                    break;
            }
            i += 2;
            continue;
        } 
        else {
            i++;
            continue;
        }

        i++;
    }

    temp[j] = '\0';
    strcpy(str, temp);
}

// Função para ler o arquivo de texto criptografado usando alocação dinâmica
long lerArquivo(char *nomeArquivo, char **textoDescriptografado) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        exit(1);
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET); // Volta ao início do arquivo

    *textoDescriptografado = (char *)malloc(tamanho + 1);  // +1 para o terminador '\0'
    if (*textoDescriptografado == NULL) {
        printf("Erro ao alocar memória para o texto descriptografado.\n");
        fclose(arquivo);
        exit(1);
    }

    fread(*textoDescriptografado, 1, tamanho, arquivo);
    (*textoDescriptografado)[tamanho] = '\0';
    fclose(arquivo);

    removerAcentos(*textoDescriptografado);

    for (long i = 0; i < tamanho; i++) {
        (*textoDescriptografado)[i] = toupper((*textoDescriptografado)[i]);
    }

    return tamanho;
}