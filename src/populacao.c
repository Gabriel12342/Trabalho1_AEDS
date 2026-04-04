#include<stdio.h>
#include<stdlib.h>
#include "trabalho1.h"

void SelecionarPais(Individuo *populacao, Individuo *pais, int m, int quantidade){
    
    if (m < 2){
        printf("População muito pequena\n");
        exit(1);
    }

    for (int i = 0; i < m; i++){
        int posicaomax = i;
        for (int j = i; j < m; j++){
            if (populacao[j].fitness > populacao[posicaomax].fitness){
                posicaomax = j;
            }
        }
        // troca
        Individuo temp = populacao[i];
        populacao[i] = populacao[posicaomax];
        populacao[posicaomax] = temp;
    }
    // pegar metade dos pais
    for (int i = 0; i < quantidade; i++){
        pais[i] = populacao[i];
    }
}

void Crossover(Individuo *populacao, Individuo *pais, Individuo *filhos, int m, int nCross){

    for (int i = 0; i < nCross; i++){
        int paiA = rand() % nCross;
        int paiB = (paiA + rand() % (nCross - 1) + 1) % nCross;

        if (rand() % 2 == 0){
            filhos[i].a = pais[paiA].a;
            filhos[i].b = pais[paiB].b;
        } else {
            filhos[i].a = pais[paiB].a;
            filhos[i].b = pais[paiA].b;
        }
    }

    // substituir os piores
    for (int i = 0; i < nCross; i++){
        populacao[m - 1 - i] = filhos[i];
    }
}