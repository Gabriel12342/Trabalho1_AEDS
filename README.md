# Trabalho 1 — AEDSI
## Algoritmo Genético para Ajuste de Função Linear

> Trabalho de Aquecimento da disciplina de Algoritmos e Estruturas de Dados I  
> CEFET-MG — Campus Divinópolis  
> Professor: Michel Pires da Silva

---

## Introdução

Este projeto implementa um **Algoritmo Genético (AG)** em linguagem C com o objetivo de encontrar os coeficientes `a` e `b` de uma reta de regressão linear da forma:

```
ŷ = ax + b
```

O AG evolui uma população de indivíduos ao longo de várias gerações, minimizando o **Erro Quadrático Médio (MSE)** entre os valores reais e os valores previstos pela reta. Cada indivíduo representa uma solução candidata, codificada como um par de parâmetros `(a, b)`.

Além da abordagem evolutiva, o projeto enfatiza aspectos fundamentais da programação em C: manipulação de memória dinâmica, uso de ponteiros e organização modular do código.

---

## Problema Proposto

Dado um conjunto fixo de pontos `D = {(x₁,y₁), (x₂,y₂), ..., (xₙ,yₙ)}`, o objetivo é encontrar os parâmetros `a` e `b` que minimizem a discrepância entre a reta estimada e os dados observados. O erro de cada indivíduo é calculado como:

```
MSE = (1/n) * Σ (yᵢ - (a·xᵢ + b))²
```

A partir do erro, define-se o **fitness** de cada indivíduo:

```
fitness = 1 / (1 + MSE)
```

Quanto menor o erro, maior o fitness — e mais próxima a solução está do ótimo.

---

## Estrutura do Projeto

```
Trabalho1AEDSI/
├── src/
│   ├── trabalho1.h       # Definições de structs e protótipos de funções
│   ├── trabalho1.c       # Função principal (main) e loop evolutivo
│   ├── individuos.c      # GerarPopulacao e Ordenar
│   ├── operacoes.c       # CalculoErroFitness, Crossover e Mutacao
│   └── pontos.c          # LerInputdatDados e GerarPontos
├── config/
│   ├── input.dat         # Parâmetros e pontos de entrada
│   └── output.dat        # Resultados gerados por geração
├── build/
│   └── app               # Executável compilado
└── Makefile
```

---

## Estruturas de Dados

O projeto utiliza três structs principais, definidas em `trabalho1.h`:

### `Individuo`
Representa uma solução candidata no espaço de busca.

```c
typedef struct {
    float a, b;        // coeficientes da reta ŷ = ax + b
    float fitness;     // aptidão do indivíduo (quanto maior, melhor)
    float erro;        // erro quadrático médio (MSE)
} Individuo;
```

### `Ponto`
Representa um par de coordenadas do conjunto amostral fixo.

```c
typedef struct {
    float x, y;        // coordenadas do ponto observado
} Ponto;
```

### `Dados`
Armazena os parâmetros de configuração do algoritmo.

```c
typedef struct {
    int n;   // número de pontos do dataset
    int m;   // tamanho da população
    int G;   // número de gerações
} Dados;
```

A população é gerenciada como um **vetor dinâmico de `m` indivíduos** (`Individuo *populacao`), alocado via `malloc`. Vetores auxiliares de pais e filhos com tamanho `m/2` são utilizados para as operações de crossover.

---

## Como Compilar e Executar

> Requer ambiente **Linux** (Ubuntu ou Zorin recomendados) com `gcc` e `make`.

Para limpar, compilar e executar em sequência:

```bash
make clean && make && make run
```

Para apenas executar o binário já compilado:

```bash
./build/app
```

---

## Entrada e Saída

### Arquivo de entrada — `config/input.dat`

A primeira linha contém os parâmetros de configuração; as linhas seguintes, os pares de pontos:

```
n m G
x1 y1
x2 y2
...
xn yn
```

| Parâmetro | Descrição |
|-----------|-----------|
| `n` | Número de pontos do dataset |
| `m` | Tamanho da população de indivíduos |
| `G` | Número de gerações do processo evolutivo |

**Exemplo (`input.dat` incluído):**

```
8 20 500
1 3
2 5
3 7
4 9
5 11
6 13
7 15
8 17
```

### Arquivo de saída — `config/output.dat`

A cada geração, é registrado o melhor indivíduo encontrado:

```
Melhor fitness:0.999469 |Erro: 0.000532 |a: 1.989948 |b: 1.046355 |
```

---

## Lógica de Evolução

O algoritmo segue o ciclo evolutivo clássico, repetido por `G` gerações:

```
Início
  │
  ├─ Leitura dos parâmetros e pontos (input.dat)
  ├─ Geração da população inicial aleatória
  │
  └─ Loop por G gerações:
        ├─ 1. Avaliação   → CalculoErroFitness (calcula MSE e fitness de todos)
        ├─ 2. Seleção     → Ordenar (ordena por fitness, copia m/2 melhores como pais)
        ├─ 3. Crossover   → combina pares de pais, filhos substituem os piores
        ├─ 4. Mutação     → aplica perturbação delta ∈ [-1,1] em a ou b com prob. 50%
        ├─ 5. Reavaliação → CalculoErroFitness novamente após as modificações
        └─ 6. Registro    → salva o melhor indivíduo da geração em output.dat
```

### Detalhamento das funções

**`LerInputdatDados`** — lê `n`, `m` e `G` da primeira linha do `input.dat`.

**`GerarPontos`** — lê os `n` pares `(x, y)` do arquivo e armazena no vetor de pontos.

**`GerarPopulacao`** — inicializa `m` indivíduos com valores aleatórios de `a` e `b` no intervalo `[-10, 10]`, controlados pela semente `srand(42)` para reprodutibilidade.

**`CalculoErroFitness`** — para cada indivíduo, calcula o MSE sobre todos os `n` pontos e deriva o fitness via `1 / (1 + MSE)`.

**`Ordenar`** — aplica Selection Sort sobre a população (decrescente por fitness) e copia os `m/2` melhores para o vetor de pais.

**`Crossover`** — sorteia pares únicos de pais e gera dois filhos por par trocando os coeficientes:
- `filho[i]   = (paiA.a, paiB.b)`
- `filho[i+1] = (paiB.a, paiA.b)`

Os filhos substituem a segunda metade (os piores) da população.

**`Mutacao`** — percorre os `m/2` indivíduos da segunda metade; com 50% de probabilidade, aplica um delta aleatório `∈ [-1, 1]` em `a` ou `b`, mantendo os valores dentro de `[-10, 10]`.

---

## Experimentos Realizados

### Configuração

| Parâmetro | Valor |
|-----------|-------|
| Pontos (`n`) | 8 |
| População (`m`) | 20 |
| Gerações (`G`) | 500 |
| Semente | `srand(42)` |
| Intervalo de busca | `[-10, 10]` |

Os pontos de entrada seguem a reta ideal `y = 2x + 1`, permitindo avaliar a precisão da convergência.

### Resultados

| | Fitness | Erro (MSE) | `a` | `b` |
|---|---|---|---|---|
| **1ª geração** | 0.244386 | 3.091892 | 1.293038 | 4.865410 |
| **Última geração** | 0.999469 | 0.000532 | 1.989948 | 1.046355 |
| **Ótimo real** | 1.000000 | 0.000000 | 2.000000 | 1.000000 |

O algoritmo convergiu para `a = 1.990` e `b = 1.046`, com desvios de apenas **0,5%** e **4,6%** em relação aos valores ideais.

---

## Comportamento do Erro ao Longo das Gerações

A evolução do erro pode ser dividida em três fases distintas:

**Fase 1 — Convergência inicial agressiva (gerações 1–9)**

Partindo de um ponto inicial ruim (MSE = 3,09), o erro cai para 0,055 em apenas 9 gerações — uma redução de **98,2%**. A alta diversidade genética inicial, combinada com o amplo intervalo `[-10, 10]`, permite saltos grandes logo no início.

**Fase 2 — Estagnação intermediária (gerações 9–60)**

O fitness estabiliza em torno de 0,954 por aproximadamente 50 gerações. O algoritmo encontrou uma boa solução local mas perdeu diversidade genética rapidamente nesta fase.

**Fase 3 — Refinamento progressivo (gerações 60–500)**

O refinamento é consistente e contínuo, com melhorias distribuídas ao longo de toda esta fase. O algoritmo continua evoluindo até gerações muito tardias (~480), atingindo erro final de **0,00053**.

### Conclusões

- O intervalo `[-10, 10]` produziu boa diversidade inicial, sustentando o refinamento por mais gerações.
- O coeficiente `a` converge antes de `b`, indicando que a paisagem de fitness é mais sensível à inclinação da reta do que ao intercepto.
- A convergência prematura ocorre mas é transitória — o algoritmo retoma melhorias após períodos de estagnação.
- A solução final (`a = 1.990`, `b = 1.046`) é muito próxima do ótimo teórico (`a = 2.0`, `b = 1.0`).

---

## Análise de Complexidade das Principais Rotinas

As variáveis utilizadas na análise são:

- **n** — número de pontos do dataset
- **m** — tamanho da população
- **G** — número de gerações
- **quantidade** = m/2 — número de pais/filhos por geração

---

### `LerInputdatDados` — `pontos.c`

Realiza uma única leitura de 3 inteiros do arquivo de entrada.

| | Complexidade |
|-|---|
| **Tempo** | O(1) |
| **Espaço** | O(1) |

---

### `GerarPontos` — `pontos.c`

```c
for (int i = 0; i < n; i++) {
    fscanf(file, "%f %f", &pontos[i].x, &pontos[i].y);
}
```

Itera uma única vez sobre os `n` pontos.

| | Complexidade |
|-|---|
| **Tempo** | O(n) |
| **Espaço** | O(n) |

---

### `GerarPopulacao` — `individuos.c`

```c
for (int i = 0; i < m; i++) {
    populacao[i].a = ((float)rand() / RAND_MAX) * 20 - 10;
    populacao[i].b = ((float)rand() / RAND_MAX) * 20 - 10;
}
```

Itera uma única vez sobre os `m` indivíduos.

| | Complexidade |
|-|---|
| **Tempo** | O(m) |
| **Espaço** | O(m) |

---

### `CalculoErroFitness` — `operacoes.c`

```c
for (int i = 0; i < m; i++) {           // percorre toda a população
    for (int j = 0; j < n; j++) {       // percorre todos os pontos
        erro = yreal - yprev;
        somatorio += erro * erro;
    }
    populacao[i].erro    = somatorio / n;
    populacao[i].fitness = 1.0 / (1.0 + populacao[i].erro);
}
```

Loop duplo aninhado: para cada indivíduo, calcula o MSE sobre todos os pontos.

Chamada **duas vezes por geração** — é a rotina mais custosa do algoritmo.

| | Complexidade |
|-|---|
| **Tempo** | O(m × n) |
| **Espaço** | O(1) auxiliar |

---

### `Ordenar` — `individuos.c`

```c
for (int i = 0; i < m; i++) {          // Selection Sort
    int posicaomax = i;
    for (int j = i; j < m; j++) {
        if (populacao[j].fitness > populacao[posicaomax].fitness)
            posicaomax = j;
    }
    // troca
}
for (int i = 0; i < quantidade; i++) { // cópia dos m/2 melhores
    pais[i] = populacao[i];
}
```

Implementa **Selection Sort** (O(m²)) seguido de uma cópia dos melhores.

| | Complexidade |
|-|---|
| **Tempo** | O(m²) |
| **Espaço** | O(m) auxiliar |

---

### `Crossover` — `operacoes.c`

**1. Seleção de pares únicos** — no pior caso, verifica todos os pares anteriores para cada novo par → O(quantidade²) = **O(m²/4)**

**2. Geração dos filhos** — troca de `a` e `b` entre cada par → O(m)

**3. Substituição dos piores** — filhos ocupam a segunda metade da população → O(m)

| | Complexidade |
|-|---|
| **Tempo** | O(m²) |
| **Espaço** | O(m) auxiliar |

---

### `Mutacao` — `operacoes.c`

```c
for (int i = 1; i < quantidade; i++) {
    if (rand() % 2 == 0) {
        // altera a ou b com delta ∈ [-1, 1]
    }
}
```

Percorre os `m/2` indivíduos, aplicando perturbação com probabilidade 50%.

| | Complexidade |
|-|---|
| **Tempo** | O(m) |
| **Espaço** | O(1) |

---

### Loop Principal — `trabalho1.c`

```c
for (int i = 0; i < G; i++) {
    CalculoErroFitness(...);   // O(m × n)
    Ordenar(...);              // O(m²)
    Crossover(...);            // O(m²)
    Mutacao(...);              // O(m)
    CalculoErroFitness(...);   // O(m × n)
}
```

**Complexidade total:**

$$T(G, m, n) = O\bigl(G \times (m^2 + m \cdot n)\bigr)$$

| | Complexidade |
|-|---|
| **Tempo total** | **O(G × (m² + m·n))** |
| **Espaço total** | **O(m + n)** |

---

### Resumo das Complexidades

| Rotina | Arquivo | Tempo | Espaço |
|--------|---------|-------|--------|
| `LerInputdatDados` | `pontos.c` | O(1) | O(1) |
| `GerarPontos` | `pontos.c` | O(n) | O(n) |
| `GerarPopulacao` | `individuos.c` | O(m) | O(m) |
| `CalculoErroFitness` | `operacoes.c` | **O(m × n)** | O(1) |
| `Ordenar` | `individuos.c` | **O(m²)** | O(m) |
| `Crossover` | `operacoes.c` | **O(m²)** | O(m) |
| `Mutacao` | `operacoes.c` | O(m) | O(1) |
| **Loop Principal** | `trabalho1.c` | **O(G × (m² + m·n))** | **O(m + n)** |

---

## Melhorias Futuras

**Algoritmo de ordenação mais eficiente**
Substituir o Selection Sort (O(m²)) por Merge Sort ou Quick Sort (O(m log m)) reduziria o custo dominante do loop principal, especialmente para populações grandes.

**Seleção de pais mais robusta**
A verificação de pares repetidos no Crossover tem complexidade quadrática. Substituir por **seleção por torneio** ou **roleta (roulette wheel selection)** tornaria a seleção O(m) e mais eficaz para explorar o espaço de busca.

**Taxa de mutação adaptativa**
Reduzir o delta de mutação conforme o fitness aumenta permitiria refinamento mais fino nas gerações finais, quando os erros já são pequenos.

**Elitismo**
Garantir que o melhor indivíduo de cada geração sempre sobreviva para a próxima, evitando que boas soluções sejam perdidas após crossover ou mutação agressiva.

**Critério de parada antecipada**
Adicionar um critério de convergência — por exemplo, interromper após `k` gerações sem melhoria — economizaria processamento nos longos períodos de estagnação observados.

**Parâmetros configuráveis via `input.dat`**
Tornar a taxa de mutação, o delta e o intervalo de busca configuráveis externamente, evitando recompilação para diferentes experimentos.

**Controle de diversidade populacional**
Sem controle de diversidade, a população pode convergir prematuramente para mínimos locais. Técnicas como **niching** ou reinicialização parcial da população ajudariam a explorar melhor o espaço de busca.

**Suporte a outros modelos**
O projeto está restrito ao ajuste linear `y = ax + b`. Generalizar para polinômios de grau `n` ou funções não-lineares aumentaria significativamente o alcance do algoritmo.

---

## Observações

- A semente aleatória está fixada em `srand(42)` para garantir **reprodutibilidade** dos resultados.
- Os coeficientes `a` e `b` são gerados e mantidos no intervalo `[-10, 10]`.
- O Makefile utiliza `gcc` como compilador.
- Arquivo `Makefile` concedido pelo professor Michel Pires.

---
## Especificações do ambiente de teste
Este projeto foi executado utilizando:

- Sistema Operacional: Linux Mint 22.1 Cinnamon
- Compilador: GCC 13.3.0
- Hardware: 12th Intel© Core™ i5-1235U × 10 ; 7.5GB RAM; 512.1GB SSD; Intel Corporation Alder Lake-UP3 GT2 [UHD Graphics].
## Autor

**Gabriel Alves Faria**  
CEFET-MG — Campus Divinópolis
