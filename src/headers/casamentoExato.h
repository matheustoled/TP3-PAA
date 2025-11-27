#ifndef CASAMENTO_H_
#define CASAMENTO_H_

#define NO_OF_CHARS 256

#include "frequencia.h"

int max(int a, int b);

void badCharHeuristic(char* str, int size, int badchar[NO_OF_CHARS]);

void search(char* txt, char* pat);

#endif