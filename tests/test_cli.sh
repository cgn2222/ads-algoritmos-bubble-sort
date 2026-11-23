#!/usr/bin/env bash
set -euo pipefail

BIN="${1:-./build/ordenacao_precos}"

OUT="$("$BIN")"
grep -q "Posicao \[01\]: R\$   5.75" <<<"$OUT"
grep -q "Posicao \[10\]: R\$  65.30" <<<"$OUT"
grep -q "Melhor caso O(n)   \[ja ordenado\] :  9 comparacoes |  0 trocas | 1 passagem" <<<"$OUT"
grep -q "Pior caso   O(n\^2) \[invertido\]   : 45 comparacoes | 45 trocas | 9 passagens" <<<"$OUT"
echo "[OK] CLI de ordenacao validada com sucesso"
