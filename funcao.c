/*
Aluno: Abdiel Abadio Gouveia Silva
Disciplina: Estrutura de Dados
Prova: Questao sobre comercio
Data de entrega: 05/04/2026
Arquivo: funcao.c
Descricao: implementa o menu principal e as rotinas de cadastro, listagem e interacao com o usuario.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include "ordenar.h"
#include "ordenacaoComplexa.h"
#include "busca.h"

static void limparTerminal()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

static void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

static void lerLinha(char *destino, int tamanho)
{
    if (fgets(destino, tamanho, stdin) != NULL)
    {
        size_t len = strlen(destino);
        if (len > 0 && destino[len - 1] == '\n')
        {
            destino[len - 1] = '\0';
        }
        else
        {
            limparBufferEntrada();
        }
    }
}

static int textoTemLetraAscii(const char *texto)
{
    while (*texto != '\0')
    {
        unsigned char c = (unsigned char)*texto;
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        {
            return 1;
        }
        texto++;
    }

    return 0;
}

static int textoEhVazioOuEspacos(const char *texto)
{
    while (*texto != '\0')
    {
        if (!isspace((unsigned char)*texto))
        {
            return 0;
        }
        texto++;
    }

    return 1;
}

static void lerTextoComLetra(const char *mensagem, char *destino, int tamanho, const char *nomeCampo)
{
    while (1)
    {
        printf("%s", mensagem);
        lerLinha(destino, tamanho);

        if (textoEhVazioOuEspacos(destino))
        {
            printf("%s invalido: nao pode ser vazio.\n", nomeCampo);
            continue;
        }

        if (!textoTemLetraAscii(destino))
        {
            printf("%s invalido: nao pode conter apenas numeros/simbolos. Informe pelo menos uma letra.\n", nomeCampo);
            continue;
        }

        return;
    }
}

static int lerInteiroValido(const char *mensagem, int min, int max)
{
    char entrada[128];

    while (1)
    {
        char *fim;
        long valor;

        printf("%s", mensagem);
        if (fgets(entrada, sizeof(entrada), stdin) == NULL)
        {
            continue;
        }

        errno = 0;
        valor = strtol(entrada, &fim, 10);

        while (*fim != '\0' && isspace((unsigned char)*fim))
        {
            fim++;
        }

        if (entrada == fim || *fim != '\0' || errno == ERANGE || valor < min || valor > max)
        {
            printf("Entrada invalida. Informe um numero inteiro entre %d e %d.\n", min, max);
            continue;
        }

        return (int)valor;
    }
}

static float lerFloatValido(const char *mensagem, float min)
{
    char entrada[128];

    while (1)
    {
        char *fim;
        float valor;

        printf("%s", mensagem);
        if (fgets(entrada, sizeof(entrada), stdin) == NULL)
        {
            continue;
        }

        errno = 0;
        valor = strtof(entrada, &fim);

        while (*fim != '\0' && isspace((unsigned char)*fim))
        {
            fim++;
        }

        if (entrada == fim || *fim != '\0' || errno == ERANGE || valor < min)
        {
            printf("Entrada invalida. Informe um valor numerico maior ou igual a %.2f.\n", min);
            continue;
        }

        return valor;
    }
}

static const char *nomeCategoria(int categoria)
{
    switch (categoria)
    {
    case 1:
        return "Mantimentos";
    case 2:
        return "Higiene";
    case 3:
        return "Limpeza";
    case 4:
        return "Bebidas";
    case 5:
        return "Padaria";
    case 6:
        return "Lacteos";
    case 7:
        return "Diversos";
    default:
        return "Nao definida";
    }
}

static int existeIdentificacao(Produto *produtos, int total, int id)
{
    int i;
    for (i = 0; i < total; i++)
    {
        if (produtos[i].identificacao == id)
        {
            return 1;
        }
    }

    return 0;
}

static void imprimirProduto(const Produto *p)
{
    printf("\n---------------------------------------\n");
    printf("ID: %d\n", p->identificacao);
    printf("Nome: %s\n", p->nome);
    printf("Categoria: %s (%d)\n", nomeCategoria(p->categoria), p->categoria);
    printf("Preco base: R$ %.2f\n", p->preco_base);
    printf("Percentual de lucro: %.2f%%\n", p->percen_lucro);
    printf("Preco consumidor: R$ %.2f\n", p->preco_cons);
    printf("Fabricante: %s\n", p->fabricante);
    printf("---------------------------------------\n");
}

static void copiarProdutos(const Produto *origem, Produto *destino, int total)
{
    int i;
    for (i = 0; i < total; i++)
    {
        destino[i] = origem[i];
    }
}

static int cmpNomeAsc(const Produto *a, const Produto *b)
{
    return compararTextoIgnorandoCase(a->nome, b->nome);
}

static int cmpNomeDesc(const Produto *a, const Produto *b)
{
    return compararTextoIgnorandoCase(b->nome, a->nome);
}

static int cmpCategoriaNomeAsc(const Produto *a, const Produto *b)
{
    int c = compararTextoIgnorandoCase(nomeCategoria(a->categoria), nomeCategoria(b->categoria));
    if (c != 0)
    {
        return c;
    }
    return cmpNomeAsc(a, b);
}

static int cmpPrecoBaseAsc(const Produto *a, const Produto *b)
{
    if (a->preco_base < b->preco_base)
    {
        return -1;
    }
    if (a->preco_base > b->preco_base)
    {
        return 1;
    }
    return cmpNomeAsc(a, b);
}

static int cmpPercenLucroDesc(const Produto *a, const Produto *b)
{
    if (a->percen_lucro > b->percen_lucro)
    {
        return -1;
    }
    if (a->percen_lucro < b->percen_lucro)
    {
        return 1;
    }
    return cmpNomeAsc(a, b);
}

static int cmpFabricanteAsc(const Produto *a, const Produto *b)
{
    int c = compararTextoIgnorandoCase(a->fabricante, b->fabricante);
    if (c != 0)
    {
        return c;
    }
    return cmpNomeAsc(a, b);
}

static int cmpPrecoConsumidorAsc(const Produto *a, const Produto *b)
{
    if (a->preco_cons < b->preco_cons)
    {
        return -1;
    }
    if (a->preco_cons > b->preco_cons)
    {
        return 1;
    }
    return cmpNomeAsc(a, b);
}

static void cadastrarProduto(Produto *produtos, int *total)
{
    Produto p;

    if (*total >= MAX_PRODUTOS)
    {
        printf("\nLimite maximo de produtos atingido (%d).\n", MAX_PRODUTOS);
        return;
    }

    printf("\n=== Cadastro de Produto ===\n");

    do
    {
        p.identificacao = lerInteiroValido("Identificacao unica (inteiro): ", INT_MIN, INT_MAX);
        if (existeIdentificacao(produtos, *total, p.identificacao))
        {
            printf("ID ja cadastrado. Informe outro.\n");
        }
    } while (existeIdentificacao(produtos, *total, p.identificacao));

    lerTextoComLetra("Nome do produto (ate 40 caracteres): ", p.nome, TAM_TEXTO + 1, "Nome do produto");

    p.categoria = lerInteiroValido("Categoria [1:mantimentos, 2:higiene, 3:limpeza, 4:bebidas, 5:padaria, 6:lacteos, 7:diversos]: ", 1, 7);
    p.preco_base = lerFloatValido("Preco base: ", 0.0f);
    p.percen_lucro = lerFloatValido("Percentual de lucro: ", 0.0f);

    p.preco_cons = p.preco_base + (p.preco_base * p.percen_lucro / 100.0f);

    lerTextoComLetra("Fabricante (ate 40 caracteres): ", p.fabricante, TAM_TEXTO + 1, "Fabricante");

    produtos[*total] = p;
    (*total)++;

    printf("\nProduto cadastrado com sucesso.\n");
}

static void listarProdutos(Produto *produtos, int total)
{
    int opcao;
    Produto aux[MAX_PRODUTOS];
    int i;

    if (total == 0)
    {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    printf("\n=== Listagem de Produtos ===\n");
    printf("1. Nome (ordem alfabetica crescente)\n");
    printf("2. Nome (ordem alfabetica decrescente)\n");
    printf("3. Categoria (ordem alfabetica crescente)\n");
    printf("4. Preco base (ordem crescente)\n");
    printf("5. Percentual de lucro (ordem decrescente)\n");
    opcao = lerInteiroValido("Opcao: ", 1, 5);

    copiarProdutos(produtos, aux, total);

    switch (opcao)
    {
    case 1:
        insercao(aux, total, cmpNomeAsc);
        break;
    case 2:
        quickSort(aux, 0, total - 1, cmpNomeDesc);
        break;
    case 3:
        selecao(aux, total, cmpCategoriaNomeAsc);
        break;
    case 4:
        mergeSort(aux, 0, total - 1, cmpPrecoBaseAsc);
        break;
    case 5:
        bubble(aux, total, cmpPercenLucroDesc);
        break;
    default:
        printf("\nOpcao invalida.\n");
        return;
    }

    for (i = 0; i < total; i++)
    {
        imprimirProduto(&aux[i]);
    }
}

static void buscarPorNome(Produto *produtos, int total)
{
    char nomeBusca[TAM_TEXTO + 1];
    Produto aux[MAX_PRODUTOS];
    int pos;

    printf("\nNome do produto para busca: ");
    lerLinha(nomeBusca, TAM_TEXTO + 1);

    copiarProdutos(produtos, aux, total);
    mergeSort(aux, 0, total - 1, cmpNomeAsc);

    pos = buscaBinariaNome(aux, total, nomeBusca);
    if (pos == -1)
    {
        printf("\nProduto nao encontrado pelo nome informado.\n");
        return;
    }

    imprimirProduto(&aux[pos]);
}

static void buscarPorFabricante(Produto *produtos, int total)
{
    char fabricanteBusca[TAM_TEXTO + 1];
    Produto aux[MAX_PRODUTOS];
    int pos;
    int encontrou = 0;

    printf("\nFabricante para busca: ");
    lerLinha(fabricanteBusca, TAM_TEXTO + 1);

    copiarProdutos(produtos, aux, total);
    quickSort(aux, 0, total - 1, cmpFabricanteAsc);

    pos = buscaPrimeiroFabricante(aux, total, fabricanteBusca);
    if (pos == -1)
    {
        printf("\nNenhum produto encontrado para esse fabricante.\n");
        return;
    }

    while (pos < total && compararTextoIgnorandoCase(aux[pos].fabricante, fabricanteBusca) == 0)
    {
        imprimirProduto(&aux[pos]);
        encontrou = 1;
        pos++;
    }

    if (!encontrou)
    {
        printf("\nNenhum produto encontrado para esse fabricante.\n");
    }
}

static void buscarPorFaixaPreco(Produto *produtos, int total)
{
    float precoInicial, precoFinal;
    Produto aux[MAX_PRODUTOS];
    int inicioFaixa;
    int i;
    int encontrou = 0;

    printf("\n");
    precoInicial = lerFloatValido("Preco inicial (consumidor): ", 0.0f);
    precoFinal = lerFloatValido("Preco final (consumidor): ", 0.0f);

    if (precoInicial > precoFinal)
    {
        float tmp = precoInicial;
        precoInicial = precoFinal;
        precoFinal = tmp;
    }

    copiarProdutos(produtos, aux, total);
    insercao(aux, total, cmpPrecoConsumidorAsc);
    inicioFaixa = buscaInicioFaixaPreco(aux, total, precoInicial);

    printf("\nProdutos na faixa R$ %.2f ate R$ %.2f:\n", precoInicial, precoFinal);
    if (inicioFaixa == -1)
    {
        printf("Nenhum produto encontrado nessa faixa de preco.\n");
        return;
    }

    for (i = inicioFaixa; i < total && aux[i].preco_cons <= precoFinal; i++)
    {
        printf("- %s (R$ %.2f)\n", aux[i].nome, aux[i].preco_cons);
        encontrou = 1;
    }

    if (!encontrou)
    {
        printf("Nenhum produto encontrado nessa faixa de preco.\n");
    }
}

static void buscarProdutos(Produto *produtos, int total)
{
    int opcao;

    if (total == 0)
    {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    printf("\n=== Busca de Produtos ===\n");
    printf("1. Buscar por nome (exibe dados do produto)\n");
    printf("2. Buscar por fabricante (exibe produtos relacionados)\n");
    printf("3. Buscar por faixa de preco (exibe nomes)\n");
    opcao = lerInteiroValido("Opcao: ", 1, 3);

    switch (opcao)
    {
    case 1:
        buscarPorNome(produtos, total);
        break;
    case 2:
        buscarPorFabricante(produtos, total);
        break;
    case 3:
        buscarPorFaixaPreco(produtos, total);
        break;
    default:
        printf("\nOpcao invalida.\n");
    }
}

static void exibirRelatorioEstatistico(Produto *produtos, int total)
{
    float somaPrecoCons[8] = {0};
    int contagemCategoria[8] = {0};
    int i;
    int indiceMaiorQtd;

    if (total == 0)
    {
        printf("\nNenhum produto cadastrado para gerar relatorio.\n");
        return;
    }

    for (i = 0; i < total; i++)
    {
        int cat = produtos[i].categoria;
        if (cat >= 1 && cat <= 7)
        {
            somaPrecoCons[cat] += produtos[i].preco_cons;
            contagemCategoria[cat]++;
        }
    }

    printf("\n=== Relatorio Estatistico ===\n");
    printf("\nPreco medio ao consumidor por categoria:\n");
    for (i = 1; i <= 7; i++)
    {
        if (contagemCategoria[i] > 0)
        {
            float media = somaPrecoCons[i] / contagemCategoria[i];
            printf("- %s: R$ %.2f (%d produto(s))\n", nomeCategoria(i), media, contagemCategoria[i]);
        }
        else
        {
            printf("- %s: sem produtos cadastrados\n", nomeCategoria(i));
        }
    }

    {
        int idxMaior = 0;
        int idxMenor = 0;
        for (i = 1; i < total; i++)
        {
            if (produtos[i].preco_cons > produtos[idxMaior].preco_cons)
            {
                idxMaior = i;
            }
            if (produtos[i].preco_cons < produtos[idxMenor].preco_cons)
            {
                idxMenor = i;
            }
        }

        printf("\nProduto com maior preco ao consumidor:\n");
        printf("- %s (ID %d): R$ %.2f\n", produtos[idxMaior].nome, produtos[idxMaior].identificacao, produtos[idxMaior].preco_cons);

        printf("\nProduto com menor preco ao consumidor:\n");
        printf("- %s (ID %d): R$ %.2f\n", produtos[idxMenor].nome, produtos[idxMenor].identificacao, produtos[idxMenor].preco_cons);
    }

    indiceMaiorQtd = 1;
    for (i = 2; i <= 7; i++)
    {
        if (contagemCategoria[i] > contagemCategoria[indiceMaiorQtd])
        {
            indiceMaiorQtd = i;
        }
    }

    if (contagemCategoria[indiceMaiorQtd] == 0)
    {
        printf("\nCategoria com mais produtos: sem dados.\n");
    }
    else
    {
        int houveEmpate = 0;
        printf("\nCategoria(s) com mais produtos (%d produto(s)):\n", contagemCategoria[indiceMaiorQtd]);
        for (i = 1; i <= 7; i++)
        {
            if (contagemCategoria[i] == contagemCategoria[indiceMaiorQtd])
            {
                printf("- %s\n", nomeCategoria(i));
                houveEmpate = 1;
            }
        }

        if (!houveEmpate)
        {
            printf("- %s\n", nomeCategoria(indiceMaiorQtd));
        }
    }
}

static void exibirRankingMargens(Produto *produtos, int total)
{
    Produto aux[MAX_PRODUTOS];
    int opcao;
    int i, limite;

    if (total == 0)
    {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    printf("\n=== Ranking de Margens e Alertas ===\n");
    printf("1. Top 5 maiores margens de lucro\n");
    printf("2. Produtos com margem abaixo de um limite\n");
    printf("3. Produtos acima de um teto de margem\n");
    opcao = lerInteiroValido("Opcao: ", 1, 3);

    switch (opcao)
    {
    case 1:
        copiarProdutos(produtos, aux, total);
        bubble(aux, total, cmpPercenLucroDesc);
        limite = total < 5 ? total : 5;
        printf("\nTop %d maiores margens de lucro:\n", limite);
        for (i = 0; i < limite; i++)
        {
            printf("%d. %s (ID %d) - margem: %.2f%% | base: R$ %.2f | consumidor: R$ %.2f\n",
                   i + 1, aux[i].nome, aux[i].identificacao,
                   aux[i].percen_lucro, aux[i].preco_base, aux[i].preco_cons);
        }
        break;
    case 2:
    {
        float limiteMargen;
        int encontrou = 0;
        limiteMargen = lerFloatValido("Limite de margem (%%): ", 0.0f);
        printf("\nProdutos com margem abaixo de %.2f%%:\n", limiteMargen);
        for (i = 0; i < total; i++)
        {
            if (produtos[i].percen_lucro < limiteMargen)
            {
                printf("- %s (ID %d) - margem: %.2f%% [ALERTA]\n",
                       produtos[i].nome, produtos[i].identificacao, produtos[i].percen_lucro);
                encontrou = 1;
            }
        }
        if (!encontrou)
        {
            printf("Nenhum produto abaixo do limite informado.\n");
        }
        break;
    }
    case 3:
    {
        float tetoMargem;
        int encontrou = 0;
        tetoMargem = lerFloatValido("Teto de margem de lucro (%%): ", 0.0f);
        printf("\nProdutos com margem acima de %.2f%%:\n", tetoMargem);
        for (i = 0; i < total; i++)
        {
            if (produtos[i].percen_lucro > tetoMargem)
            {
                printf("- %s (ID %d) - margem: %.2f%% (%.2f%% acima do teto) [ALERTA]\n",
                       produtos[i].nome, produtos[i].identificacao, produtos[i].percen_lucro,
                       produtos[i].percen_lucro - tetoMargem);
                encontrou = 1;
            }
        }
        if (!encontrou)
        {
            printf("Nenhum produto acima do teto informado.\n");
        }
        break;
    }
    default:
        printf("\nOpcao invalida.\n");
    }
}

static void encerrarInteracao()
{
    printf("\nPressione Enter para continuar...");
    getchar();
    limparTerminal();
}

void menu()
{
    int opcao;
    int totalProdutos = 0;
    Produto produtos[MAX_PRODUTOS];

    limparTerminal();

    do
    {
        printf("\n=============================================\n");
        printf(" Cadastro de Produtos do Comercio\n");
        printf("=============================================\n");
        printf("1. Cadastro de produto\n");
        printf("2. Listagem de produtos\n");
        printf("3. Busca de dados do produto\n");
        printf("4. Relatorios estatisticos\n");
        printf("5. Ranking de margens e alertas\n");
        printf("6. Sair\n");
        opcao = lerInteiroValido("Escolha uma opcao: ", 1, 6);

        switch (opcao)
        {
        case 1:
            cadastrarProduto(produtos, &totalProdutos);
            break;
        case 2:
            listarProdutos(produtos, totalProdutos);
            break;
        case 3:
            buscarProdutos(produtos, totalProdutos);
            break;
        case 4:
            exibirRelatorioEstatistico(produtos, totalProdutos);
            break;
        case 5:
            exibirRankingMargens(produtos, totalProdutos);
            break;
        case 6:
            printf("\nAplicacao finalizada.\n");
            break;
        default:
            printf("\nOpcao invalida.\n");
        }

        if (opcao != 6)
        {
            encerrarInteracao();
        }
    } while (opcao != 6);
}