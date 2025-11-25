#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "./headers/comandos.h"

// Função para remover acentos de caracteres
void removerAcentos(char *str) {
    char temp[strlen(str) + 1];
    int j = 0;

    for (int i = 0; str[i] != '\0'; ) {
        unsigned char c = str[i];

        // Se for ASCII puro (0–127)
        if (c < 128) {

            // Converte para MAIÚSCULO se for letra minúscula
            if (c >= 'a' && c <= 'z')
                temp[j++] = c - 32;

            // Mantém letras maiúsculas e pontuação
            else if ((c >= 'A' && c <= 'Z') ||
                     c == ' ' || c == '.' || c == ',' ||
                     c == ':' || c == ';' || c == '?' ||
                     c == '!' || c == '"')
                temp[j++] = c;

            // Ignora caracteres esquisitos
            else
                ; // descarta

            i++;
            continue;
        }

        // UTF-8 acentuado
        // mapeamos MANUALMENTE o segundo byte
        if (c == 0xC3) {
            unsigned char n = str[i + 1];
            switch (n) {
                case 0xA0: case 0xA1:
                case 0xA2: case 0xA3:
                case 0xA4:
                    temp[j++] = 'A'; break;

                case 0xA8: case 0xA9:
                case 0xAA: case 0xAB:
                    temp[j++] = 'E'; break;

                case 0xAC: case 0xAD:
                case 0xAE: case 0xAF:
                    temp[j++] = 'I'; break;

                case 0xB2: case 0xB3:
                case 0xB4: case 0xB5:
                case 0xB6:
                    temp[j++] = 'O'; break;

                case 0xB9: case 0xBA:
                case 0xBB: case 0xBC:
                    temp[j++] = 'U'; break;

                case 0xA7:
                    temp[j++] = 'C'; break;

                case 0xB1:
                    temp[j++] = 'N'; break;
            }

            i += 2;
            continue;
        }

        // QUALQUER OUTRO UTF-8: descarta
        // (emoji entra aqui)
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

    *textoDescriptografado = (char *)malloc(tamanho + 1);
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