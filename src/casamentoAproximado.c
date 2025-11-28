#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <ctype.h>

void toUpperStr(char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
        s[i] = toupper((unsigned char)s[i]);
    }
}


long casamentoAproximado(char *T)
{
    char P[256];

    int k;

    printf("Digite o padrao e a tolerancia desejada:\n");
    if (scanf("%255s %d", P, &k) != 2) {
        printf("Erro ao ler padrao e tolerancia.\n");
        return -1;
    }

    toUpperStr(P);

    int m = (int)strlen(P);
    int n = (int)strlen(T);

    if (m == 0 || n == 0) {
        printf("Padrao ou texto vazio.\n");
        return 0;
    }

    if (m > 63) {
        printf("Erro: padrao muito grande (max 63 chars).\n");
        return -1;
    }

    if (k < 0) k = 0;
    if (k > 63) k = 63; 

    uint64_t Peq[256];
    for (int c = 0; c < 256; ++c) Peq[c] = 0ULL;
    for (int i = 0; i < m; ++i) {
        unsigned char c = (unsigned char)P[i];
        Peq[c] |= (1ULL << i); 
    }

    uint64_t *D = (uint64_t*)malloc((size_t)(k + 1) * sizeof(uint64_t));
    if (!D) { printf("Erro de memoria.\n"); return -1; }

    uint64_t ALL_ONES = ~0ULL;

    D[0] = 0ULL;
    for (int d = 1; d <= k; ++d) D[d] = ALL_ONES;

    long ocorrencias = 0;

    for (int i = 0; i < n; ++i) {
        unsigned char tc = (unsigned char)T[i];
        uint64_t pc = Peq[tc];

        uint64_t prev = D[0];

        D[0] = ((D[0] << 1) | 1ULL) & pc;

        for (int d = 1; d <= k; ++d) {
            uint64_t old = D[d];
            uint64_t shifted_match = ((D[d] << 1) | 1ULL) & pc;
            D[d] = shifted_match | (prev << 1); 
            prev = old;
        }

        if ((D[k] & (1ULL << (m - 1))) != 0) {
            int start = i - m + 1;
            if (start < 0) start = 0; 
            printf("Ocorrencia %ld: ", ocorrencias + 1);
            for (int j = 0; j < m && start + j < n; ++j)
                putchar(T[start + j]);
            putchar('\n');

            ocorrencias++;
        }
    }

    free(D);

    printf("Numero total de ocorrencias: %ld\n", ocorrencias);
    return ocorrencias;
}
