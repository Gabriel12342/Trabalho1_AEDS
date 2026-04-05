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

# Problema Proposto

O problema consiste na implementação de um algoritmo genético capaz de ler valores de entrada de um arquivo, contendo uma amostra empírica de pontos (x, y) que permanecem constantes durante toda a execução. Esses dados constituem o espaço amostral sobre o qual as soluções candidatas são avaliadas.

A população inicial é gerada de forma aleatória, sendo estruturada como um conjunto de vetores de dimensão *m* × 2, onde *m* corresponde ao número total de indivíduos e cada vetor representa um indivíduo.

# Funcionalidades
O algoritmo deve ser capaz de ler valores de entrada a partir de um arquivo externo, contendo uma amostra empírica de pontos (*x*, *y*), bem como a quantidade total desses pontos, o tamanho da população de indivíduos a ser simulada e o número de gerações do processo evolutivo. Esses parâmetros permanecem constantes durante toda a execução, constituindo o espaço amostral sobre o qual as soluções candidatas são avaliadas.

A população inicial de indivíduos é gerada por meio de processos pseudoaleatórios, controlados por uma semente (*seed*), garantindo a reprodutibilidade dos experimentos. Dessa forma, diferentes execuções do algoritmo podem ser comparadas de maneira consistente sob as mesmas condições iniciais.

Cada indivíduo representa uma possível solução para o problema e é definido por um conjunto de parâmetros, sendo estruturado como um conjunto de vetores de dimensão *m × 2*, onde *m* corresponde ao número total de indivíduos e cada vetor representa um indivíduo.

# Avaliação
A avaliação dos indivíduos é realizada com base no ajuste de uma função linear (ŷ = ax + b) aos dados amostrais. Cada indivíduo representa um par de parâmetros (a, b), que define uma reta candidata no espaço de soluções.

O desempenho de cada indivíduo é medido pela discrepância entre os valores estimados pela função e os valores reais observados no conjunto de dados. Essa discrepância é calculada para todos os pontos e agregada por meio do Erro Quadrático Médio (MSE), obtido a partir da média dos quadrados das diferenças entre os valores reais e previstos.

Com base nesse erro, define-se a função de fitness de cada indivíduo, de modo que soluções com menor erro apresentem maior aptidão. Para isso, utiliza-se uma transformação inversa do erro, garantindo que indivíduos mais ajustados aos dados possuam valores de fitness mais elevados.

# Entrada/Saida

A amostra de pontos é lida a partir de um arquivo externo input.dat, que contém os valores de entrada do problema, incluindo o número total de pontos (n), o tamanho da população de indivíduos (m) e a quantidade de gerações a serem simuladas (G). Esses dados são fundamentais para a inicialização do algoritmo e para a execução das etapas evolutivas.

Ao longo da simulação, a cada geração, os resultados são registrados em um arquivo output.dat. Para cada iteração, são armazenados o maior valor de fitness encontrado, o erro associado a esse indivíduo e os respectivos parâmetros (a e b) que definem a melhor solução candidata naquele momento.

# Requisitos Técnicos 

O projeto deve ser desenvolvido em C, utilizando manipulação de vetores e matrizes, uso de estruturas dinâmicas, aritmética básica de ponteiros e organização modular de programas em C, com separação em pastas (src, headers). A compilação deverá ser gerenciada via Makefile, e o executável precisa ser compatível com sistemas Linux. Também é exigida uma análise de desempenho para análisar da complexidade das principais rotinas e discussão sobre o comportamento do erro ao longo das gerações.

# Entrada de Dados
## Arquivo de entrada (input.dat):
O arquivo de entrada é estruturado da seguinte forma: A primeira linha contem os valores totais da quantidade de numeros de pontos e de indivíduos da população de amostra e a quantidade de gerações de interações do algorítmo, correspondendo as variáveis n, m e G. O restante do arquivo contem os pares de pontos x e y que o algorítimo deve ler. 

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

# Metodologia
A metodologia implementada no projeto é dividida em várias etapas:

## LerInputdatDados
```
void LerInputdatDados(FILE *file, Dados *dados);
```
Lê os parâmetros n, m e G da primeira linha do arquivo input.dat e os armazena na struct Dados. Caso a leitura falhe, exibe uma mensagem de erro e encerra o programa.

## Gerar População
```
void GerarPopulacao(Individuo *populacao, int m)
```
A função GerarPopulacao é responsável por inicializar a população de indivíduos. Cada indivíduo recebe valores aleatórios para os parâmetros a e b, distribuídos uniformemente no intervalo [0,10]. Essa etapa garante diversidade inicial no espaço de busca, permitindo que o algoritmo explore diferentes soluções desde as primeiras gerações.

## Ordenar
```
void Ordenar(Individuo *populacao, Individuo *pais, int m, int quantidade)
```
A função Ordenar realiza a seleção dos indivíduos mais aptos para reprodução. A população é ordenada em ordem decrescente de fitness por meio de um algoritmo de ordenação simples. Em seguida, os melhores indivíduos são copiados para o vetor de pais, garantindo que apenas as soluções mais promissoras sejam utilizadas nas próximas etapas do algoritmo.

## Gerar Pontos
```
void GerarPontos(FILE *file, Ponto *pontos, int n);
```
Lê os n pares de coordenadas (x, y) do arquivo de entrada e os armazena no vetor de Ponto. Esses pontos formam o conjunto de dados que o algoritmo tentará aproximar com uma reta.

## CalculoErroFitness 

```
void CalculoErroFitness(Individuo *populacao, Dados *dados, Ponto *pontos);
```
Avalia cada indivíduo da população calculando:

- Erro médio quadrático (MSE): média da soma dos quadrados das diferenças entre o valor real y e o valor previsto ax + b.
- Fitness: calculado como `1 / (1 + erro)`, de forma que indivíduos com menor erro possuem fitness mais próximo de 1 (melhor).

## Crossover
```
void Crossover(Individuo *populacao, Individuo *pais, Individuo *filhos, Dados dados, int quantidade);
```
Realiza o cruzamento entre pares de pais selecionados aleatoriamente, gerando filhos que combinam os coeficientes, sempre evitando que os pares sejam repetidos e os filhos gerados substituem a pior metade da população atual.:
- `filho[i].a = paiA.a e filho[i].b = paiB.b`

- `filho[i+1].a = paiB.a e filho[i+1].b = paiA.b`

## Mutação
```
void Mutacao(Individuo *populacao, int quantidade);
```
Aplica mutações aleatórias em indivíduos da população (excluindo o melhor). Para cada indivíduo, com probabilidade de 50%, um delta aleatório no intervalo [-1, 1] é somado a a ou b. Os valores são mantidos dentro do intervalo [0, 10].

# Discussão do erro:
Saida do `output.dat`:
```
Melhor fitness:0.238069 |Erro: 3.200465 |a: 2.062651 |b: 2.501285 |
Melhor fitness:0.806186 |Erro: 0.240408 |a: 2.062651 |b: 0.249239 |
Melhor fitness:0.885488 |Erro: 0.129321 |a: 2.155306 |b: 0.249239 |
Melhor fitness:0.885488 |Erro: 0.129321 |a: 2.155306 |b: 0.249239 |
Melhor fitness:0.953362 |Erro: 0.048920 |a: 2.062651 |b: 0.886333 |
Melhor fitness:0.953362 |Erro: 0.048920 |a: 2.062651 |b: 0.886333 |
Melhor fitness:0.953362 |Erro: 0.048920 |a: 2.062651 |b: 0.886333 |
Melhor fitness:0.953362 |Erro: 0.048920 |a: 2.062651 |b: 0.886333 |
Melhor fitness:0.953362 |Erro: 0.048920 |a: 2.062651 |b: 0.886333 |
Melhor fitness:0.953362 |Erro: 0.048920 |a: 2.062651 |b: 0.886333 |
Melhor fitness:0.953362 |Erro: 0.048920 |a: 2.062651 |b: 0.886333 |
Melhor fitness:0.953362 |Erro: 0.048920 |a: 2.062651 |b: 0.886333 |
Melhor fitness:0.953362 |Erro: 0.048920 |a: 2.062651 |b: 0.886333 |
Melhor fitness:0.953362 |Erro: 0.048920 |a: 2.062651 |b: 0.886333 |
Melhor fitness:0.953362 |Erro: 0.048920 |a: 2.062651 |b: 0.886333 |
Melhor fitness:0.953362 |Erro: 0.048920 |a: 2.062651 |b: 0.886333 |
Melhor fitness:0.953362 |Erro: 0.048920 |a: 2.062651 |b: 0.886333 |
Melhor fitness:0.953362 |Erro: 0.048920 |a: 2.062651 |b: 0.886333 |
Melhor fitness:0.953362 |Erro: 0.048920 |a: 2.062651 |b: 0.886333 |
Melhor fitness:0.953362 |Erro: 0.048920 |a: 2.062651 |b: 0.886333 |
Melhor fitness:0.953362 |Erro: 0.048920 |a: 2.062651 |b: 0.886333 |
Melhor fitness:0.953362 |Erro: 0.048920 |a: 2.062651 |b: 0.886333 |
Melhor fitness:0.953362 |Erro: 0.048920 |a: 2.062651 |b: 0.886333 |
Melhor fitness:0.970719 |Erro: 0.030164 |a: 2.062651 |b: 0.620308 |
Melhor fitness:0.970719 |Erro: 0.030164 |a: 2.062651 |b: 0.620308 |
Melhor fitness:0.975495 |Erro: 0.025120 |a: 2.062651 |b: 0.785248 |
Melhor fitness:0.975495 |Erro: 0.025120 |a: 2.062651 |b: 0.785248 |
Melhor fitness:0.975495 |Erro: 0.025120 |a: 2.062651 |b: 0.785248 |
Melhor fitness:0.975495 |Erro: 0.025120 |a: 2.062651 |b: 0.785248 |
Melhor fitness:0.978227 |Erro: 0.022257 |a: 2.062651 |b: 0.677446 |
Melhor fitness:0.978227 |Erro: 0.022257 |a: 2.062651 |b: 0.677446 |
Melhor fitness:0.978227 |Erro: 0.022257 |a: 2.062651 |b: 0.677446 |
Melhor fitness:0.978227 |Erro: 0.022257 |a: 2.062651 |b: 0.677446 |
Melhor fitness:0.978572 |Erro: 0.021897 |a: 2.062651 |b: 0.753989 |
Melhor fitness:0.978572 |Erro: 0.021897 |a: 2.062651 |b: 0.753989 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979356 |Erro: 0.021079 |a: 2.062651 |b: 0.696354 |
Melhor fitness:0.979606 |Erro: 0.020818 |a: 2.062651 |b: 0.732589 |
Melhor fitness:0.979606 |Erro: 0.020818 |a: 2.062651 |b: 0.732589 |
Melhor fitness:0.979606 |Erro: 0.020818 |a: 2.062651 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.982242 |Erro: 0.018079 |a: 2.058663 |b: 0.732589 |
Melhor fitness:0.985489 |Erro: 0.014725 |a: 2.046894 |b: 0.732589 |
Melhor fitness:0.985489 |Erro: 0.014725 |a: 2.046894 |b: 0.732589 |
Melhor fitness:0.985489 |Erro: 0.014725 |a: 2.046894 |b: 0.732589 |
Melhor fitness:0.985489 |Erro: 0.014725 |a: 2.046894 |b: 0.732589 |
Melhor fitness:0.985489 |Erro: 0.014725 |a: 2.046894 |b: 0.732589 |
Melhor fitness:0.985489 |Erro: 0.014725 |a: 2.046894 |b: 0.732589 |
Melhor fitness:0.985489 |Erro: 0.014725 |a: 2.046894 |b: 0.732589 |
Melhor fitness:0.985489 |Erro: 0.014725 |a: 2.046894 |b: 0.732589 |
Melhor fitness:0.985489 |Erro: 0.014725 |a: 2.046894 |b: 0.732589 |
Melhor fitness:0.985489 |Erro: 0.014725 |a: 2.046894 |b: 0.732589 |
Melhor fitness:0.985489 |Erro: 0.014725 |a: 2.046894 |b: 0.732589 |
Melhor fitness:0.985489 |Erro: 0.014725 |a: 2.046894 |b: 0.732589 |
Melhor fitness:0.985489 |Erro: 0.014725 |a: 2.046894 |b: 0.732589 |
Melhor fitness:0.985489 |Erro: 0.014725 |a: 2.046894 |b: 0.732589 |
Melhor fitness:0.985489 |Erro: 0.014725 |a: 2.046894 |b: 0.732589 |
Melhor fitness:0.985489 |Erro: 0.014725 |a: 2.046894 |b: 0.732589 |
Melhor fitness:0.985489 |Erro: 0.014725 |a: 2.046894 |b: 0.732589 |
Melhor fitness:0.985489 |Erro: 0.014725 |a: 2.046894 |b: 0.732589 |
Melhor fitness:0.985489 |Erro: 0.014725 |a: 2.046894 |b: 0.732589 |
Melhor fitness:0.985489 |Erro: 0.014725 |a: 2.046894 |b: 0.732589 |
Melhor fitness:0.985489 |Erro: 0.014725 |a: 2.046894 |b: 0.732589 |
Melhor fitness:0.985489 |Erro: 0.014725 |a: 2.046894 |b: 0.732589 |
Melhor fitness:0.985489 |Erro: 0.014725 |a: 2.046894 |b: 0.732589 |
Melhor fitness:0.985886 |Erro: 0.014316 |a: 2.046894 |b: 0.736334 |
Melhor fitness:0.985886 |Erro: 0.014316 |a: 2.046894 |b: 0.736334 |
Melhor fitness:0.985886 |Erro: 0.014316 |a: 2.046894 |b: 0.736334 |
Melhor fitness:0.985886 |Erro: 0.014316 |a: 2.046894 |b: 0.736334 |
Melhor fitness:0.985886 |Erro: 0.014316 |a: 2.046894 |b: 0.736334 |
Melhor fitness:0.985886 |Erro: 0.014316 |a: 2.046894 |b: 0.736334 |
Melhor fitness:0.985886 |Erro: 0.014316 |a: 2.046894 |b: 0.736334 |
Melhor fitness:0.988587 |Erro: 0.011545 |a: 2.046894 |b: 0.789679 |
Melhor fitness:0.988587 |Erro: 0.011545 |a: 2.046894 |b: 0.789679 |
Melhor fitness:0.988587 |Erro: 0.011545 |a: 2.046894 |b: 0.789679 |
Melhor fitness:0.988587 |Erro: 0.011545 |a: 2.046894 |b: 0.789679 |
Melhor fitness:0.988587 |Erro: 0.011545 |a: 2.046894 |b: 0.789679 |
Melhor fitness:0.988587 |Erro: 0.011545 |a: 2.046894 |b: 0.789679 |
Melhor fitness:0.988587 |Erro: 0.011545 |a: 2.046894 |b: 0.789679 |
Melhor fitness:0.988587 |Erro: 0.011545 |a: 2.046894 |b: 0.789679 |
Melhor fitness:0.988587 |Erro: 0.011545 |a: 2.046894 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989831 |Erro: 0.010273 |a: 2.043877 |b: 0.789679 |
Melhor fitness:0.989947 |Erro: 0.010155 |a: 2.043877 |b: 0.795653 |
Melhor fitness:0.989947 |Erro: 0.010155 |a: 2.043877 |b: 0.795653 |
Melhor fitness:0.989947 |Erro: 0.010155 |a: 2.043877 |b: 0.795653 |
Melhor fitness:0.989992 |Erro: 0.010109 |a: 2.043877 |b: 0.801250 |
Melhor fitness:0.989992 |Erro: 0.010109 |a: 2.043877 |b: 0.801250 |
Melhor fitness:0.989992 |Erro: 0.010109 |a: 2.043877 |b: 0.801250 |
Melhor fitness:0.989992 |Erro: 0.010109 |a: 2.043877 |b: 0.801250 |
Melhor fitness:0.989992 |Erro: 0.010109 |a: 2.043877 |b: 0.801250 |
Melhor fitness:0.989992 |Erro: 0.010109 |a: 2.043877 |b: 0.801250 |
Melhor fitness:0.989992 |Erro: 0.010109 |a: 2.043877 |b: 0.801250 |
Melhor fitness:0.990512 |Erro: 0.009578 |a: 2.027544 |b: 0.801250 |
Melhor fitness:0.990512 |Erro: 0.009578 |a: 2.027544 |b: 0.801250 |
Melhor fitness:0.990512 |Erro: 0.009578 |a: 2.027544 |b: 0.801250 |
Melhor fitness:0.990512 |Erro: 0.009578 |a: 2.027544 |b: 0.801250 |
Melhor fitness:0.990512 |Erro: 0.009578 |a: 2.027544 |b: 0.801250 |
Melhor fitness:0.990512 |Erro: 0.009578 |a: 2.027544 |b: 0.801250 |
Melhor fitness:0.990512 |Erro: 0.009578 |a: 2.027544 |b: 0.801250 |
Melhor fitness:0.990512 |Erro: 0.009578 |a: 2.027544 |b: 0.801250 |
Melhor fitness:0.990512 |Erro: 0.009578 |a: 2.027544 |b: 0.801250 |
Melhor fitness:0.990512 |Erro: 0.009578 |a: 2.027544 |b: 0.801250 |
Melhor fitness:0.990512 |Erro: 0.009578 |a: 2.027544 |b: 0.801250 |
Melhor fitness:0.990512 |Erro: 0.009578 |a: 2.027544 |b: 0.801250 |
Melhor fitness:0.990512 |Erro: 0.009578 |a: 2.027544 |b: 0.801250 |
Melhor fitness:0.990512 |Erro: 0.009578 |a: 2.027544 |b: 0.801250 |
Melhor fitness:0.990512 |Erro: 0.009578 |a: 2.027544 |b: 0.801250 |
Melhor fitness:0.990512 |Erro: 0.009578 |a: 2.027544 |b: 0.801250 |
Melhor fitness:0.993626 |Erro: 0.006415 |a: 2.027544 |b: 0.826735 |
Melhor fitness:0.993626 |Erro: 0.006415 |a: 2.027544 |b: 0.826735 |
Melhor fitness:0.993626 |Erro: 0.006415 |a: 2.027544 |b: 0.826735 |
Melhor fitness:0.993626 |Erro: 0.006415 |a: 2.027544 |b: 0.826735 |
Melhor fitness:0.993626 |Erro: 0.006415 |a: 2.027544 |b: 0.826735 |
Melhor fitness:0.993626 |Erro: 0.006415 |a: 2.027544 |b: 0.826735 |
Melhor fitness:0.993626 |Erro: 0.006415 |a: 2.027544 |b: 0.826735 |
Melhor fitness:0.994718 |Erro: 0.005310 |a: 2.027544 |b: 0.839625 |
Melhor fitness:0.994718 |Erro: 0.005310 |a: 2.027544 |b: 0.839625 |
Melhor fitness:0.994718 |Erro: 0.005310 |a: 2.027544 |b: 0.839625 |
Melhor fitness:0.994718 |Erro: 0.005310 |a: 2.027544 |b: 0.839625 |
Melhor fitness:0.994718 |Erro: 0.005310 |a: 2.027544 |b: 0.839625 |
Melhor fitness:0.994718 |Erro: 0.005310 |a: 2.027544 |b: 0.839625 |
Melhor fitness:0.994718 |Erro: 0.005310 |a: 2.027544 |b: 0.839625 |
Melhor fitness:0.994718 |Erro: 0.005310 |a: 2.027544 |b: 0.839625 |
Melhor fitness:0.994718 |Erro: 0.005310 |a: 2.027544 |b: 0.839625 |
Melhor fitness:0.994718 |Erro: 0.005310 |a: 2.027544 |b: 0.839625 |
Melhor fitness:0.994718 |Erro: 0.005310 |a: 2.027544 |b: 0.839625 |
Melhor fitness:0.994718 |Erro: 0.005310 |a: 2.027544 |b: 0.839625 |
Melhor fitness:0.994718 |Erro: 0.005310 |a: 2.027544 |b: 0.839625 |
Melhor fitness:0.994718 |Erro: 0.005310 |a: 2.027544 |b: 0.839625 |
Melhor fitness:0.994718 |Erro: 0.005310 |a: 2.027544 |b: 0.839625 |
Melhor fitness:0.994718 |Erro: 0.005310 |a: 2.027544 |b: 0.839625 |
Melhor fitness:0.994718 |Erro: 0.005310 |a: 2.027544 |b: 0.839625 |
Melhor fitness:0.994718 |Erro: 0.005310 |a: 2.027544 |b: 0.839625 |
Melhor fitness:0.994718 |Erro: 0.005310 |a: 2.027544 |b: 0.839625 |
Melhor fitness:0.994718 |Erro: 0.005310 |a: 2.027544 |b: 0.839625 |
Melhor fitness:0.995914 |Erro: 0.004103 |a: 2.027544 |b: 0.865103 |
Melhor fitness:0.995914 |Erro: 0.004103 |a: 2.027544 |b: 0.865103 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.995973 |Erro: 0.004043 |a: 2.027544 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996429 |Erro: 0.003584 |a: 2.022537 |b: 0.868290 |
Melhor fitness:0.996569 |Erro: 0.003443 |a: 2.022537 |b: 0.870721 |
Melhor fitness:0.996569 |Erro: 0.003443 |a: 2.022537 |b: 0.870721 |
Melhor fitness:0.996569 |Erro: 0.003443 |a: 2.022537 |b: 0.870721 |
Melhor fitness:0.996569 |Erro: 0.003443 |a: 2.022537 |b: 0.870721 |
Melhor fitness:0.996569 |Erro: 0.003443 |a: 2.022537 |b: 0.870721 |
Melhor fitness:0.996569 |Erro: 0.003443 |a: 2.022537 |b: 0.870721 |
Melhor fitness:0.996569 |Erro: 0.003443 |a: 2.022537 |b: 0.870721 |
Melhor fitness:0.996569 |Erro: 0.003443 |a: 2.022537 |b: 0.870721 |
Melhor fitness:0.996569 |Erro: 0.003443 |a: 2.022537 |b: 0.870721 |
Melhor fitness:0.996569 |Erro: 0.003443 |a: 2.022537 |b: 0.870721 |
Melhor fitness:0.996569 |Erro: 0.003443 |a: 2.022537 |b: 0.870721 |
Melhor fitness:0.996569 |Erro: 0.003443 |a: 2.022537 |b: 0.870721 |
Melhor fitness:0.996569 |Erro: 0.003443 |a: 2.022537 |b: 0.870721 |
Melhor fitness:0.996569 |Erro: 0.003443 |a: 2.022537 |b: 0.870721 |
Melhor fitness:0.996569 |Erro: 0.003443 |a: 2.022537 |b: 0.870721 |
Melhor fitness:0.996569 |Erro: 0.003443 |a: 2.022537 |b: 0.870721 |
Melhor fitness:0.996569 |Erro: 0.003443 |a: 2.022537 |b: 0.870721 |
Melhor fitness:0.996569 |Erro: 0.003443 |a: 2.022537 |b: 0.870721 |
Melhor fitness:0.996569 |Erro: 0.003443 |a: 2.022537 |b: 0.870721 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
Melhor fitness:0.997297 |Erro: 0.002710 |a: 2.022537 |b: 0.905171 |
```



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
```
