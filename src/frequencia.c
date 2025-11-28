#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./headers/frequencia.h"

char tabelaPortugues[26] = {
    'A','E','O','S','R','I','N','D','M','U',
    'T','C','L','P','V','G','H','Q','B','F',
    'Z','J','X','K','Y','W'
};

// Função de comparação para ordenação das frequências (ordem decrescente)
int compararFrequencias(const void *a, const void *b) {
    FrequenciaLetra *letraA = (FrequenciaLetra *)a;
    FrequenciaLetra *letraB = (FrequenciaLetra *)b;

    if (letraA->freqRelativa < letraB->freqRelativa) {
        return 1;
    } else if (letraA->freqRelativa > letraB->freqRelativa) {
        return -1;
    }
    return 0;
}

// Função para contar frequências e exibir resultados
char *analiseFrequencia(char *textoCriptografado) {
    int frequencia[qtdLetras] = {0};
    int totalLetras = 0;

    // Contando a frequência das letras
    for (int i = 0; textoCriptografado[i] != '\0'; i++) {
        char c = textoCriptografado[i];
        if (c >= 'A' && c <= 'Z') {
            frequencia[c - 'A']++;  // Incrementa a frequência da letra
            totalLetras++;
        }
    }

    // Criar um vetor de estruturas para armazenar as letras e suas frequências
    FrequenciaLetra letras[qtdLetras];
    for (int i = 0; i < qtdLetras; i++) {
        letras[i].letra = 'A' + i;
        letras[i].contagem = frequencia[i];
        letras[i].freqRelativa = (float)frequencia[i] / totalLetras * 100;
    }

    // Ordenando as letras com base na frequência relativa
    qsort(letras, qtdLetras, sizeof(FrequenciaLetra), compararFrequencias);

    // Exibindo as frequências absolutas e relativas ordenadas
    printf("\n--- Frequencia das letras ---\n");
    printf("Letra\tCont.\tFreq.\n");
    for (int i = 0; i < qtdLetras; i++) {
        if (letras[i].contagem > 0) {
            printf("%c\t%d\t%.2f%%\n", letras[i].letra, letras[i].contagem, letras[i].freqRelativa);
        }
    }

    char *chaveCriptografada = (char *)malloc(qtdLetras * sizeof(char));
    
    for (int i = 0; i < qtdLetras; i++) {
        chaveCriptografada[letras[i].letra - 'A'] = tabelaPortugues[i];
    }

    chaveCriptografada[qtdLetras] = '\0';

    printf("\n--- chaveCriptografada ---\n");
    for (int i = 0; i < qtdLetras; i++) {
        printf("%c ", 'A' + i);
    }
    printf("\n");
    for (int i = 0; i < qtdLetras; i++) {
        printf("%c ", chaveCriptografada[i]);
    }
    printf("\n");

    return chaveCriptografada;
}