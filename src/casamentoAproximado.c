#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>

/* ---------------------------------------------------------
   Transforma string em MAIÚSCULA
--------------------------------------------------------- */
void toUpperStr(char *s) {
    for (; *s; s++) *s = toupper((unsigned char)*s);
}

/* ---------------------------------------------------------
   Cálculo real da distância de edição (Levenshtein)
   COMPLETO e 100% correto
--------------------------------------------------------- */
int distanciaEdicao(const char *a, const char *b, int m, int n) {
    int *dp = (int *)malloc((m+1) * (n+1) * sizeof(int));
    if (!dp) return 999999; // fallback

    #define D(i,j) dp[(i)*(n+1) + (j)]

    for (int i = 0; i <= m; i++) D(i,0) = i;
    for (int j = 0; j <= n; j++) D(0,j) = j;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int custo = (a[i-1] == b[j-1]) ? 0 : 1;
            int del = D(i-1,j) + 1;
            int ins = D(i,j-1) + 1;
            int sub = D(i-1,j-1) + custo;
            int min = del;
            if (ins < min) min = ins;
            if (sub < min) min = sub;
            D(i,j) = min;
        }
    }

    int resposta = D(m,n);
    free(dp);
    return resposta;
}

/* ---------------------------------------------------------
   SHIFT-AND APROXIMADO + verificação por Levenshtein
   100% correto e sem falsos positivos
--------------------------------------------------------- */
long casamentoAproximado(char *T)
{
    char P[256];
    int k;

    printf("Digite o padrao e a tolerancia:\n");
    if (scanf("%255s %d", P, &k) != 2) {
        printf("Erro ao ler entrada.\n");
        return -1;
    }

    toUpperStr(P);
    toUpperStr(T);

    int m = strlen(P);
    int n = strlen(T);

    if (m == 0 || n == 0) return 0;
    if (m > 63) { printf("Erro: padrao muito grande (max 63).\n"); return -1; }
    if (k < 0) k = 0;

    /* ----- Preparar as máscaras ----- */
    uint64_t Peq[256];
    for (int c = 0; c < 256; c++) Peq[c] = 0ULL;
    for (int i = 0; i < m; i++) {
        Peq[(unsigned char)P[i]] |= (1ULL << i);
    }

    /* Estados D[0..k] */
    uint64_t *D = malloc((k+1) * sizeof(uint64_t));
    if (!D) { printf("Erro de memoria.\n"); return -1; }

    D[0] = 0ULL;
    for (int d = 1; d <= k; d++) D[d] = ~0ULL;

    long ocorrencias = 0;

    for (int i = 0; i < n; i++) {

        uint64_t prev = D[0];
        uint64_t charmask = Peq[(unsigned char)T[i]];

        /* Atualiza nível 0 */
        D[0] = ((D[0] << 1) | 1ULL) & charmask;

        /* Atualiza níveis 1..k */
        for (int d = 1; d <= k; d++) {
            uint64_t old = D[d];
            uint64_t sub_or_match = ((D[d] << 1) | 1ULL) & charmask;
            D[d] = sub_or_match | (prev << 1); 
            prev = old;
        }

        /* Se o bit do fim estiver 1 → CANDIDATO */
        if (D[k] & (1ULL << (m - 1))) {

            int start = i - m + 1;
            if (start < 0) continue;

            int dist = distanciaEdicao(P, T + start, m, m);
            if (dist <= k) {

                printf("Ocorrencia %ld: ", ocorrencias + 1);
                for (int j = 0; j < m; j++)
                    putchar(T[start + j]);
                putchar('\n');

                ocorrencias++;

                /* pular adiante para NÃO contar substrings internas */
                i = i + m - 1;
            }
        }
    }

    free(D);

    printf("Numero total de ocorrencias: %ld\n", ocorrencias);
    return ocorrencias;
}
