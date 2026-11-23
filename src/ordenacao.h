#ifndef ORDENACAO_H
#define ORDENACAO_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum {
    ORDEM_CRESCENTE = 0,
    ORDEM_DECRESCENTE = 1
} OrdemOrdenacao;

typedef struct {
    size_t passagens;
    size_t comparacoes;
    size_t trocas;
} MetricasOrdenacao;

typedef struct {
    int id_original;
    int64_t preco_centavos;
} ItemPreco;

/*
 * Ordena um vetor de precos (double) in-place usando Bubble Sort com
 * otimizacao de parada antecipada (early-exit).
 * Se `metricas` nao for NULL, preenche passagens, comparacoes e trocas.
 */
void bubble_sort_precos(double *valores,
                        size_t n,
                        OrdemOrdenacao ordem,
                        MetricasOrdenacao *metricas);

/*
 * Ordena um vetor de ItemPreco preservando estabilidade (chaves iguais
 * mantem sua ordem relativa original por usar comparacao estrita '>' / '<').
 */
void bubble_sort_itens(ItemPreco *itens,
                       size_t n,
                       OrdemOrdenacao ordem,
                       MetricasOrdenacao *metricas);

bool vetor_esta_ordenado(const double *valores, size_t n, OrdemOrdenacao ordem);

#endif
