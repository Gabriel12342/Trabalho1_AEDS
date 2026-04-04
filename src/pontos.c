#include<stdio.h>
#include<stdlib.h>
#include "trabalho1.h"

void LerInputdatDados(FILE *file, Dados *dados){
    if (fscanf(file, "%d %d %d", &dados->n, &dados->m, &dados->G) != 3){
        printf("Erro ao ler n, m, G\n");
        exit(1);
    }
}

void GerarPontos(FILE *file, Ponto *pontos, int n){
    for (int i = 0; i < n; i++){
        if (fscanf(file, "%f %f", &pontos[i].x, &pontos[i].y) != 2){
            printf("Erro ao ler ponto %d\n", i);
            exit(1);
        }
    }
}