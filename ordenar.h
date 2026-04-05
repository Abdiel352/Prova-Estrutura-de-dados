/*
Aluno: Abdiel Abadio Gouveia Silva
Disciplina: Estrutura de Dados
Prova: Questao sobre comercio
Data de entrega: 05/04/2026
Arquivo: ordenar.h
Descricao: declara os algoritmos basicos de ordenacao e o tipo de comparador de produtos.
*/

#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "funcao.h"

typedef int (*ComparadorProduto)(const Produto *a, const Produto *b);

void insercao(Produto *produtos, int tam, ComparadorProduto comparar);
void selecao(Produto *produtos, int tam, ComparadorProduto comparar);
void bubble(Produto *produtos, int tam, ComparadorProduto comparar);

#endif