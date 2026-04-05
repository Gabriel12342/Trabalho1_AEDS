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
void Crossover(Individuo *populacao, Individuo *pais, Individuo *filhos, int quantidade)
{

    int par_pais[(quantidade/2) * 2];

    for (int i = 0; i < (quantidade/2); i ++)
    {

        int paiA, paiB, repetido;

        do
        {

            repetido = 0;

            paiA = rand() % quantidade;

            do
            {

                paiB = rand() % quantidade;
            } while (paiA == paiB);

            for (int j = 0; j < i; j ++)
            {

                if ((par_pais[j*2] == paiA && par_pais[(j*2) + 1] == paiB) || (par_pais[j*2] == paiB && par_pais[(j*2) + 1] == paiA))
                {

                    repetido = 1;
                    break;
                }
            }

        } while (repetido);

        par_pais[i*2] = paiA;
        par_pais[(i*2) + 1] = paiB;
    }

    

   int j = 0;

    for (int i = 0; i < quantidade/2; i ++)
    {
        int pai1 = par_pais[j];
        int pai2 = par_pais[j+1];

        filhos[i].a = pais[pai1].a;
        filhos[i].b = pais[pai2].b;

        filhos[i+1].a = pais[pai2].a;
        filhos[i+1].b = pais[pai1].b;

        j += 2;
    }


    // substituir os piores
    for (int i = 0; i < quantidade; i++)
    {
        populacao[quantidade + i] = filhos[i];
    }
}

//---------------------------------------------------------------------------------------------------------------

void Mutacao(Individuo *populacao, int quantidade)
{

    for (int i = 1; i < quantidade; i++)
    {

        if (rand() % 2 == 0)
        {

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
