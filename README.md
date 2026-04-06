# Trabalho 1 — AEDSI
## Algoritmo Genético para Ajuste de Função Linear

> Trabalho de Aquecimento da disciplina de Algoritmos e Estruturas de Dados I  
> CEFET-MG — Campus Divinópolis  
> Professor: Michel Pires da Silva

---

## Introdução

Este projeto implementa um **Algoritmo Genético (AG)** em linguagem C com o objetivo de encontrar os coeficientes `a` e `b` de uma reta de regressão linear da forma:

```
y = ax + b
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

A população é gerenciada como um **vetor dinâmico de `m` indivíduos** (`Individuo *populacao`), alocado via `malloc`. Vetores auxiliares de pais (`m/2`) e filhos (`m/2`) são utilizados para as operações de crossover.

---

## Como Compilar e Executar

Para limpar, compilar e executar em sequência:

```bash
make clean && make && make run
```

Para apenas executar o binário já compilado:

```bash
./build/app
```

O Makefile utiliza `gcc` com flags `-Wall -Wextra -g` e linka com `-lm`.

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
Melhor fitness:0.996697 |Erro: 0.003314 |a: 1.974881 |b: 1.114194 |
```

---

## Lógica do Algoritmo

O projeto possui um arquivo cabeçalho `trabalho1.h` onde são definidas as estruturas principais: `Individuo`, que armazena os parâmetros `a`, `b`, o erro e o fitness de cada solução candidata; `Ponto`, que representa um par de coordenadas `(x, y)` do conjunto amostral; e `Dados`, que agrupa os parâmetros de configuração — número de pontos `(n)`, tamanho da população `(m)` e número de gerações `(G)`.

O algoritmo lê as informações do arquivo de entrada `input.dat` via `fscanf`, coletando `n`, `m` e `G` na primeira linha e armazenando-os na struct `Dados`. Em seguida, lê os `n` pares `(x, y)` e os armazena no vetor de pontos alocado dinamicamente.

A população inicial é gerada com `m` indivíduos, cada um recebendo valores aleatórios para `a` e `b` no intervalo `[-10, 10]`. A semente `srand(42)` garante a reprodutibilidade dos resultados entre execuções.

A cada geração, o ciclo evolutivo ocorre da seguinte forma: primeiro, é calculado o MSE de cada indivíduo em relação a todos os `n` pontos, e o fitness é derivado pela fórmula `1 / (1 + MSE)`. Em seguida, a população é ordenada de forma decrescente por fitness via **Selection Sort**, e os `m/2` melhores indivíduos são copiados para o vetor de pais.

No **crossover**, `m/4` pares únicos de pais são sorteados aleatoriamente e dois filhos são gerados por par com a troca dos coeficientes:

```
filho[i]   = (paiA.a, paiB.b)
filho[i+1] = (paiB.a, paiA.b)
```

Os `m/2` filhos gerados substituem a segunda metade da população (os indivíduos de menor fitness).

Na **mutação**, o algoritmo percorre os `m/2` indivíduos da primeira metade da população — com exceção do melhor (`populacao[0]`), que é preservado sem alteração (elitismo). Para cada indivíduo, com probabilidade de 50%, um delta aleatório `∈ [-1, 1]` é somado a `a` ou `b`, mantendo os valores dentro dos limites `[-10, 10]`.

Por fim, `CalculoErroFitness` é chamada novamente para atualizar os valores de erro e fitness após as operações genéticas. Esse ciclo se repete por `G` gerações, registrando o melhor indivíduo de cada geração no arquivo `output.dat`.

O algoritmo segue o ciclo evolutivo clássico:

```
Início
  │
  ├─ Leitura dos parâmetros e pontos (input.dat)
  ├─ Geração da população inicial aleatória
  │
  └─ Loop por G gerações:
        ├─ 1. Avaliação   → CalculoErroFitness (calcula MSE e fitness de todos)
        ├─ 2. Seleção     → Ordenar (ordena por fitness, copia m/2 melhores como pais)
        ├─ 3. Crossover   → m/4 pares de pais geram m/2 filhos, substituem os piores
        ├─ 4. Mutação     → aplica perturbação delta ∈ [-1,1] em a ou b com prob. 50%
        ├─ 5. Reavaliação → CalculoErroFitness novamente após as modificações
        └─ 6. Registro    → salva o melhor indivíduo da geração em output.dat
```

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
| **Última geração** | 0.996697 | 0.003314 | 1.974881 | 1.114194 |
| **Ótimo real** | 1.000000 | 0.000000 | 2.000000 | 1.000000 |

O algoritmo convergiu para `a = 1.975` e `b = 1.114`, com desvios de apenas **1,3%** e **11,4%** em relação aos valores ideais.

---

## Comportamento do Erro ao Longo das Gerações

A evolução do erro pode ser dividida em três fases distintas:

**Fase 1 — Convergência inicial rápida (gerações 1–50)**

Partindo de um ponto inicial ruim (`MSE = 3.09`), o erro cai para aproximadamente `0.17` nas primeiras 50 gerações — uma redução de **94,5%**. A alta diversidade genética inicial, combinada com o amplo intervalo `[-10, 10]`, permite saltos grandes logo no início.

**Fase 2 — Refinamento progressivo (gerações 50–200)**

O algoritmo continua melhorando consistentemente, com o fitness passando de ~0.86 para ~0.99. Os ajustes se tornam mais finos, com `a` e `b` convergindo progressivamente para os valores ideais.

**Fase 3 — Estagnação final (gerações 200–500)**

O refinamento desacelera, com longos períodos mantendo o mesmo melhor indivíduo. O algoritmo tende a estagnar próximo do ótimo local encontrado, atingindo erro final de **0.003314**.

### Conclusões

- A população de `m = 20` foi suficiente para sustentar diversidade e refinamento por várias centenas de gerações.
- O coeficiente `a` converge antes de `b`, indicando que a paisagem de fitness é mais sensível à inclinação da reta do que ao intercepto.
- A solução final (`a = 1.975`, `b = 1.114`) é muito próxima do ótimo teórico (`a = 2.0`, `b = 1.0`).

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

Loop duplo aninhado: para cada indivíduo, calcula o MSE sobre todos os pontos. Chamada **duas vezes por geração** — é a rotina mais custosa do algoritmo.

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
| **Espaço** | O(1) auxiliar |

---

### `Crossover` — `operacoes.c`

**1. Seleção de pares únicos** — sorteia `quantidade/2` pares sem repetição → O(quantidade²) = **O(m²/4)**

**2. Geração dos filhos** — troca de `a` e `b` entre cada par, gerando 2 filhos por par → O(quantidade) = **O(m)**

**3. Substituição dos piores** — `quantidade` filhos ocupam a segunda metade da população → O(m)

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

Percorre os `m/2 - 1` indivíduos (preserva o melhor), aplicando perturbação com probabilidade 50%.

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
| `Ordenar` | `individuos.c` | **O(m²)** | O(1) |
| `Crossover` | `operacoes.c` | **O(m²)** | O(m) |
| `Mutacao` | `operacoes.c` | O(m) | O(1) |
| **Loop Principal** | `trabalho1.c` | **O(G × (m² + m·n))** | **O(m + n)** |

---

## Limitações

- **Tamanho de população pequeno:** Com `m = 20` indivíduos, a população pode perder diversidade genética ao longo das gerações, favorecendo a estagnação observada na fase final. Populações maiores sustentariam a exploração do espaço de busca por mais tempo.
- **Número fixo de gerações:** O algoritmo sempre executa exatamente `G` gerações, mesmo que a solução já tenha convergido. Isso representa desperdício de processamento nas fases de estagnação.
- **Restrito à regressão linear:** A implementação está limitada ao modelo `y = ax + b`. Não é possível ajustar outros tipos de função sem modificar diretamente o código-fonte.

---

## Conclusão

O Algoritmo Genético implementado demonstrou ser eficaz para o problema de ajuste de uma função linear `y = ax + b` a um conjunto de pontos. Com 500 gerações e uma população de 20 indivíduos, foi possível convergir para uma solução próxima do valor estipulado — atingindo `a = 1.975` e `b = 1.114` frente aos valores ideais `a = 2.0` e `b = 1.0`, com um MSE final de apenas **0.003314**.

O processo evolutivo evidenciou um comportamento em três fases: uma convergência inicial rápida nas primeiras gerações, seguida de refinamento progressivo, e por fim um período de estagnação que se estendeu até as gerações finais. Esse padrão reforça a importância de um espaço de busca amplo (`[-10, 10]`) para manter diversidade genética.

Do ponto de vista algorítmico, o projeto permitiu observar na prática os conceitos de análise assintótica discutidos na disciplina. O custo total do algoritmo é dominado pelas operações de ordenação e crossover — ambas O(m²) por geração — e pelo cálculo de fitness — O(m×n), chamado duas vezes por geração — resultando em uma complexidade geral de **O(G × (m² + m·n))**.

Por fim, o trabalho consolidou habilidades fundamentais de programação em C: alocação dinâmica de memória, organização modular com separação de responsabilidades entre arquivos, e uso de ponteiros para manipulação eficiente de estruturas de dados.

---

## Especificações do Ambiente de Teste

- **Sistema Operacional:** Linux Mint 22.1 Cinnamon
- **Compilador:** GCC 13.3.0
- **Hardware:** Intel® Core™ i5-1235U × 10 | 7.5 GB RAM | 512 GB SSD | Intel UHD Graphics

---

## Créditos

Arquivo Makefile concedido pelo professor [Michel Pires](https://github.com/mpiress).

## Autor

**Gabriel Alves Faria**  
CEFET-MG — Campus Divinópolis
