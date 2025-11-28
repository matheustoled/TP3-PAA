
#ifndef FREQUENCIA_H_  
#define FREQUENCIA_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comandos.h"

typedef struct {
    char letra;
    int contagem;
    float freqRelativa;
} FrequenciaLetra;

// Função de comparação para ordenação das frequências (ordem decrescente)
int compararFrequencias(const void *a, const void *b);

// Função para contar frequências e exibir resultados
char *analiseFrequencia(char *textoCriptografado);

#endif // FREQUENCIA_H_