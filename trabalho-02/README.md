# 🇧🇷 Notebook Data Structures — Calculadora de Inteiros Grandes (Big Integer Calculator)

## Título do Projeto
* **Nome:** Notebook Data Structures — Calculadora de Inteiros Grandes (Big Integer Calculator)
* **Tipo:** Projeto C pequeno que fornece uma biblioteca `bigint` e uma calculadora CLI

---

## Visão Geral
* **Descrição:** Este repositório contém uma implementação simples de inteiro de precisão arbitrária (**bigint**) e um programa de calculadora que a utiliza. O projeto inclui código-fonte, *headers* (cabeçalhos), *scripts* de *build* (compilação) e artefatos de relatórios/benchmarks usados para avaliação.
* **Linguagem:** C

---

## Estrutura do Repositório
* **Raiz:** Entrada do projeto e artefatos de *build* como `Makefile` e `main` (executável esperado após o *build*).
* **Código-Fonte:** `src/` contém a implementação: `bigint.c`, `calculator.c` e `main.c`.
* **Headers (Cabeçalhos):**: `lib/` contém *headers* públicos: `bigint.h`, `calculator.h`.
* **Saída do Build:** `build/` contém objetos compilados e binários.
* **Relatório:** `report/` contém o relatório do projeto, `benchmark.csv` e `main.typ` usados para gerar o relatório.

---

## Build (Compilação)
* **Pré-requisitos:** Um compilador C (ex: `gcc`), `make` e um *shell* tipo POSIX (Linux recomendado).
* **Comando de Build:**
```bash
make
```

## Executando

```bash
make run
```
