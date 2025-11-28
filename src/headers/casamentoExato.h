#ifndef CASAMENTO_H_
#define CASAMENTO_H_
#define ROSA "\x1b[38;5;218m"
#define RESET "\x1b[0m"
#define NUM_CARACTERES 256

//#include "frequencia.h"

// Função para realizar o casamento exato de caracteres no texto criptografado
void casamentoExato(char *textoCriptografado, int tamanhoTexto);

// Funções do algoritmo Boyer-Moore
int maximo(int a, int b);
void heuristicaCaractereRuim(char* padrao, int tamanho, int tabelaCaractereRuim[NUM_CARACTERES]);
int buscarPadrao(char* texto, char* padrao, int *indices);
float ContarPalavras(char *textoCriptografado);
float ContarLetras(char *textoCriptografado);

#endif