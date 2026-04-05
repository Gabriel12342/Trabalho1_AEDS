#ifndef TRABALHO1_H
#define TRABALHO1_H
#include <stdio.h>

typedef struct{
    float a, b, fitness, erro;
} Individuo;

typedef struct{
    int n, m, G;
} Dados;

typedef struct{
    float x, y;
} Ponto;

void LerInputdatDados(FILE *file, Dados *dados);
void GerarPopulacao(Individuo *populacao, int m);
void GerarPontos(FILE *file, Ponto *pontos, int n);
void CalculoErroFitness(Individuo *populacao, Dados *dados, Ponto *pontos);
void Ordenar(Individuo *populacao, Individuo *pais, int m, int quantidade);
void Crossover(Individuo *populacao, Individuo *pais, Individuo *filhos, Dados dados, int quantidade);
void Mutacao(Individuo *populacao, int quantidade);
#endif