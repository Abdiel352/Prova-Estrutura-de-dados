/*
Aluno: Abdiel Abadio Gouveia Silva
Disciplina: Estrutura de Dados
Prova: Questao sobre comercio
Data de entrega: 05/04/2026
Arquivo: funcao.h
Descricao: define a estrutura Produto, constantes do sistema e o prototipo do menu.
*/

#ifndef FUNCAO_H
#define FUNCAO_H

#define MAX_PRODUTOS 200
#define TAM_TEXTO 40

typedef struct {
    int identificacao;
    char nome[TAM_TEXTO + 1];
    int categoria;
    float preco_base;
    float percen_lucro;
    float preco_cons;
    char fabricante[TAM_TEXTO + 1];
} Produto;

void menu();

#endif