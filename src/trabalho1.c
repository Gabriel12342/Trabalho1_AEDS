#include <stdio.h>
#include <stdlib.h>
#include "trabalho1.h"

int main(){
/*#############################################################################################################################*/
    srand(42);
    FILE *file, *saida;

    file = fopen("config/input.dat","r");
    if (file == NULL){
        printf("Erro ao abrir arquivo input.dat .\n");
        return(1); 
    }

    Dados dados;
    Individuo *populacao, *pais, *filhos;
    Ponto *pontos;

    LerInputdatDados(file, &dados);
/*#############################################################################################################################*/

    int quantidade = dados.m / 2;

    populacao = malloc(dados.m * sizeof(Individuo));
    pontos = malloc(dados.n * sizeof(Ponto));
    pais = malloc(quantidade * sizeof(Individuo));
    filhos = malloc(quantidade * sizeof(Individuo));

    if ((populacao == NULL) || (pontos == NULL) || (pais == NULL) || (filhos == NULL)){
        printf("Erro de alocar memória.");
        return 1;
    }
    
    // ler pontos
    GerarPontos(file, pontos, dados.n);
    // gerar população
    GerarPopulacao(populacao, dados.m);

    fclose(file);
/*#############################################################################################################################*/
    saida = fopen("config/output.dat", "w");
    if (saida == NULL){
        printf("Erro ao abrir arquivo output.dat.\n");
        return(1);
    }

    for (int i = 0; i < dados.G; i++){
        CalculoErroFitness(populacao, &dados, pontos);

        SelecionarPais(populacao, pais, dados.m, quantidade);

        CrossOrMuta(populacao, pais, filhos, quantidade, dados.m);
            
        CalculoErroFitness(populacao, &dados, pontos);
            //Salva o maior
        int melhor = 0;
        for (int j = 1; j < dados.m; j++){
            if (populacao[j].fitness > populacao[melhor].fitness){
                melhor = j;
            }
        }

        fprintf(saida, "Melhor fitness:%.3f |Erro: %.3f |a: %.3f |b: %.3f |\n", populacao[melhor].fitness, populacao[melhor].erro, populacao[melhor].a, populacao[melhor].b);

    }

    fclose(saida);
/*########################################################################################################################################*/
    free(populacao);
    free(pontos);
    free(pais);
    free(filhos);
/*########################################################################################################################################*/
    return 0;
}