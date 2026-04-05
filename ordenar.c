/*
Aluno: Abdiel Abadio Gouveia Silva
Disciplina: Estrutura de Dados
Prova: Questao sobre comercio
Data de entrega: 05/04/2026
Arquivo: ordenar.c
Descricao: implementa os algoritmos basicos de ordenacao (insercao, selecao e bolha).
*/

#include "ordenar.h"

void insercao(Produto *produtos, int tam, ComparadorProduto comparar) {
    int i;
    for (i = 1; i < tam; i++) {
        Produto atual = produtos[i];
        int j = i - 1;
        while (j >= 0 && comparar(&produtos[j], &atual) > 0) {
            produtos[j + 1] = produtos[j];
            j--;
        }
        produtos[j + 1] = atual;
    }
}

void bubble(Produto *produtos, int tam, ComparadorProduto comparar) {
    int i, j;
    for (i = 0; i < tam - 1; i++) {
        for (j = 0; j < tam - 1 - i; j++) {
            if (comparar(&produtos[j], &produtos[j + 1]) > 0) {
                Produto aux = produtos[j];
                produtos[j] = produtos[j + 1];
                produtos[j + 1] = aux;
            }
        }
    }
}

void selecao(Produto *produtos, int tam, ComparadorProduto comparar) {
    int i, j, min;

    for (i = 0; i < tam - 1; i++) {
        min = i;
        for (j = i + 1; j < tam; j++) {
            if (comparar(&produtos[j], &produtos[min]) < 0) {
                min = j;
            }
        }

        if (min != i) {
            Produto aux = produtos[i];
            produtos[i] = produtos[min];
            produtos[min] = aux;
        }
    }
}