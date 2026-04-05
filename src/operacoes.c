#include <stdio.h>
#include <stdlib.h>
#include "trabalho1.h"

//---------------------------------------------------------------------------------------------------------------

void CalculoErroFitness(Individuo *populacao, Dados *dados, Ponto *pontos)
{

    float yreal, yprev, erro;

    for (int i = 0; i < dados->m; i++)
    {

        float somatorio = 0;

        for (int j = 0; j < dados->n; j++)
        {

            yreal = pontos[j].y;
            yprev = populacao[i].a * pontos[j].x + populacao[i].b;
            erro = yreal - yprev;
            somatorio += erro * erro;
        }

        populacao[i].erro = somatorio / dados->n;

        populacao[i].fitness = 1.0 / (1.0 + populacao[i].erro);
    }
}

//---------------------------------------------------------------------------------------------------------------
void Crossover(Individuo *populacao, Individuo *pais, Individuo *filhos, Dados dados, int quantidade)
{

    int par_pais[dados.m];

    for (int i = 0; i < quantidade; i += 2)
    {

        int paiA, paiB, repetido;

        do
        {

            repetido = 0;

            paiA = rand() % quantidade;

            paiB = rand() % quantidade;

           
            do{

                paiB = rand() % quantidade;
            } while (paiA == paiB);

            for (int j = 0; j < i; j += 2)
            {

                if ((par_pais[j] == paiA && par_pais[j + 1] == paiB) || (par_pais[j] == paiB && par_pais[j + 1] == paiA))
                {

                    repetido = 1;
                    break;
                }
            }

        } while (repetido);

        par_pais[i] = paiA;
        par_pais[i + 1] = paiB;
    }

    int c = 0;

    for (int i = 0; i < quantidade; i += 2)
    {

        filhos[i].a = pais[par_pais[c]].a;
        filhos[i].b = pais[par_pais[c + 1]].b;

        filhos[i + 1].a = pais[par_pais[c + 1]].a;
        filhos[i + 1].b = pais[par_pais[c]].b;

        c += 2;
    }

    // substituir os piores
    for (int i = 0; i < quantidade; i++)
    {
        populacao[quantidade + i] = filhos[i];
    }

}

//---------------------------------------------------------------------------------------------------------------

void Mutacao(Individuo *populacao, int quantidade){

    for (int i = 1; i < quantidade; i++){

        if(rand() % 2 == 0){

            float temp = 0;

            float delta = ((float)rand() / RAND_MAX) * 2 - 1;

            if (rand() % 2 == 0)
            {
                temp = populacao[i].a;
                temp += delta;

                if (temp < 10 && temp >= -10)
                {
                    populacao[i].a += delta;
                }
                else if (temp >= 10)
                {
                    populacao[i].a = 10;
                }
                else
                {
                    populacao[i].a = -10;
                }
            }
            else
            {
                temp = populacao[i].b;
                temp += delta;

                if (temp < 10 && temp >= -10)
                {
                    populacao[i].b += delta;
                }
                else if (temp >= 10)
                {
                    populacao[i].b = 10;
                }
                else
                {
                    populacao[i].b = -10;
                }
            }
        }
    }
}
