# Cadastro de Produtos do Comércio

**Aluno:** Abdiel Abadio Gouveia Silva  
**Disciplina:** Estrutura de Dados  
**Instituição:** IFMT  
**Data de entrega:** 05/04/2026

---

## Descrição do Projeto

Sistema de cadastro e gerenciamento de produtos de comércio desenvolvido em linguagem C. O programa permite cadastrar até 200 produtos com informações como nome, categoria, preço base, percentual de lucro, preço ao consumidor e fabricante. Além do cadastro, oferece funcionalidades de listagem ordenada, busca por diferentes critérios, relatórios estatísticos e análise de margens de lucro.

---

## Estrutura de Arquivos

O projeto foi organizado de forma modular, separando responsabilidades em pares de arquivos `.h` (cabeçalho) e `.c` (implementação):

| Arquivo | Descrição |
|---|---|
| `main.c` | Ponto de entrada do programa. Apenas chama a função `menu()`. |
| `funcao.h` | Define a struct `Produto`, constantes (`MAX_PRODUTOS`, `TAM_TEXTO`) e o protótipo do menu. |
| `funcao.c` | Implementa toda a lógica do menu, cadastro, listagem, busca, relatórios, ranking e validações de entrada. |
| `ordenar.h` | Declara o tipo `ComparadorProduto` (ponteiro de função) e os algoritmos básicos de ordenação. |
| `ordenar.c` | Implementa Insertion Sort, Selection Sort e Bubble Sort. |
| `ordenacaoComplexa.h` | Declara os algoritmos avançados de ordenação. |
| `ordenacaoComplexa.c` | Implementa Merge Sort e Quick Sort. |
| `busca.h` | Declara as funções de comparação textual e busca binária. |
| `busca.c` | Implementa comparação case-insensitive e buscas binárias por nome, fabricante e faixa de preço. |

### Por que essa organização?

A separação em módulos foi feita para manter o **princípio da responsabilidade única**: cada par de arquivos cuida de um aspecto do sistema (ordenação, busca, lógica principal). Isso facilita a leitura, manutenção e reutilização do código. Os cabeçalhos (`.h`) expõem apenas o necessário, enquanto funções auxiliares são declaradas como `static` dentro dos `.c`, ficando invisíveis para o restante do programa.

---

## Estrutura de Dados Principal

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

O `preco_cons` é calculado automaticamente no cadastro pela fórmula:

$$\text{preco\_cons} = \text{preco\_base} + \left(\text{preco\_base} \times \frac{\text{percen\_lucro}}{100}\right)$$

---

## Funcionalidades do Menu

### 1. Cadastro de Produto

Permite cadastrar um novo produto com todos os campos. Validações implementadas:

- **Identificação:** deve ser um número inteiro válido e único (não pode repetir).
- **Nome e Fabricante:** não podem ser vazios, conter apenas espaços, nem conter apenas números/símbolos — é exigida pelo menos uma letra (validação feita por verificação explícita de caracteres ASCII A–Z/a–z, sem depender de `isalpha()` que varia conforme locale).
- **Categoria:** número inteiro entre 1 e 7.
- **Preço base e Percentual de lucro:** números decimais válidos, maiores ou iguais a zero.

Todas as entradas numéricas usam `strtol`/`strtof` com verificação de erro completa (rejeita texto misturado, overflow, entrada vazia), em vez de `scanf` que aceita entrada parcial silenciosamente.

### 2. Listagem de Produtos

Exibe todos os produtos cadastrados, ordenados conforme a escolha do usuário:

| Opção | Critério | Algoritmo Utilizado | Por quê? |
|---|---|---|---|
| 1 | Nome (A→Z) | Insertion Sort | Eficiente para dados quase ordenados, estável |
| 2 | Nome (Z→A) | Quick Sort | Rápido em caso geral, demonstra particionamento |
| 3 | Categoria (A→Z) | Selection Sort | Simples, número limitado de categorias |
| 4 | Preço base (crescente) | Merge Sort | Estável e O(n log n) garantido |
| 5 | % de lucro (decrescente) | Bubble Sort | Didático, demonstra trocas adjacentes |

A escolha de algoritmos diferentes para cada critério foi intencional, para demonstrar domínio de múltiplos algoritmos de ordenação conforme exigido pela disciplina.

Todos os algoritmos utilizam um **comparador genérico** (`ComparadorProduto`), que é um ponteiro de função. Isso permite reutilizar o mesmo algoritmo com critérios diferentes sem duplicar código.

### 3. Busca de Dados do Produto

Três tipos de busca, todas utilizando **busca binária** sobre cópias ordenadas do vetor:

- **Por nome:** ordena por nome (Merge Sort) e faz busca binária exata (case-insensitive).
- **Por fabricante:** ordena por fabricante (Quick Sort), encontra o primeiro via busca binária e percorre sequencialmente para listar todos do mesmo fabricante.
- **Por faixa de preço:** ordena por preço ao consumidor (Insertion Sort), encontra o início da faixa via busca binária e percorre até o fim da faixa.

A busca binária foi escolhida por ter complexidade O(log n), muito mais eficiente que busca linear O(n) para grandes volumes de dados.

### 4. Relatórios Estatísticos

Gera um relatório completo com:

- **Preço médio ao consumidor por categoria:** calcula a média aritmética dos preços agrupados por cada uma das 7 categorias.
- **Produto mais caro e mais barato:** percorre o vetor uma única vez para identificar os extremos.
- **Categoria(s) com mais produtos:** identifica qual categoria tem maior quantidade cadastrada, tratando empates (exibe todas as empatadas).

### 5. Ranking de Margens e Alertas

Funcionalidade de análise de negócio com três sub-opções:

- **Top 5 maiores margens:** ordena por percentual de lucro decrescente (Bubble Sort) e exibe os 5 primeiros, com margem, preço base e preço ao consumidor.
- **Alerta de margem baixa:** o usuário informa um limite percentual e o sistema lista todos os produtos com margem abaixo desse valor, marcados com `[ALERTA]`.
- **Alerta de margem acima do teto:** o usuário informa um teto de margem e o sistema lista todos os produtos que ultrapassam esse valor, mostrando quantos pontos percentuais acima do teto estão, com `[ALERTA]`.

Essa funcionalidade simula uma ferramenta de apoio à decisão comercial, permitindo identificar rapidamente produtos com margem insuficiente ou excessiva.

### 6. Sair

Encerra o programa.

---

## Algoritmos de Ordenação

| Algoritmo | Complexidade Média | Complexidade Pior Caso | Estável? | Arquivo | Onde é usado |
|---|---|---|---|---|---|
| Insertion Sort | O(n²) | O(n²) | Sim | `ordenar.c` | Listagem por nome (A→Z) e busca por faixa de preço |
| Selection Sort | O(n²) | O(n²) | Não | `ordenar.c` | Listagem por categoria |
| Bubble Sort | O(n²) | O(n²) | Sim | `ordenar.c` | Listagem por % de lucro (decrescente) e ranking top 5 margens |
| Quick Sort | O(n log n) | O(n²) | Não | `ordenacaoComplexa.c` | Listagem por nome (Z→A) e busca por fabricante |
| Merge Sort | O(n log n) | O(n log n) | Sim | `ordenacaoComplexa.c` | Listagem por preço base e busca por nome |

O Quick Sort usa pivô mediano para reduzir a chance do pior caso. O Merge Sort usa alocação dinâmica (`malloc`) para o array temporário durante a intercalação.

Todos os algoritmos utilizam um **comparador genérico** via ponteiro de função (`ComparadorProduto`), o que permite reutilizar o mesmo algoritmo com critérios de ordenação diferentes sem duplicar código.

## Algoritmos de Busca

| Algoritmo | Complexidade | Arquivo | Onde é usado |
|---|---|---|---|
| Busca Binária (nome) | O(log n) | `busca.c` | Buscar produto exato por nome |
| Busca Binária (fabricante) | O(log n) | `busca.c` | Encontrar primeiro produto de um fabricante e listar todos do mesmo |
| Busca Binária (faixa de preço) | O(log n) | `busca.c` | Encontrar início de uma faixa de preço ao consumidor |

Todas as buscas binárias exigem que o vetor esteja ordenado pelo critério buscado, por isso uma cópia é ordenada antes de cada busca — preservando a ordem original de cadastro.

---

## Validação de Entrada

O sistema implementa validação robusta em todas as entradas do usuário:

- **Números inteiros:** lidos como string e convertidos com `strtol`, verificando overflow, caracteres inválidos e limites min/max.
- **Números decimais:** lidos como string e convertidos com `strtof`, com verificações similares.
- **Textos (nome e fabricante):** exigem pelo menos uma letra ASCII (A–Z ou a–z), rejeitando entradas puramente numéricas, vazias ou só com espaços. A verificação de letras usa comparação explícita de faixa ASCII em vez de `isalpha()`, garantindo comportamento consistente em qualquer locale do sistema.

Essa abordagem elimina problemas comuns do `scanf` como leitura parcial, buffer sujo e aceitação silenciosa de entradas inválidas.

---

## Como Compilar e Executar

### Compilação (GCC)

```bash
gcc main.c funcao.c ordenar.c ordenacaoComplexa.c busca.c -o prova.exe
```

### Execução

```bash
./prova.exe
```

---

## Observações Técnicas

- O programa suporta até **200 produtos** (definido por `MAX_PRODUTOS`).
- Campos de texto têm limite de **40 caracteres** (definido por `TAM_TEXTO`).
- A tela é limpa entre interações usando `system("cls")` no Windows ou `system("clear")` no Linux/Mac.
- Todas as comparações de texto são **case-insensitive** (ignora maiúsculas/minúsculas).
- O vetor original de produtos nunca é alterado pelas operações de listagem ou busca — sempre se trabalha com cópias.
