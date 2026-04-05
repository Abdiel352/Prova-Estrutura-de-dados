/*
Aluno: Abdiel Abadio Gouveia Silva
Disciplina: Estrutura de Dados
Prova: Questao sobre comercio
Data de entrega: 05/04/2026
Arquivo: busca.h
Descricao: declara as funcoes de comparacao textual e busca binaria de produtos.
*/

#ifndef BUSCA_H
#define BUSCA_H

#include "funcao.h"

int compararTextoIgnorandoCase(const char *a, const char *b);
int buscaBinariaNome(const Produto *produtos, int total, const char *nome);
int buscaPrimeiroFabricante(const Produto *produtos, int total, const char *fabricante);
int buscaInicioFaixaPreco(const Produto *produtos, int total, float preco);

#endif
