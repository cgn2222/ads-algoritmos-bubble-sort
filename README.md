# Ordenação de Preços com Bubble Sort Instrumentado em C11

Implementação modular e instrumentada do algoritmo **Bubble Sort** em **C11** com otimização de parada antecipada (*early-exit*), medição exata de passagens, comparações e trocas, prova unitária de **estabilidade** e verificação automatizada em CI com `gcc`, `clang`, AddressSanitizer e UBSan.

[![C11 CI](https://github.com/cgn2222/ads-algoritmos-bubble-sort/actions/workflows/ci.yml/badge.svg)](https://github.com/cgn2222/ads-algoritmos-bubble-sort/actions/workflows/ci.yml)
![C11](https://img.shields.io/badge/C-11-00599C?logo=c&logoColor=white)
![Zero Warnings](https://img.shields.io/badge/warnings--Werror-0-2E7D32)
![Licença MIT](https://img.shields.io/badge/licen%C3%A7a-MIT-yellow)

---

## Complexidade assintótica

| Cenário | Tempo | Comparações ($n = 10$) | Trocas ($n = 10$) | Observação |
| --- | :---: | :---: | :---: | --- |
| **Melhor caso** (já ordenado) | $O(n)$ | $n - 1 = 9$ | $0$ | Garantido pela flag de *early-exit* (`!trocou`) |
| **Caso médio** (aleatório) | $O(n^2)$ | $\sim \frac{n(n-1)}{2}$ | $\sim \frac{n(n-1)}{4}$ | Aproxima-se de quadrático rapidamente |
| **Pior caso** (ordem inversa) | $O(n^2)$ | $\frac{n(n-1)}{2} = 45$ | $\frac{n(n-1)}{2} = 45$ | Toda comparação resulta em troca |
| **Espaço auxiliar** | $O(1)$ | — | — | Ordenação *in-place* |
| **Estabilidade** | **Estável** | — | — | Comparação estrita (`>` / `<`) preserva ordem de chaves iguais |

---

## Como compilar e executar

```bash
# Compilar (-std=c11 -Wall -Wextra -Wpedantic -Werror)
make

# Executar ordenacao crescente, decrescente e analise empirica
make run

# Rodar testes unitarios (incluindo prova de estabilidade e O(n)/O(n^2)) + CLI
make test

# Rodar testes com AddressSanitizer e UndefinedBehaviorSanitizer
make sanitize
```

### Exemplo de saída (`make run`)

```text
-------------- ANALISE EMPIRICA (n = 10) ------------
Melhor caso O(n)   [ja ordenado] :  9 comparacoes |  0 trocas | 1 passagem
Pior caso   O(n^2) [invertido]   : 45 comparacoes | 45 trocas | 9 passagens
----------------------------------------------------
```

---

## Decisões de engenharia e trade-offs

| Decisão | Justificativa | Trade-off / Evolução |
| --- | --- | --- |
| **Parâmetro `OrdemOrdenacao` unificado** | Elimina duplicação de código entre os laços crescente e decrescente, centralizando a regra no predicado de comparação. | Para tipos arbitrários em C, o próximo passo natural é aceitar ponteiro de função comparadora (`int (*cmp)(const void *, const void *)`), como `qsort`. |
| **Instrumentação opcional (`MetricasOrdenacao *`)** | Permite validar empiricamente nos testes unitários que o *early-exit* realmente atinge $n - 1$ comparações no melhor caso e $\frac{n(n-1)}{2}$ no pior caso. | Passar `NULL` desabilita a devolução das métricas sem alterar a assinatura da função. |
| **Preservação do vetor original em `main.c`** | Ordena cópias independentes para crescente e decrescente; evita o viés de medir a ordenação decrescente sempre sobre um vetor já invertido. | Custa $O(n)$ extra em memória no chamador, preservando integridade dos dados de entrada. |
| **Quando não usar Bubble Sort** | Excelente valor didático para visualizar invariantes de laço e estabilidade, mas ineficiente para grandes volumes ($n \gg 50$). | Em produção, usar algoritmos $O(n \log n)$ como `qsort` (Introsort/Quicksort), Mergesort ou Timsort. |

---

## Estrutura do repositório

```text
ads-algoritmos-bubble-sort/
├── .github/workflows/ci.yml   # CI com gcc, clang, ASan e UBSan
├── Makefile                   # Build estrito C11, testes e sanitizers
├── src/
│   ├── ordenacao.h            # Contratos, OrdemOrdenacao, MetricasOrdenacao e ItemPreco
│   ├── ordenacao.c            # Bubble Sort com early-exit e garantia de estabilidade
│   └── main.c                 # Demonstracao com 10 precos e comparativo O(n) vs O(n^2)
└── tests/
    ├── test_ordenacao.c       # Testes unitarios (estabilidade, melhor/pior caso, bordas)
    └── test_cli.sh            # Smoke test da CLI
```

---

## Créditos

Desenvolvido por **Carlos Gabriel Novo** no curso superior de tecnologia em **Análise e Desenvolvimento de Sistemas** (Cruzeiro do Sul Virtual, 2026) — disciplina de *Algoritmos e Pensamento Computacional* (Experiência Prática IV).

Distribuído sob licença **MIT** ([`LICENSE`](LICENSE)).
