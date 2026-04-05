#include <stdio.h>
#include <stdlib.h>
#include "trabalho1.h"

void GerarPopulacao(Individuo *populacao, int m)
{ // Gera A e B aleatorios

    for (int i = 0; i < m; i++)
    {

        populacao[i].a = ((float)rand() / RAND_MAX) * 20 - 10; // entre -10 e 10
        populacao[i].b = ((float)rand() / RAND_MAX) * 20 - 10;
    }
}

//---------------------------------------------------------------------------------------------------------------

void Ordenar(Individuo *populacao, Individuo *pais, int m, int quantidade)
{

    for (int i = 0; i < m; i++)
    {

        int posicaomax = i;

        for (int j = i; j < m; j++)
        {

            if (populacao[j].fitness > populacao[posicaomax].fitness)
            {

                posicaomax = j;
            }
        }

        // troca
        Individuo temp = populacao[i];
        populacao[i] = populacao[posicaomax];
        populacao[posicaomax] = temp;
    }
    // pegar metade dos pais
    for (int i = 0; i < quantidade; i++)
    {
        pais[i] = populacao[i];
    }
}
//---------------------------------------------------------------------------------------------------------------