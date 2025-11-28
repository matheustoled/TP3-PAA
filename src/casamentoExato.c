#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

#include "./headers/casamentoExato.h"

// Função utilitária para obter o máximo entre dois inteiros
int maximo(int a, int b) { 
    return (a > b) ? a : b; 
}

// Função de pré-processamento para a heurística do caractere ruim de Boyer-Moore
// Preenche a tabela indicando a última ocorrência de cada caractere no padrão
void heuristicaCaractereRuim(char* padrao, int tamanho, 
    int tabelaCaractereRuim[NUM_CARACTERES]){
    int i;

    // Inicializa todas as ocorrências como -1
    for (i = 0; i < NUM_CARACTERES; i++)
        tabelaCaractereRuim[i] = -1;

    // Preenche com o valor da última ocorrência de um caractere
    for (i = 0; i < tamanho; i++)
        tabelaCaractereRuim[(int)padrao[i]] = i;
}

/* Função de busca de padrão usando o algoritmo de Boyer-Moore */
/* Retorna o número de ocorrências encontradas */
int buscarPadrao(char* texto, char* padrao){
    int m = strlen(padrao);
    int n = strlen(texto);
    int ocorrencias = 0;

    int tabelaCaractereRuim[NUM_CARACTERES];

    // Preenche o array de caracteres ruins (pré-processamento)
    heuristicaCaractereRuim(padrao, m, tabelaCaractereRuim);

    int s = 0; // s é o deslocamento do padrão em relação ao texto
    while (s <= (n - m)) {
        int j = m - 1;

        // Reduz o índice j do padrão enquanto os caracteres casam
        // com o texto na posição atual (s + j)
        while (j >= 0 && padrao[j] == texto[s + j])
            j--;

        // Se o padrão estiver presente no deslocamento atual (j < 0)
        if (j < 0) {
            ocorrencias++;
            
            // Imprimir a posição (índice) da ocorrência
            printf("Padrao encontrado na posicao: %d\n", s);

            /* Desloca o padrão para alinhar o próximo caractere do texto
               com a última ocorrência dele no padrão */
            // Verifica se s + m < n para não acessar memória fora do texto
            if (s + m < n) {
                s += m - tabelaCaractereRuim[(int)texto[s + m]];
            } else {
                s += 1;
            }
        }
        else {
            /* Desloca o padrão para alinhar o caractere ruim no texto
               com a última ocorrência dele no padrão */
            s += maximo(1, j - tabelaCaractereRuim[(int)texto[s + j]]);
        }
    }
    
    return ocorrencias;
}

// Função de interface para casamento exato (Chamada pelo menu)
void casamentoExato(char *textoCriptografado) {
    char padrao[256];

    // Solicita o padrão
    printf("Qual o padrao utilizado?\n> ");
    scanf("%s", padrao);

    // Converte o padrão para maiúsculas para bater com o texto criptografado
    for(int i = 0; padrao[i]; i++){
        padrao[i] = toupper(padrao[i]);
    }

    // Realiza a busca chamando a função traduzida
    int qtd = buscarPadrao(textoCriptografado, padrao);

    // Exibe o resultado conforme especificação
    printf("Ocorrencias: %d\n", qtd);
}