#include "ordenacao.h"

#include <string.h>

static bool deve_trocar_double(double atual, double proximo, OrdemOrdenacao ordem) {
    if (ordem == ORDEM_CRESCENTE) {
        return atual > proximo;
    }
    return atual < proximo;
}

static bool deve_trocar_int64(int64_t atual, int64_t proximo, OrdemOrdenacao ordem) {
    if (ordem == ORDEM_CRESCENTE) {
        return atual > proximo;
    }
    return atual < proximo;
}

void bubble_sort_precos(double *valores,
                        size_t n,
                        OrdemOrdenacao ordem,
                        MetricasOrdenacao *metricas) {
    MetricasOrdenacao local = {0, 0, 0};

    if (valores == NULL || n < 2) {
        if (metricas != NULL) {
            *metricas = local;
        }
        return;
    }

    for (size_t i = 0; i < n - 1; i++) {
        bool trocou = false;
        local.passagens++;

        for (size_t j = 0; j < n - 1 - i; j++) {
            local.comparacoes++;
            if (deve_trocar_double(valores[j], valores[j + 1], ordem)) {
                double temp = valores[j];
                valores[j] = valores[j + 1];
                valores[j + 1] = temp;
                local.trocas++;
                trocou = true;
            }
        }

        if (!trocou) {
            break;
        }
    }

    if (metricas != NULL) {
        *metricas = local;
    }
}

void bubble_sort_itens(ItemPreco *itens,
                       size_t n,
                       OrdemOrdenacao ordem,
                       MetricasOrdenacao *metricas) {
    MetricasOrdenacao local = {0, 0, 0};

    if (itens == NULL || n < 2) {
        if (metricas != NULL) {
            *metricas = local;
        }
        return;
    }

    for (size_t i = 0; i < n - 1; i++) {
        bool trocou = false;
        local.passagens++;

        for (size_t j = 0; j < n - 1 - i; j++) {
            local.comparacoes++;
            if (deve_trocar_int64(itens[j].preco_centavos, itens[j + 1].preco_centavos, ordem)) {
                ItemPreco temp = itens[j];
                itens[j] = itens[j + 1];
                itens[j + 1] = temp;
                local.trocas++;
                trocou = true;
            }
        }

        if (!trocou) {
            break;
        }
    }

    if (metricas != NULL) {
        *metricas = local;
    }
}

bool vetor_esta_ordenado(const double *valores, size_t n, OrdemOrdenacao ordem) {
    if (valores == NULL || n < 2) {
        return true;
    }
    for (size_t i = 0; i < n - 1; i++) {
        if (deve_trocar_double(valores[i], valores[i + 1], ordem)) {
            return false;
        }
    }
    return true;
}
