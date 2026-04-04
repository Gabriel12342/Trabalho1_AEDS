#include <stdio.h>
#include <stdlib.h>
#include "trabalho1.h"

void GerarPopulacao(Individuo *populacao, int m){
    for (int i = 0; i < m; i++){
        populacao[i].a = ((float)rand() / RAND_MAX) * 20-10; // entre -10 e 10 
        populacao[i].b = ((float)rand() / RAND_MAX) * 20-10;
    }
}

void CalculoErroFitness(Individuo *populacao, Dados *dados, Ponto *pontos){
    float yreal, yprev, erro;

    for (int i = 0; i < dados->m; i++){
        float somatorio = 0;
        for (int j = 0; j < dados->n; j++){
            yreal = pontos[j].y;
            yprev = populacao[i].a * pontos[j].x + populacao[i].b;
            erro = yreal - yprev;
            somatorio += erro * erro;
        }

        populacao[i].erro = somatorio / dados->n;

        populacao[i].fitness = 1.0 / (1.0 + populacao[i].erro);
    }
}

void CrossOrMuta(Individuo *populacao, Individuo *pais, Individuo *filhos, int quantidade, int m){

    Individuo paisCross[quantidade];
    Individuo paisMuta[quantidade];

    int nCross = 0, nMuta = 0;

    // separa quem faz o que
    for (int i = 0; i < quantidade; i++){

        if (i == 0){
            paisCross[nCross++] = pais[i]; // melhor sempre cruza
        }
        else if ((rand()%100) < 50){
            paisCross[nCross++] = pais[i];
        } else{
            paisMuta[nMuta++] = pais[i];
        }
    }

    // faz crossover só com quem foi selecionado
    if (nCross >= 2){
        Crossover(populacao, paisCross, filhos, m, nCross);
    }

    // mutação
    Mutacao(paisMuta, nMuta);

    // recoloca mutados na parte dos pais
    for (int i = 0; i < nMuta; i++){
        populacao[i + (nCross)] = paisMuta[i];
    }
}

void Mutacao(Individuo *individuos, int nMuta){

    for (int i = 0; i < nMuta; i++){   

        float delta = ((float)rand() / RAND_MAX) * 2 - 1;

        if(rand() % 2 == 0){
                individuos[i].a += delta;
        } else {
                individuos[i].b += delta;
        } 
              
    }
}