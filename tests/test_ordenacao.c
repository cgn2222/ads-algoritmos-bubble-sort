#include "../src/ordenacao.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

static void test_precos_supermercado(void) {
    const double orig[10] = {
        28.50, 14.90, 5.75, 42.00, 19.99,
        8.40,  65.30, 12.25, 33.80, 9.90
    };
    double v[10];
    MetricasOrdenacao m;

    memcpy(v, orig, sizeof(orig));
    bubble_sort_precos(v, 10, ORDEM_CRESCENTE, &m);
    assert(vetor_esta_ordenado(v, 10, ORDEM_CRESCENTE));
    assert(fabs(v[0] - 5.75) < 1e-9);
    assert(fabs(v[9] - 65.30) < 1e-9);
    assert(m.comparacoes > 0 && m.trocas > 0);

    memcpy(v, orig, sizeof(orig));
    bubble_sort_precos(v, 10, ORDEM_DECRESCENTE, &m);
    assert(vetor_esta_ordenado(v, 10, ORDEM_DECRESCENTE));
    assert(fabs(v[0] - 65.30) < 1e-9);
    assert(fabs(v[9] - 5.75) < 1e-9);
}

static void test_melhor_e_pior_caso(void) {
    double ordenado[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    MetricasOrdenacao m_best;

    /* Melhor caso O(n): n - 1 = 9 comparacoes, 0 trocas, 1 passagem */
    bubble_sort_precos(ordenado, 10, ORDEM_CRESCENTE, &m_best);
    assert(m_best.passagens == 1);
    assert(m_best.comparacoes == 9);
    assert(m_best.trocas == 0);

    /* Pior caso O(n^2): n*(n-1)/2 = 45 comparacoes e 45 trocas */
    MetricasOrdenacao m_worst;
    bubble_sort_precos(ordenado, 10, ORDEM_DECRESCENTE, &m_worst);
    assert(m_worst.passagens == 9);
    assert(m_worst.comparacoes == 45);
    assert(m_worst.trocas == 45);
    assert(vetor_esta_ordenado(ordenado, 10, ORDEM_DECRESCENTE));
}

static void test_estabilidade(void) {
    /* Itens com precos iguais devem preservar a ordem relativa de id_original. */
    ItemPreco itens[5] = {
        {.id_original = 1, .preco_centavos = 1990},
        {.id_original = 2, .preco_centavos = 990},
        {.id_original = 3, .preco_centavos = 1990},
        {.id_original = 4, .preco_centavos = 990},
        {.id_original = 5, .preco_centavos = 1990}
    };
    MetricasOrdenacao m;

    bubble_sort_itens(itens, 5, ORDEM_CRESCENTE, &m);
    assert(itens[0].preco_centavos == 990 && itens[0].id_original == 2);
    assert(itens[1].preco_centavos == 990 && itens[1].id_original == 4);
    assert(itens[2].preco_centavos == 1990 && itens[2].id_original == 1);
    assert(itens[3].preco_centavos == 1990 && itens[3].id_original == 3);
    assert(itens[4].preco_centavos == 1990 && itens[4].id_original == 5);
}

static void test_casos_borda(void) {
    MetricasOrdenacao m;

    /* NULL e n < 2 nao devem falhar */
    bubble_sort_precos(NULL, 0, ORDEM_CRESCENTE, &m);
    assert(m.passagens == 0 && m.comparacoes == 0 && m.trocas == 0);

    double unico[1] = {42.0};
    bubble_sort_precos(unico, 1, ORDEM_CRESCENTE, &m);
    assert(m.passagens == 0 && unico[0] == 42.0);
    assert(vetor_esta_ordenado(unico, 1, ORDEM_CRESCENTE));

    /* Valores negativos e duplicados */
    double misto[5] = {-2.5, 0.0, -2.5, 10.0, -10.0};
    bubble_sort_precos(misto, 5, ORDEM_CRESCENTE, NULL);
    assert(vetor_esta_ordenado(misto, 5, ORDEM_CRESCENTE));
    assert(fabs(misto[0] - (-10.0)) < 1e-9);
    assert(fabs(misto[4] - 10.0) < 1e-9);
}

int main(void) {
    test_precos_supermercado();
    test_melhor_e_pior_caso();
    test_estabilidade();
    test_casos_borda();

    printf("[OK] Todos os testes unitarios de bubble_sort passaram.\n");
    return 0;
}
