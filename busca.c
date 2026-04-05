/*
Aluno: Abdiel Abadio Gouveia Silva
Disciplina: Estrutura de Dados
Prova: Questao sobre comercio
Data de entrega: 05/04/2026
Arquivo: busca.c
Descricao: implementa as funcoes de busca binaria por nome, fabricante e faixa de preco.
*/

#include <ctype.h>
#include "busca.h"

int compararTextoIgnorandoCase(const char *a, const char *b)
{
    while (*a != '\0' && *b != '\0')
    {
        char ca = (char)tolower((unsigned char)*a);
        char cb = (char)tolower((unsigned char)*b);

        if (ca != cb)
        {
            return (int)(unsigned char)ca - (int)(unsigned char)cb;
        }

        a++;
        b++;
    }

    return (int)(unsigned char)tolower((unsigned char)*a) - (int)(unsigned char)tolower((unsigned char)*b);
}

int buscaBinariaNome(const Produto *produtos, int total, const char *nome)
{
    int ini = 0;
    int fim = total - 1;

    while (ini <= fim)
    {
        int meio = (ini + fim) / 2;
        int cmp = compararTextoIgnorandoCase(produtos[meio].nome, nome);
        if (cmp == 0)
        {
            return meio;
        }
        if (cmp < 0)
        {
            ini = meio + 1;
        }
        else
        {
            fim = meio - 1;
        }
    }

    return -1;
}

int buscaPrimeiroFabricante(const Produto *produtos, int total, const char *fabricante)
{
    int ini = 0;
    int fim = total - 1;
    int resp = -1;

    while (ini <= fim)
    {
        int meio = (ini + fim) / 2;
        int cmp = compararTextoIgnorandoCase(produtos[meio].fabricante, fabricante);
        if (cmp == 0)
        {
            resp = meio;
            fim = meio - 1;
        }
        else if (cmp < 0)
        {
            ini = meio + 1;
        }
        else
        {
            fim = meio - 1;
        }
    }

    return resp;
}

int buscaInicioFaixaPreco(const Produto *produtos, int total, float preco)
{
    int ini = 0;
    int fim = total - 1;
    int resp = -1;

    while (ini <= fim)
    {
        int meio = (ini + fim) / 2;
        if (produtos[meio].preco_cons >= preco)
        {
            resp = meio;
            fim = meio - 1;
        }
        else
        {
            ini = meio + 1;
        }
    }

    return resp;
}
