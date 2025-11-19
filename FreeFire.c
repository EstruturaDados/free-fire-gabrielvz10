#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

    return 0;
}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.

// Código da Ilha – Edição Free Fire
// Nível: Mestre (Comparação de Estruturas: Vetor vs Lista Encadeada)
// Implementa duas versões da mochila: vetor (lista sequencial) e lista encadeada.
// Opera: inserir, remover, listar, buscar sequencial em ambas; ordenar + busca binária no vetor.
// Conta comparações de cada tipo de busca e mede tempo aproximado de execução.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_ITENS 10
#define TAM_NOME 30
#define TAM_TIPO 20

/* -------------------------
   Structs
   ------------------------- */

// Item: representa um objeto com nome, tipo e quantidade.
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

// No: nó da lista encadeada contendo um Item.
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

/* -------------------------
   Variáveis do Vetor (lista sequencial)
   ------------------------- */

Item mochilaVetor[MAX_ITENS];
int numItensVetor = 0;

/* -------------------------
   Variáveis da Lista Encadeada
   ------------------------- */

No* headLista = NULL; // início da lista

/* -------------------------
   Contadores de comparações
   ------------------------- */

long comparacoesSeqVetor = 0;
long comparacoesBinVetor = 0;
long comparacoesSeqLista = 0;

/* -------------------------
   Protótipos - utilitários
   ------------------------- */

void limparBufferEntrada();
void pausar();

/* -------------------------
   Protótipos - Vetor
   ------------------------- */

void inserirItemVetor();
void removerItemVetor();
void listarItensVetor();
int buscarSequencialVetor(const char* nome); // retorna índice ou -1
void ordenarVetorPorNome(); // selection sort com contador
int buscarBinariaVetor(const char* nome); // pressupõe vetor ordenado; retorna índice ou -1

/* -------------------------
   Protótipos - Lista Encadeada
   ------------------------- */

void inserirItemLista();
bool removerItemLista(const char* nome);
void listarItensLista();
No* buscarSequencialLista(const char* nome); // retorna ponteiro para nó ou NULL

/* -------------------------
   Protótipos - Menu / Comparação
   ------------------------- */

void menuPrincipal();
void menuVetor();
void menuLista();
void relatorioComparacoes();

/* -------------------------
   Implementação
   ------------------------- */

/* Limpa stdin */
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/* Pausa simples */
void pausar() {
    printf("\nPressione Enter para continuar...");
    getchar();
}

/* -------------------------
   Funções do VETOR
   ------------------------- */

/* Inserir novo item no vetor */
void inserirItemVetor() {
    if (numItensVetor >= MAX_ITENS) {
        printf("Mochila (vetor) cheia! Remova um item antes de inserir.\n");
        return;
    }

    Item it;
    printf("Nome do item: ");
    scanf(" %29[^\n]", it.nome);
    limparBufferEntrada();

    printf("Tipo do item (arma, municao, cura...): ");
    scanf(" %19[^\n]", it.tipo);
    limparBufferEntrada();

    printf("Quantidade: ");
    while (scanf("%d", &it.quantidade) != 1 || it.quantidade < 0) {
        limparBufferEntrada();
        printf("Valor inválido. Digite um inteiro não-negativo para quantidade: ");
    }
    limparBufferEntrada();

    mochilaVetor[numItensVetor++] = it;
    printf("Item inserido no vetor com sucesso.\n");
}

/* Remove item por nome (vetor) */
void removerItemVetor() {
    if (numItensVetor == 0) {
        printf("Mochila (vetor) vazia.\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("Nome do item a remover: ");
    scanf(" %29[^\n]", nomeBusca);
    limparBufferEntrada();

    int idx = buscarSequencialVetor(nomeBusca);
    if (idx == -1) {
        printf("Item não encontrado no vetor.\n");
        return;
    }

    // desloca elementos à esquerda para preencher lacuna
    for (int i = idx; i < numItensVetor - 1; i++) {
        mochilaVetor[i] = mochilaVetor[i + 1];
    }
    numItensVetor--;
    printf("Item removido do vetor com sucesso.\n");
}

/* Lista itens do vetor */
void listarItensVetor() {
    if (numItensVetor == 0) {
        printf("Mochila (vetor) vazia.\n");
        return;
    }
    printf("\n--- Itens no vetor (mochila) ---\n");
    for (int i = 0; i < numItensVetor; i++) {
        printf("%d) Nome: %-20s | Tipo: %-10s | Quantidade: %d\n",
               i, mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

/* Busca sequencial no vetor por nome; incrementa comparacoesSeqVetor */
int buscarSequencialVetor(const char* nome) {
    for (int i = 0; i < numItensVetor; i++) {
        comparacoesSeqVetor++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) return i;
    }
    return -1;
}

/* Ordena o vetor por nome (ordem alfabética) - Selection Sort
   Incrementa comparações em comparacoesBinVetor para manter análise (conta comparações de ordenação também).
*/
void ordenarVetorPorNome() {
    if (numItensVetor <= 1) return;
    // Vamos usar Selection Sort e contar comparações
    long comparacoesAntes = comparacoesBinVetor;
    for (int i = 0; i < numItensVetor - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < numItensVetor; j++) {
            comparacoesBinVetor++; // cada comparação de nomes
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[menor].nome) < 0) {
                menor = j;
            }
        }
        if (menor != i) {
            Item tmp = mochilaVetor[i];
            mochilaVetor[i] = mochilaVetor[menor];
            mochilaVetor[menor] = tmp;
        }
    }
    long adicionadas = comparacoesBinVetor - comparacoesAntes;
    printf("Vetor ordenado por nome (Selection Sort). Comparações nesta ordenação: %ld\n", adicionadas);
}

/* Busca binária no vetor por nome - pressupõe vetor ordenado.
   Conta comparações em comparacoesBinVetor.
*/
int buscarBinariaVetor(const char* nome) {
    int left = 0;
    int right = numItensVetor - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        comparacoesBinVetor++;
        int cmp = strcmp(mochilaVetor[mid].nome, nome);
        if (cmp == 0) return mid;
        else if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

/* -------------------------
   Funções da LISTA ENCADEADA
   ------------------------- */

/* Inserir item no início da lista (padrão simples) */
void inserirItemLista() {
    Item it;
    printf("Nome do item: ");
    scanf(" %29[^\n]", it.nome);
    limparBufferEntrada();

    printf("Tipo do item (arma, municao, cura...): ");
    scanf(" %19[^\n]", it.tipo);
    limparBufferEntrada();

    printf("Quantidade: ");
    while (scanf("%d", &it.quantidade) != 1 || it.quantidade < 0) {
        limparBufferEntrada();
        printf("Valor inválido. Digite um inteiro não-negativo para quantidade: ");
    }
    limparBufferEntrada();

    No* novo = (No*) malloc(sizeof(No));
    if (!novo) {
        printf("Erro de alocação.\n");
        return;
    }
    novo->dados = it;
    novo->proximo = headLista;
    headLista = novo;
    printf("Item inserido na lista encadeada com sucesso (no início).\n");
}

/* Remover item da lista por nome; retorna true se removido */
bool removerItemLista(const char* nome) {
    No* atual = headLista;
    No* anterior = NULL;

    while (atual != NULL) {
        comparacoesSeqLista++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            // remover
            if (anterior == NULL) {
                headLista = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            return true;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    return false;
}

/* Listar itens na lista encadeada */
void listarItensLista() {
    if (headLista == NULL) {
        printf("Mochila (lista) vazia.\n");
        return;
    }
    printf("\n--- Itens na lista encadeada (mochila) ---\n");
    No* p = headLista;
    int idx = 0;
    while (p != NULL) {
        printf("%d) Nome: %-20s | Tipo: %-10s | Quantidade: %d\n",
               idx, p->dados.nome, p->dados.tipo, p->dados.quantidade);
        p = p->proximo;
        idx++;
    }
}

/* Busca sequencial na lista encadeada: retorna ponteiro para nó ou NULL.
   Também incrementa comparacoesSeqLista para cada comparação.
*/
No* buscarSequencialLista(const char* nome) {
    No* p = headLista;
    while (p != NULL) {
        comparacoesSeqLista++;
        if (strcmp(p->dados.nome, nome) == 0) return p;
        p = p->proximo;
    }
    return NULL;
}

/* -------------------------
   Menus e interação
   ------------------------- */

void menuVetor() {
    int opc;
    do {
        printf("\n--- MENU: Mochila (VETOR) ---\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item por nome\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar (sequencial)\n");
        printf("5 - Ordenar por nome\n");
        printf("6 - Buscar binaria (requer ordenacao)\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        if (scanf("%d", &opc) != 1) { limparBufferEntrada(); printf("Entrada inválida.\n"); continue; }
        limparBufferEntrada();

        if (opc == 1) inserirItemVetor();
        else if (opc == 2) removerItemVetor();
        else if (opc == 3) listarItensVetor();
        else if (opc == 4) {
            char nomeBusca[TAM_NOME];
            printf("Nome a buscar (sequencial): ");
            scanf(" %29[^\n]", nomeBusca); limparBufferEntrada();
            clock_t inicio = clock();
            int idx = buscarSequencialVetor(nomeBusca);
            clock_t fim = clock();
            double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000.0;
            if (idx == -1) printf("Item nao encontrado (vetor - sequencial).\n");
            else printf("Item encontrado no indice %d: %s | Tipo: %s | Quantidade: %d\n",
                        idx, mochilaVetor[idx].nome, mochilaVetor[idx].tipo, mochilaVetor[idx].quantidade);
            printf("Comparacoes sequenciais realizadas (vetor): %ld | Tempo: %.3f ms\n", comparacoesSeqVetor, tempo);
        }
        else if (opc == 5) ordenarVetorPorNome();
        else if (opc == 6) {
            char nomeBusca[TAM_NOME];
            printf("Nome a buscar (binaria) - vetor deve estar ordenado por nome: ");
            scanf(" %29[^\n]", nomeBusca); limparBufferEntrada();
            clock_t inicio = clock();
            int idx = buscarBinariaVetor(nomeBusca);
            clock_t fim = clock();
            double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000.0;
            if (idx == -1) printf("Item nao encontrado (vetor - binaria).\n");
            else printf("Item encontrado no indice %d: %s | Tipo: %s | Quantidade: %d\n",
                        idx, mochilaVetor[idx].nome, mochilaVetor[idx].tipo, mochilaVetor[idx].quantidade);
            printf("Comparacoes (binaria) realizadas: %ld | Tempo: %.3f ms\n", comparacoesBinVetor, tempo);
        }
        else if (opc == 0) break;
        else printf("Opcao invalida.\n");

        pausar();
        limparBufferEntrada();
    } while (opc != 0);
}

void menuLista() {
    int opc;
    do {
        printf("\n--- MENU: Mochila (LISTA ENCADEADA) ---\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item por nome\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar (sequencial)\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        if (scanf("%d", &opc) != 1) { limparBufferEntrada(); printf("Entrada inválida.\n"); continue; }
        limparBufferEntrada();

        if (opc == 1) inserirItemLista();
        else if (opc == 2) {
            char nomeBusca[TAM_NOME];
            printf("Nome a remover: ");
            scanf(" %29[^\n]", nomeBusca); limparBufferEntrada();
            bool ok = removerItemLista(nomeBusca);
            if (ok) printf("Item removido da lista com sucesso.\n");
            else printf("Item nao encontrado na lista.\n");
        }
        else if (opc == 3) listarItensLista();
        else if (opc == 4) {
            char nomeBusca[TAM_NOME];
            printf("Nome a buscar (sequencial - lista): ");
            scanf(" %29[^\n]", nomeBusca); limparBufferEntrada();
            clock_t inicio = clock();
            No* p = buscarSequencialLista(nomeBusca);
            clock_t fim = clock();
            double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000.0;
            if (p == NULL) printf("Item nao encontrado na lista.\n");
            else printf("Item encontrado: %s | Tipo: %s | Quantidade: %d\n",
                        p->dados.nome, p->dados.tipo, p->dados.quantidade);
            printf("Comparacoes sequenciais realizadas (lista): %ld | Tempo: %.3f ms\n", comparacoesSeqLista, tempo);
        }
        else if (opc == 0) break;
        else printf("Opcao invalida.\n");

        pausar();
        limparBufferEntrada();
    } while (opc != 0);
}

/* Relatório simples das comparações entre estruturas */
void relatorioComparacoes() {
    printf("\n--- Relatorio de Comparacoes ---\n");
    printf("Comparacoes (busca sequencial - vetor): %ld\n", comparacoesSeqVetor);
    printf("Comparacoes (busca binaria - vetor): %ld\n", comparacoesBinVetor);
    printf("Comparacoes (busca sequencial - lista): %ld\n", comparacoesSeqLista);
}

/* -------------------------
   Função principal / Menu Principal
   ------------------------- */

void menuPrincipal() {
    int opc;
    do {
        printf("\n=====================================\n");
        printf("MOCHILA - Comparacao: Vetor x Lista\n");
        printf("1 - Acessar mochila (VETOR)\n");
        printf("2 - Acessar mochila (LISTA ENCADEADA)\n");
        printf("3 - Exibir relatorio de comparacoes\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opc) != 1) { limparBufferEntrada(); printf("Entrada invalida.\n"); continue; }
        limparBufferEntrada();

        if (opc == 1) menuVetor();
        else if (opc == 2) menuLista();
        else if (opc == 3) relatorioComparacoes();
        else if (opc == 0) break;
        else printf("Opcao invalida.\n");

        pausar();
    } while (opc != 0);
}

/* -------------------------
   Limpeza final: desalocar lista encadeada
   ------------------------- */

void liberarLista() {
    No* p = headLista;
    while (p != NULL) {
        No* prox = p->proximo;
        free(p);
        p = prox;
    }
    headLista = NULL;
}

/* -------------------------
   main
   ------------------------- */

int main() {
    printf("=== MOCHILA: Vetor vs Lista Encadeada - Free Fire Island ===\n");
    printf("Comparativo de performace e operacoes basicas.\n\n");
    menuPrincipal();

    // libera memória da lista (se restar)
    liberarLista();

    printf("\nEncerrando programa. Ate a proxima fuga!\n");
    return 0;
}