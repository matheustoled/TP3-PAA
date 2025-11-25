#ifndef COMANDOS_H_
#define COMANDOS_H_

#include "centralControle.h"

#define qtdLetras 26

// Função para codificar o texto
char *codifica(char *textoDescriptografado, long tamanhoTexto);

// Função para decodificar o texto
void decodifica();

// Função para apresentar o estado atual da criptoanálise
// void apresentarEstado(char *textoCriptografado, char *chave);

// Função para realizar a análise de frequência
void analiseFrequencia(char *textoCriptografado);

// Função para buscar padrão exato no texto criptografado
void casamentoExato(char *textoCriptografado);

// Função para casamento aproximado (Shift-And)
void casamentoAproximado(char *textoCriptografado);

// Função para alterar a chave de criptografia
void alterarChave(char *chave);

// Função para exportar o resultado
void exportarResultado(char *chave);

#endif