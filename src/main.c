#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./headers/frequencia.h"
#include "./headers/casamentoExato.h"

int main() {
    char nomeArquivo[100];
    char *textoDescriptografado = NULL;
    char chave[26] = {0};
    char *chaveCriptografada = NULL;

    printf("Digite o nome do arquivo de texto descriptografado: ");
    scanf("%s", nomeArquivo);
    long tamanhoTexto = lerArquivo(nomeArquivo, &textoDescriptografado);
    
    char *textoCriptografado = codifica(textoDescriptografado, tamanhoTexto);

    int opcao;
    do {
        printf("\nSelecione uma operacao:\n");
        printf("1. Apresentar o estado atual da criptoanalise\n");
        printf("2. Fazer um chute baseado na analise de frequencia\n");
        printf("3. Realizar casamento exato de caracteres no texto criptografado\n");
        printf("4. Realizar casamento aproximado de caracteres no texto parcialmente decifrado\n");
        printf("5. Alterar chave de criptografia\n");
        printf("6. Exportar resultado e encerrar o programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                apresentarEstado(textoCriptografado, chave, chaveCriptografada);
                break;
            case 2:
                chaveCriptografada = analiseFrequencia(textoCriptografado);
                break;
            case 3:
                casamentoExato(textoCriptografado);
                break;
            case 4:
                printf("Funcionalidade em desenvolvimento.\n");
                //casamentoAproximado(textoDescriptografado);
                break;
            case 5:
                printf("Funcionalidade em desenvolvimento.\n");
                //alterarChave(chave);
                break;
            case 6:
                printf("Funcionalidade em desenvolvimento.\n");
                //exportarResultado(chave);
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 6);

    free(textoDescriptografado);
    free(textoCriptografado);

    return 0;
}
