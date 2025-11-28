#ifndef COMANDOS_H_
#define COMANDOS_H_

#include "centralControle.h"

#define qtdLetras 26

// Função para codificar o texto
char *codifica(char *textoDescriptografado, long tamanhoTexto);

void apresentarEstado(char *textoCriptografado, char *chave, char *chaveCriptografada);

// Função para alterar a chave de criptografia
void alterarChave(char *chave);

// Função para exportar o resultado
void exportarResultado(char *chave);

#endif