/*
Aluno: Abdiel Abadio Gouveia Silva
Disciplina: Estrutura de Dados
Prova: Questao sobre comercio
Data de entrega: 05/04/2026
Arquivo: ordenacaoComplexa.c
Descricao: implementa os algoritmos sofisticados de ordenacao (merge sort e quick sort).
*/

#include <stdlib.h>
#include "ordenacaoComplexa.h"

void merge(Produto *produtos, int inicio, int meio, int fim, ComparadorProduto comparar) {
    int i = inicio;
    int j = meio + 1;
    int k = 0;
    int tam = fim - inicio + 1;
    Produto *aux = (Produto *)malloc(tam * sizeof(Produto));

    if (aux == NULL) {
        return;
    }

    while (i <= meio && j <= fim) {
        if (comparar(&produtos[i], &produtos[j]) <= 0) {
            aux[k++] = produtos[i++];
        } else {
            aux[k++] = produtos[j++];
        }
    }

    while (i <= meio) {
        aux[k++] = produtos[i++];
    }

    while (j <= fim) {
        aux[k++] = produtos[j++];
    }

    for (k = 0; k < tam; k++) {
        produtos[inicio + k] = aux[k];
    }

    free(aux);
}

void mergeSort(Produto *produtos, int inicio, int fim, ComparadorProduto comparar) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        mergeSort(produtos, inicio, meio, comparar);
        mergeSort(produtos, meio + 1, fim, comparar);
        merge(produtos, inicio, meio, fim, comparar);
    }
}

void quickSort(Produto *produtos, int inicio, int fim, ComparadorProduto comparar) {
    int i, j;
    Produto pivo;

    if (inicio >= fim) {
        return;
    }

    i = inicio;
    j = fim;
    pivo = produtos[(inicio + fim) / 2];

    while (i <= j) {
        while (comparar(&produtos[i], &pivo) < 0) {
            i++;
        }
        while (comparar(&produtos[j], &pivo) > 0) {
            j--;
        }
        if (i <= j) {
            Produto aux = produtos[i];
            produtos[i] = produtos[j];
            produtos[j] = aux;
            i++;
            j--;
        }
    }

    if (inicio < j) {
        quickSort(produtos, inicio, j, comparar);
    }
    if (i < fim) {
        quickSort(produtos, i, fim, comparar);
    }
}