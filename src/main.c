#include "ordenacao.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QTD_PRECOS 10

static void imprimir_lista(const char *titulo,
                           const double *valores,
                           size_t n,
                           const MetricasOrdenacao *m) {
    printf("====================================================\n");
    printf(" %s\n", titulo);
    printf("====================================================\n");
    for (size_t i = 0; i < n; i++) {
        printf("Posicao [%02zu]: R$ %6.2f\n", i + 1, valores[i]);
    }
    if (m != NULL) {
        printf("----------------------------------------------------\n");
        printf("Metricas -> passagens: %zu | comparacoes: %zu | trocas: %zu\n",
               m->passagens, m->comparacoes, m->trocas);
    }
    printf("====================================================\n\n");
}

int main(void) {
    const double precos_originais[QTD_PRECOS] = {
        28.50, 14.90, 5.75, 42.00, 19.99,
        8.40,  65.30, 12.25, 33.80, 9.90
    };

    double crescente[QTD_PRECOS];
    double decrescente[QTD_PRECOS];
    memcpy(crescente, precos_originais, sizeof(precos_originais));
    memcpy(decrescente, precos_originais, sizeof(precos_originais));

    printf("\n====================================================\n");
    printf("   ORDENACAO DE PRECOS DE SUPERMERCADO (BUBBLE)     \n");
    printf("====================================================\n\n");

    imprimir_lista("LISTA ORIGINAL (PRESERVADA SEM MUTACAO)", precos_originais, QTD_PRECOS, NULL);

    MetricasOrdenacao m_cresc;
    bubble_sort_precos(crescente, QTD_PRECOS, ORDEM_CRESCENTE, &m_cresc);
    imprimir_lista("ORDEM CRESCENTE (MENOR -> MAIOR)", crescente, QTD_PRECOS, &m_cresc);

    MetricasOrdenacao m_decr;
    bubble_sort_precos(decrescente, QTD_PRECOS, ORDEM_DECRESCENTE, &m_decr);
    imprimir_lista("ORDEM DECRESCENTE (A PARTIR DO ORIGINAL)", decrescente, QTD_PRECOS, &m_decr);

    /* Demonstracao empirica de melhor caso O(n) vs pior caso O(n^2) com n = 10 */
    MetricasOrdenacao m_melhor;
    bubble_sort_precos(crescente, QTD_PRECOS, ORDEM_CRESCENTE, &m_melhor);

    double pior_caso[QTD_PRECOS];
    memcpy(pior_caso, crescente, sizeof(crescente));
    MetricasOrdenacao m_pior;
    bubble_sort_precos(pior_caso, QTD_PRECOS, ORDEM_DECRESCENTE, &m_pior);

    printf("-------------- ANALISE EMPIRICA (n = %d) ------------\n", QTD_PRECOS);
    printf("Melhor caso O(n)   [ja ordenado] : %2zu comparacoes | %2zu trocas | %zu passagem\n",
           m_melhor.comparacoes, m_melhor.trocas, m_melhor.passagens);
    printf("Pior caso   O(n^2) [invertido]   : %2zu comparacoes | %2zu trocas | %zu passagens\n",
           m_pior.comparacoes, m_pior.trocas, m_pior.passagens);
    printf("----------------------------------------------------\n");

    return EXIT_SUCCESS;
}
