/*
Aluno: Abdiel Abadio Gouveia Silva
Disciplina: Estrutura de Dados
Prova: Questao sobre comercio
Data de entrega: 05/04/2026
Arquivo: ordenacaoComplexa.h
Descricao: declara os algoritmos sofisticados de ordenacao (merge sort e quick sort).
*/

#ifndef ORDENACAO_COMPLEXA_H
#define ORDENACAO_COMPLEXA_H

#include <stdlib.h>
#include <stdio.h>
#include "ordenar.h"

void quickSort(Produto *produtos, int inicio, int fim, ComparadorProduto comparar);
void mergeSort(Produto *produtos, int inicio, int fim, ComparadorProduto comparar);
void merge(Produto *produtos, int inicio, int meio, int fim, ComparadorProduto comparar);

#endif