# Cadastro de Produtos do Comércio

**Aluno:** Abdiel Abadio Gouveia Silva  
**Disciplina:** Estrutura de Dados  
**Instituição:** IFMT  
**Data de entrega:** 05/04/2026  

---

# Descrição do Projeto

Este projeto consiste em um **sistema de cadastro e gerenciamento de produtos de comércio**, desenvolvido na linguagem C. O programa permite cadastrar até **200 produtos**, contendo informações como nome, categoria, preço base, percentual de lucro, preço ao consumidor e fabricante.

Além do cadastro, o sistema oferece funcionalidades de **listagem ordenada, busca por diferentes critérios, geração de relatórios estatísticos e análise de margens de lucro**.

---

# Estrutura de Arquivos

O projeto foi organizado de forma **modular**, separando responsabilidades em pares de arquivos `.h` (cabeçalhos) e `.c` (implementações).

| Arquivo | Descrição |
|---|---|
| `main.c` | Ponto de entrada do programa. Responsável apenas por chamar a função `menu()`. |
| `funcao.h` | Define a estrutura `Produto`, constantes (`MAX_PRODUTOS`, `TAM_TEXTO`) e o protótipo da função `menu`. |
| `funcao.c` | Implementa a lógica principal do sistema, incluindo menu, cadastro, listagem, buscas, relatórios, ranking e validações de entrada. |
| `ordenar.h` | Declara o tipo `ComparadorProduto` (ponteiro de função) e os protótipos dos algoritmos básicos de ordenação. |
| `ordenar.c` | Implementa os algoritmos Insertion Sort, Selection Sort e Bubble Sort. |
| `ordenacaoComplexa.h` | Declara os algoritmos avançados de ordenação. |
| `ordenacaoComplexa.c` | Implementa Merge Sort e Quick Sort. |
| `busca.h` | Declara funções de comparação textual e busca binária. |
| `busca.c` | Implementa comparação textual case-insensitive e buscas binárias por nome, fabricante e faixa de preço. |

## Justificativa da Organização

A separação em módulos foi adotada para seguir o **princípio da responsabilidade única**, em que cada módulo é responsável por uma parte específica do sistema (ordenação, busca ou lógica principal).

Essa abordagem facilita:

- a **manutenção do código**
- a **leitura e organização**
- a **reutilização de componentes**

Os arquivos de cabeçalho (`.h`) expõem apenas as interfaces necessárias, enquanto funções auxiliares são declaradas como `static` dentro dos arquivos `.c`, tornando-as invisíveis para outros módulos.

---

# Estrutura de Dados Principal

```c
typedef struct {
    int identificacao;         // ID único do produto
    char nome[41];             // Nome do produto (até 40 caracteres)
    int categoria;             // 1-7 (mantimentos, higiene, limpeza, bebidas, padaria, lácteos, diversos)
    float preco_base;          // Preço de custo
    float percen_lucro;        // Percentual de lucro aplicado
    float preco_cons;          // Preço ao consumidor (calculado automaticamente)
    char fabricante[41];       // Nome do fabricante (até 40 caracteres)
} Produto;
```

O campo `preco_cons` é calculado automaticamente no momento do cadastro por meio da fórmula:

```
preco_cons = preco_base + (preco_base * (percen_lucro / 100))
```

---

# Funcionalidades do Menu

## 1. Cadastro de Produto

Permite cadastrar um novo produto com todos os campos necessários.

### Validações implementadas

**Identificação**

- Deve ser um número inteiro válido.
- Não pode ser repetido.

**Nome e Fabricante**

- Não podem ser vazios.
- Não podem conter apenas espaços.
- Não podem conter apenas números ou símbolos.
- Devem conter **pelo menos uma letra**.

A verificação de letras é feita por meio da verificação explícita de caracteres ASCII (`A–Z` e `a–z`), evitando o uso de `isalpha()`, cujo comportamento pode variar dependendo do locale do sistema.

**Categoria**

- Deve ser um número inteiro entre **1 e 7**.

**Preço base e percentual de lucro**

- Devem ser números decimais válidos.
- Devem ser maiores ou iguais a zero.

Todas as entradas numéricas são lidas como **strings** e convertidas utilizando `strtol` e `strtof`, com verificação completa de erros. Essa abordagem evita problemas comuns do `scanf`, como leitura parcial ou aceitação silenciosa de entradas inválidas.

---

# 2. Listagem de Produtos

Exibe todos os produtos cadastrados, ordenados de acordo com o critério escolhido pelo usuário.

| Opção | Critério | Algoritmo Utilizado | Justificativa |
|---|---|---|---|
| 1 | Nome (A → Z) | Insertion Sort | Eficiente para conjuntos pequenos ou quase ordenados |
| 2 | Nome (Z → A) | Quick Sort | Alta eficiência em casos gerais |
| 3 | Categoria | Selection Sort | Implementação simples e adequada para poucas categorias |
| 4 | Preço base (crescente) | Merge Sort | Complexidade garantida O(n log n) e algoritmo estável |
| 5 | Percentual de lucro (decrescente) | Bubble Sort | Uso didático para demonstrar trocas adjacentes |

A utilização de diferentes algoritmos foi intencional, com o objetivo de **demonstrar domínio de múltiplas técnicas de ordenação**, conforme exigido pela disciplina.

Todos os algoritmos utilizam um **comparador genérico** (`ComparadorProduto`), implementado como **ponteiro de função**, permitindo reutilizar os mesmos algoritmos com diferentes critérios de ordenação sem duplicação de código.

---

# 3. Busca de Dados do Produto

O sistema oferece três tipos de busca, todas utilizando **busca binária**, que possui complexidade **O(log n)**.

### Busca por nome

1. O vetor é ordenado por nome usando **Merge Sort**.
2. É realizada uma **busca binária case-insensitive**.
3. O produto encontrado é exibido.

### Busca por fabricante

1. O vetor é ordenado por fabricante usando **Quick Sort**.
2. A busca binária encontra o primeiro produto do fabricante.
3. A partir dele, os produtos seguintes do mesmo fabricante são listados.

### Busca por faixa de preço

1. O vetor é ordenado por preço ao consumidor utilizando **Insertion Sort**.
2. A busca binária encontra o início da faixa.
3. Os produtos dentro do intervalo são listados sequencialmente.

Para preservar a ordem original de cadastro, todas as buscas são realizadas **sobre cópias do vetor original**.

---

# 4. Relatórios Estatísticos

O sistema gera um relatório contendo:

### Preço médio por categoria

Calcula a média aritmética do preço ao consumidor para cada uma das **7 categorias de produtos**.

### Produto mais caro e mais barato

O vetor é percorrido uma única vez para identificar:

- o produto com maior preço
- o produto com menor preço

### Categoria com maior número de produtos

Conta quantos produtos existem em cada categoria e identifica aquela(s) com maior quantidade, tratando possíveis empates.

---

# 5. Ranking de Margens e Alertas

Essa funcionalidade fornece uma análise das margens de lucro cadastradas.

### Top 5 maiores margens

Ordena os produtos pelo percentual de lucro em ordem decrescente e exibe os **5 maiores valores**, mostrando:

- nome do produto
- percentual de lucro
- preço base
- preço ao consumidor

### Alerta de margem baixa

O usuário informa um limite mínimo de margem, e o sistema exibe todos os produtos com percentual inferior ao valor informado, marcados com `[ALERTA]`.

### Alerta de margem acima do teto

O usuário informa um teto máximo de margem, e o sistema lista todos os produtos que ultrapassam esse valor, indicando quantos pontos percentuais estão acima do limite.

Essa funcionalidade auxilia na **análise comercial dos produtos**, permitindo identificar rapidamente margens inadequadas.

---

# 6. Encerramento

Finaliza a execução do programa.

---

# Como Compilar e Executar

## Compilação

```bash
gcc main.c funcao.c ordenar.c ordenacaoComplexa.c busca.c -o prova.exe
```

## Execução

```bash
./prova.exe
```

---

# Observações Técnicas

- O sistema suporta até **200 produtos** (`MAX_PRODUTOS`).
- Campos de texto possuem limite de **40 caracteres** (`TAM_TEXTO`).
- A tela é limpa entre interações usando `system("cls")` no Windows ou `system("clear")` no Linux/Mac.
- Todas as comparações de texto são **case-insensitive**, ignorando diferenças entre maiúsculas e minúsculas.
- O vetor original de produtos **não é alterado** pelas operações de listagem ou busca; essas operações são realizadas sobre **cópias do vetor**.
