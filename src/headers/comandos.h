#ifndef COMANDOS_H_
#define COMANDOS_H_
#define ROSA "\x1b[38;5;218m"
#define RESET "\x1b[0m"
#include "centralControle.h"

#define qtdLetras 26

// Função para codificar o texto
char *codifica(char *textoDescriptografado, long tamanhoTexto);

void apresentarEstado(char *textoCriptografado, char *chave, char *chaveCriptografada, char *textoParcialmenteDescriptografada);

// Função para alterar a chave de criptografia
void alterarChave(char *chave, char* chaveCriptografada, char *textoCriptografado);

// Função para exportar o resultado
void exportarResultado(char *chave, char *textoCriptografado, char *chaveCriptografada);

#endif