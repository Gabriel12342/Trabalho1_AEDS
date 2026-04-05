# Trabalho1_AEDS
Trabalho de Aquecimento: Algoritmos Genéticos
# Introdução
Este projeto foi desenvolvido no contexto da disciplina de Análise Estrutural de Dados I (AEDSI), do Centro Federal de Educação Tecnológica de Minas Gerais (CEFET-MG), Campus Divinópolis.

Este projeto implementa um Algoritmo Genético (AG) em linguagem C com o objetivo de encontrar os coeficientes a e b de uma reta de regressão linear do tipo:
```
y = a * x + b
```
O AG evolui uma população de indivíduos ao longo de várias gerações, minimizando o erro quadrático médio entre os valores reais e os valores previstos pela reta.

Além da abordagem evolutiva, o projeto também enfatiza aspectos fundamentais da programação em C, como manipulação de memória dinâmica, uso de ponteiros e organização modular do código.

---
# Problema Proposto

O problema consiste na implementação de um algoritmo genético capaz de ler valores de entrada de um arquivo, contendo uma amostra empírica de pontos (x, y) que permanecem constantes durante toda a execução. Esses dados constituem o espaço amostral sobre o qual as soluções candidatas são avaliadas.

A população inicial é gerada de forma aleatória, sendo estruturada como um conjunto de vetores de dimensão *m* × 2, onde *m* corresponde ao número total de indivíduos e cada vetor representa um indivíduo.

---

# Funcionalidades
O algoritmo deve ser capaz de ler valores de entrada a partir de um arquivo externo, contendo uma amostra empírica de pontos (*x*, *y*), bem como a quantidade total desses pontos, o tamanho da população de indivíduos a ser simulada e o número de gerações do processo evolutivo. Esses parâmetros permanecem constantes durante toda a execução, constituindo o espaço amostral sobre o qual as soluções candidatas são avaliadas.

A população inicial de indivíduos é gerada por meio de processos pseudoaleatórios, controlados por uma semente (*seed*), garantindo a reprodutibilidade dos experimentos. Dessa forma, diferentes execuções do algoritmo podem ser comparadas de maneira consistente sob as mesmas condições iniciais.

Cada indivíduo representa uma possível solução para o problema e é definido por um conjunto de parâmetros, sendo estruturado como um conjunto de vetores de dimensão *m × 2*, onde *m* corresponde ao número total de indivíduos e cada vetor representa um indivíduo.

---
# Avaliação
A avaliação dos indivíduos é realizada com base no ajuste de uma função linear (ŷ = ax + b) aos dados amostrais. Cada indivíduo representa um par de parâmetros (a, b), que define uma reta candidata no espaço de soluções.

O desempenho de cada indivíduo é medido pela discrepância entre os valores estimados pela função e os valores reais observados no conjunto de dados. Essa discrepância é calculada para todos os pontos e agregada por meio do Erro Quadrático Médio (MSE), obtido a partir da média dos quadrados das diferenças entre os valores reais e previstos.

Com base nesse erro, define-se a função de fitness de cada indivíduo, de modo que soluções com menor erro apresentem maior aptidão. Para isso, utiliza-se uma transformação inversa do erro, garantindo que indivíduos mais ajustados aos dados possuam valores de fitness mais elevados.

---
# Entrada/Saida

A amostra de pontos é lida a partir de um arquivo externo input.dat, que contém os valores de entrada do problema, incluindo o número total de pontos (n), o tamanho da população de indivíduos (m) e a quantidade de gerações a serem simuladas (G). Esses dados são fundamentais para a inicialização do algoritmo e para a execução das etapas evolutivas.

Ao longo da simulação, a cada geração, os resultados são registrados em um arquivo output.dat. Para cada iteração, são armazenados o maior valor de fitness encontrado, o erro associado a esse indivíduo e os respectivos parâmetros (a e b) que definem a melhor solução candidata naquele momento.

---
# Requisitos Técnicos 

O projeto deve ser desenvolvido em C, utilizando manipulação de vetores e matrizes, uso de estruturas dinâmicas, aritmética básica de ponteiros e organização modular de programas em C, com separação em pastas (src, headers). A compilação deverá ser gerenciada via Makefile, e o executável precisa ser compatível com sistemas Linux. Também é exigida uma análise de desempenho para análisar da complexidade das principais rotinas e discussão sobre o comportamento do erro ao longo das gerações.

---
# Entrada de Dados
## Arquivo de entrada (input.dat):
O arquivo de entrada é estruturado da seguinte forma: A primeira linha contem os valores totais da quantidade de numeros de pontos e de indivíduos da população de amostra e a quantidade de gerações de interações do algorítmo, correspondendo as variáveis n, m e G. O restante do arquivo contem os pares de pontos x e y que o algorítimo deve ler. 

---
### Formato do Arquivo de Entrada
```
n m G
x1 y1
x2 y2
...
xn yn
```
### Exemplo (input.dat incluído):
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

---
# Metodologia
A metodologia implementada no projeto é dividida em várias etapas:

---
## LerInputdatDados
```
void LerInputdatDados(FILE *file, Dados *dados);
```
Lê os parâmetros n, m e G da primeira linha do arquivo input.dat e os armazena na struct Dados. Caso a leitura falhe, exibe uma mensagem de erro e encerra o programa.

---
## Gerar População
```
void GerarPopulacao(Individuo *populacao, int m)
```
A função GerarPopulacao é responsável por inicializar a população de indivíduos. Cada indivíduo recebe valores aleatórios para os parâmetros a e b, distribuídos uniformemente no intervalo [0,10]. Essa etapa garante diversidade inicial no espaço de busca, permitindo que o algoritmo explore diferentes soluções desde as primeiras gerações.

---
## Ordenar
```
void Ordenar(Individuo *populacao, Individuo *pais, int m, int quantidade)
```
A função Ordenar realiza a seleção dos indivíduos mais aptos para reprodução. A população é ordenada em ordem decrescente de fitness por meio de um algoritmo de ordenação simples. Em seguida, os melhores indivíduos são copiados para o vetor de pais, garantindo que apenas as soluções mais promissoras sejam utilizadas nas próximas etapas do algoritmo.

---
## Gerar Pontos
```
void GerarPontos(FILE *file, Ponto *pontos, int n);
```
Lê os n pares de coordenadas (x, y) do arquivo de entrada e os armazena no vetor de Ponto. Esses pontos formam o conjunto de dados que o algoritmo tentará aproximar com uma reta.

---
## CalculoErroFitness 

```
void CalculoErroFitness(Individuo *populacao, Dados *dados, Ponto *pontos);
```
Avalia cada indivíduo da população calculando:

- Erro médio quadrático (MSE): média da soma dos quadrados das diferenças entre o valor real y e o valor previsto ax + b.
- Fitness: calculado como `1 / (1 + erro)`, de forma que indivíduos com menor erro possuem fitness mais próximo de 1 (melhor).

---
## Crossover
```
void Crossover(Individuo *populacao, Individuo *pais, Individuo *filhos, Dados dados, int quantidade);
```
Realiza o cruzamento entre pares de pais selecionados aleatoriamente, gerando filhos que combinam os coeficientes, sempre evitando que os pares sejam repetidos e os filhos gerados substituem a pior metade da população atual.:
- `filho[i].a = paiA.a e filho[i].b = paiB.b`

- `filho[i+1].a = paiB.a e filho[i+1].b = paiA.b`

---
## Mutação
```
void Mutacao(Individuo *populacao, int quantidade);
```
Aplica mutações aleatórias em indivíduos da população (excluindo o melhor). Para cada indivíduo, com probabilidade de 50%, um delta aleatório no intervalo [-1, 1] é somado a a ou b. Os valores são mantidos dentro do intervalo [0, 10].

---
# Discussão do erro:
Saida do `output.dat`:
Primeira Geração:
`Melhor fitness:0.244386 |Erro: 3.091892 |a: 1.293038 |b: 4.865410 |`

Ultima Geração:
`Melhor fitness:0.999469 |Erro: 0.000532 |a: 1.989948 |b: 1.046355 |`

Valor estimado para a e b:
`a = 2.0, b = 1.0`

Com isso concluimos que o algoritmo convergiu com sucesso para uma solução muito próxima da reta real `y = 2x + 1`, atingindo fitness de 0.997 ao final das 500 gerações.

---
## Comportamento por fases:
Fase 1 — Convergência inicial agressiva (gerações 1–9): Partindo de um ponto inicial ruim (b = 4.87), o erro cai de 3.09 para 0.055 em apenas 9 gerações — redução de 98.2%. A maior diversidade genética do intervalo [-10, 10] permite saltos maiores logo no início.

Fase 2 — Estagnação intermediária (gerações 9–60): O fitness estabiliza em torno de 0.954 por aproximadamente 50 gerações. O algoritmo encontrou uma boa solução local mas perdeu diversidade genética rapidamente.

Fase 3 — Refinamento progressivo (gerações 60–500): Diferentemente da versão anterior com intervalo [0, 10], aqui o refinamento é mais consistente e contínuo, com saltos de melhoria distribuídos ao longo de toda esta fase. O algoritmo conseguiu continuar evoluindo até gerações muito tardias (geração ~480), atingindo erro final de apenas 0.00053 — 5× menor que na versão anterior.

---
## Conclusões

- O intervalo [-10, 10] produziu resultados superiores. Apesar de partir de um ponto inicial mais distante do ótimo (b = 4.87 vs b = 2.50), a versão final terminou com erro 5× menor (0.00053 contra 0.00271) e fitness mais alto (0.9995 contra 0.9973).
- Maior diversidade inicial sustenta o refinamento por mais gerações. Na versão final, melhorias ocorrem até a geração ~480, enquanto na versão anterior o algoritmo estagnava definitivamente por volta da geração 390. A amplitude maior do espaço de busca mantém variabilidade genética útil por mais tempo.
- a converge antes de b em ambas as versões. A paisagem de fitness é estruturalmente mais sensível à inclinação (a) do que ao intercepto (b), um comportamento consistente independente do intervalo de inicialização.
- A solução final é muito próxima do ótimo. a = 1.990 e b = 1.046 representam desvios de apenas 0.5% e 4.6% em relação aos valores ideais a = 2.0 e b = 1.0.
- A convergência prematura persiste, mas é menos severa. A maior estagnação observada foi de ~90 gerações seguidas sem melhoria (gerações 390–480), depois da qual o algoritmo ainda encontrou um salto final.

---
## Possíveis melhorias

- Mutação adaptativa: reduzir o delta de mutação conforme o fitness aumenta, permitindo ajuste mais fino nas gerações finais onde o erro já é pequeno.
- Critério de parada antecipada: interromper a execução quando não houver melhoria por N gerações consecutivas, economizando processamento nas longas estagnações.
- Maior população: aumentar m além de 20 indivíduos para retardar a perda de diversidade genética e reduzir a frequência de estagnações.

---
## Observações
- A semente aleatória está fixada em srand(42) para garantir reprodutibilidade dos resultados.
- O Makefile utiliza -gcc como compilador; altere para gcc caso necessário.
- Os coeficientes a e b são gerados e mantidos no intervalo [-10, 10].
- 
---

# Como Compilar e Executar

Este projeto utiliza **Makefile** para facilitar a compilação. Para limpar, compilar e executar em sequência, utilize:

```
make clean && make && make run
```

Para apenas executar o executável já compilado:

```
./build/app
```
---

# Análise de Complexidade das Principais Rotinas

As variáveis utilizadas na análise são:

- **n** — número de pontos do dataset
- **m** — tamanho da população
- **G** — número de gerações
- **quantidade** = m/2 — número de pais/filhos selecionados por geração

---

## `LerInputdatDados` — `pontos.c`

Realiza uma única leitura de 3 inteiros do arquivo de entrada (`n`, `m`, `G`).

| | Complexidade |
|-|---|
| **Tempo** | O(1) |
| **Espaço** | O(1) |

---

## `GerarPontos` — `pontos.c`

```c
for (int i = 0; i < n; i++) {
    fscanf(file, "%f %f", &pontos[i].x, &pontos[i].y);
}
```

Itera uma única vez sobre os `n` pontos, lendo as coordenadas `x` e `y` de cada um.

| | Complexidade |
|-|---|
| **Tempo** | O(n) |
| **Espaço** | O(n) |

---

## `GerarPopulacao` — `individuos.c`

```c
for (int i = 0; i < m; i++) {
    populacao[i].a = ((float)rand() / RAND_MAX) * 20 - 10;
    populacao[i].b = ((float)rand() / RAND_MAX) * 20 - 10;
}
```

Itera uma única vez sobre os `m` indivíduos, atribuindo valores aleatórios a `a` e `b` no intervalo `[-10, 10]`.

| | Complexidade |
|-|---|
| **Tempo** | O(m) |
| **Espaço** | O(m) |

---

## `CalculoErroFitness` — `operacoes.c`

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

Para cada um dos `m` indivíduos, calcula o erro quadrático médio em relação a todos os `n` pontos e deriva o valor de fitness.

Esta função é chamada **duas vezes por geração** no loop principal, tornando-a a rotina mais custosa do algoritmo.

| | Complexidade |
|-|---|
| **Tempo** | O(m × n) |
| **Espaço** | O(1) auxiliar |

---

## `Ordenar` — `individuos.c`

```c
// Selection Sort sobre a população
for (int i = 0; i < m; i++) {
    int posicaomax = i;
    for (int j = i; j < m; j++) {
        if (populacao[j].fitness > populacao[posicaomax].fitness)
            posicaomax = j;
    }
    // troca
}
// cópia dos m/2 melhores para o vetor de pais
for (int i = 0; i < quantidade; i++) {
    pais[i] = populacao[i];
}
```

Implementa **Selection Sort** sobre os `m` indivíduos (ordenação decrescente por fitness), seguido de uma cópia dos `m/2` melhores para o vetor de pais.

| | Complexidade |
|-|---|
| **Tempo** | O(m²) |
| **Espaço** | O(m) auxiliar |

---

## `Crossover` — `operacoes.c`

A função é composta por três etapas:

**1. Seleção de pares únicos de pais:**
```c
for (int i = 0; i < quantidade; i += 2) {
    do {
        // sorteia paiA e paiB
        for (int j = 0; j < i; j += 2) {
            // verifica se o par já foi usado
        }
    } while (repetido);
}
```
No pior caso, para cada novo par gerado todos os pares anteriores são verificados → O(quantidade²) = **O(m²/4)**

**2. Geração dos filhos** — troca de `a` e `b` entre cada par de pais → O(m)

**3. Substituição dos piores** — os filhos substituem a segunda metade da população → O(m)

| | Complexidade |
|-|---|
| **Tempo** | O(m²) |
| **Espaço** | O(m) auxiliar |

Para populações grandes, a verificação de pares repetidos pode se tornar um gargalo. Para o tamanho usado no exemplo (`m=20`), o impacto é negligenciável.

---

## `Mutacao` — `operacoes.c`

```c
for (int i = 1; i < quantidade; i++) {
    if (rand() % 2 == 0) {
        // altera a ou b com probabilidade 50%
    }
}
```

Percorre os `m/2` indivíduos da segunda metade da população. Com probabilidade 50%, aplica uma perturbação aleatória `delta ∈ [-1, 1]` em `a` ou `b`, respeitando os limites `[-10, 10]`.

| | Complexidade |
|-|---|
| **Tempo** | O(m) |
| **Espaço** | O(1) |

---

## Loop Principal — `trabalho1.c`

```c
for (int i = 0; i < G; i++) {
    CalculoErroFitness(...);   // O(m × n)
    Ordenar(...);              // O(m²)
    Crossover(...);            // O(m²)
    Mutacao(...);              // O(m)
    CalculoErroFitness(...);   // O(m × n)  ← chamada novamente após crossover/mutação
}
```

Por geração, o custo dominante é **O(m² + m×n)**.

Ao longo de todas as `G` gerações:

$$T(G, m, n) = O\bigl(G \times (m^2 + m \cdot n)\bigr)$$

| | Complexidade |
|-|---|
| **Tempo total** | **O(G × (m² + m·n))** |
| **Espaço total** | **O(m + n)** |

---

## Resumo das Complexidades

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

# Fluxo do Algorítmo
```
Início
  │
  ├─ Leitura dos parâmetros e pontos (input.dat)
  │
  ├─ Geração da população inicial (aleatória)
  │
  └─ Loop por G gerações:
        ├─ Cálculo de Erro e Fitness (CalculoErroFitness)
        ├─ Seleção dos melhores pais (Ordenar)
        ├─ Cruzamento → geração de filhos (Crossover)
        ├─ Mutação nos filhos (Mutacao)
        ├─ Recálculo de Fitness (CalculoErroFitness)
        └─ Registro do melhor indivíduo (output.dat)
```


# Estrutura do Projeto

```
Trabalho1AEDSI/
├── src/
│   ├── trabalho1.h       # Definições de structs e protótipos
│   ├── trabalho1.c       # Função principal (main)
│   ├── individuos.c      # GerarPopulacao e Ordenar
│   ├── operacoes.c       # CalculoErroFitness, Crossover e Mutacao
│   └── pontos.c          # LerInputdatDados e GerarPontos
├── config/
│   ├── input.dat         # Parâmetros e pontos de entrada
│   └── output.dat        # Resultados por geração
├── build/
│   └── app               # Executável compilado
└── Makefile
```

# Ambiente de Teste

# Creditos
Arquivo Makefile concedido pelo professor Michel Pires.

# Autor
Gabriel Alves Faria.
