# Trabalho1_AEDS
Trabalho de Aquecimento: Algoritmos Genéticos
## Introdução
Este projeto foi desenvolvido no contexto da disciplina de Análise Estrutural de Dados I (AEDSI), do Centro Federal de Educação Tecnológica de Minas Gerais (CEFET-MG), Campus Divinópolis.

A aplicação consiste na implementação de um Algoritmo Genético (AG) simplificado, voltado para o problema de ajuste de parâmetros a partir de um conjunto de dados. A proposta é explorar como soluções candidatas podem ser representadas, avaliadas e evoluídas iterativamente por meio de operações como seleção, crossover e mutação.

Além da abordagem evolutiva, o projeto também enfatiza aspectos fundamentais da programação em C, como manipulação de memória dinâmica, uso de ponteiros e organização modular do código.

## Problema Proposto

O problema consiste na implementação de um algoritmo genético capaz de ler valores de entrada de um arquivo, contendo uma amostra empírica de pontos (x, y) que permanecem constantes durante toda a execução. Esses dados constituem o espaço amostral sobre o qual as soluções candidatas são avaliadas.

A população inicial é gerada de forma aleatória, sendo estruturada como um conjunto de vetores de dimensão *m* × 2, onde *m* corresponde ao número total de indivíduos e cada vetor representa um indivíduo.

## Funcionalidades
O algoritmo deve ser capaz de ler valores de entrada a partir de um arquivo externo, contendo uma amostra empírica de pontos (*x*, *y*), bem como a quantidade total desses pontos, o tamanho da população de indivíduos a ser simulada e o número de gerações do processo evolutivo. Esses parâmetros permanecem constantes durante toda a execução, constituindo o espaço amostral sobre o qual as soluções candidatas são avaliadas.

A população inicial de indivíduos é gerada por meio de processos pseudoaleatórios, controlados por uma semente (*seed*), garantindo a reprodutibilidade dos experimentos. Dessa forma, diferentes execuções do algoritmo podem ser comparadas de maneira consistente sob as mesmas condições iniciais.

Cada indivíduo representa uma possível solução para o problema e é definido por um conjunto de parâmetros, sendo estruturado como um conjunto de vetores de dimensão *m × 2*, onde *m* corresponde ao número total de indivíduos e cada vetor representa um indivíduo.

## Avaliação
A avaliação dos indivíduos é realizada com base no ajuste de uma função linear (ŷ = ax + b) aos dados amostrais. Cada indivíduo representa um par de parâmetros (a, b), que define uma reta candidata no espaço de soluções.

O desempenho de cada indivíduo é medido pela discrepância entre os valores estimados pela função e os valores reais observados no conjunto de dados. Essa discrepância é calculada para todos os pontos e agregada por meio do Erro Quadrático Médio (MSE), obtido a partir da média dos quadrados das diferenças entre os valores reais e previstos.

Com base nesse erro, define-se a função de fitness de cada indivíduo, de modo que soluções com menor erro apresentem maior aptidão. Para isso, utiliza-se uma transformação inversa do erro, garantindo que indivíduos mais ajustados aos dados possuam valores de fitness mais elevados.

## Entrada/Saida

A amostra de pontos é lida a partir de um arquivo externo input.dat, que contém os valores de entrada do problema, incluindo o número total de pontos (n), o tamanho da população de indivíduos (m) e a quantidade de gerações a serem simuladas (G). Esses dados são fundamentais para a inicialização do algoritmo e para a execução das etapas evolutivas.

Ao longo da simulação, a cada geração, os resultados são registrados em um arquivo output.dat. Para cada iteração, são armazenados o maior valor de fitness encontrado, o erro associado a esse indivíduo e os respectivos parâmetros (a e b) que definem a melhor solução candidata naquele momento.

# Requisitos Técnicos 

O projeto deve ser desenvolvido em C, utilizando manipulação de vetores e matrizes, uso de estruturas dinâmicas, aritmética básica de ponteiros e organização modular de programas em C, com separação em pastas (src, headers). A compilação deverá ser gerenciada via Makefile, e o executável precisa ser compatível com sistemas Linux. Também é exigida uma análise de desempenho para análisar da complexidade das principais rotinas e discussão sobre o comportamento do erro ao longo das gerações.

# Entrada de Dados
## Arquivo de entrada (input.dat):
O arquivo de entrada é estruturado da seguinte forma: A primeira linha contem os valores totais da quantidade de numeros de pontos e de indivíduos da população de amostra e a quantidade de gerações de interações do algorítmo, correspondendo as variáveis n, m e G. O restante do arquivo contem os pares de pontos x e y que o algorítimo deve ler. 

```
n m G
x1 y1
x2 y2
...
xn yn
```

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

# Estrutura do Projeto

Trabalho1AEDSI/
├── build/
│   ├── app              # Executável compilado
│   └── objects/
├── config/
│   ├── input.dat        # Arquivo de entrada (parâmetros + pontos)
│   └── output.dat       # Arquivo de saída gerado após execução
├── src/
│   ├── trabalho1.c      # Função main — fluxo principal do algoritmo
│   ├── funsoes.c        # Implementação de todas as funções do AG
│   └── trabalho1.h      # Declarações de structs e protótipos de funções
└── Makefile             # Script de compilação

