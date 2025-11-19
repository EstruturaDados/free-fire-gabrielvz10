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
#include <time.h>

#define MAX_COMPONENTES 20
#define TAM_NOME 30
#define TAM_TIPO 20

/* --- Struct Componente --- */
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int prioridade; /* 1 (baixa) .. 10 (alta) */
} Componente;

/* --- Protótipos --- */
void limparNovoLinha(char *s);
void cadastrarComponentes(Componente arr[], int *n);
void mostrarComponentes(const Componente arr[], int n);

/* Ordenações (cada uma atualiza o contador de comparações passado por ponteiro) */
double bubbleSortNome(Componente arr[], int n, long *comparacoes);      /* por nome (string) */
double insertionSortTipo(Componente arr[], int n, long *comparacoes);   /* por tipo (string) */
double selectionSortPrioridade(Componente arr[], int n, long *comparacoes); /* por prioridade (int) */

/* Busca binária por nome (requer vetor ordenado por nome) */
int buscaBinariaPorNome(const Componente arr[], int n, const char chave[], long *comparacoes);

/* Utilitários */
void trocarComponente(Componente *a, Componente *b);
void copiarVetor(const Componente src[], Componente dst[], int n);

int main(void) {
    setbuf(stdout, NULL);
    Componente componentes[MAX_COMPONENTES];
    int n = 0;

    printf("=== TORRE DE RESGATE: Organização de Componentes ===\n\n");

    /* 1) Cadastro */
    cadastrarComponentes(componentes, &n);
    if (n == 0) {
        printf("Nenhum componente cadastrado. Encerrando.\n");
        return 0;
    }

    /* Fazemos cópias do vetor para que o usuário possa testar cada algoritmo
       sem interferir com os outros (mantemos original como base). */
    Componente backup[MAX_COMPONENTES];
    copiarVetor(componentes, backup, n);

    int opc;
    long comp = 0;
    double tempo_ms = 0.0;
    char chave[TAM_NOME];

    do {
        printf("\n--- MENU DE ESTRATÉGIAS ---\n");
        printf("1 - Bubble Sort por NOME (ordenacao) + busca binaria\n");
        printf("2 - Insertion Sort por TIPO (ordenacao)\n");
        printf("3 - Selection Sort por PRIORIDADE (ordenacao)\n");
        printf("4 - Mostrar componentes atualmente (vetor atual)\n");
        printf("5 - Restaurar vetor original (antes das ordenacoes)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opc) != 1) { 
            /* consumo e continua */
            int c; while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Entrada invalida. Tente novamente.\n");
            continue;
        }
        int c = getchar(); /* consumir \n restante */

        switch (opc) {
            case 1:
                /* bubble sort por nome e depois busca binária por um componente-chave */
                copiarVetor(backup, componentes, n); /* recupera o estado original */
                comp = 0;
                tempo_ms = bubbleSortNome(componentes, n, &comp);
                printf("\nResultado da ordenacao (Bubble sort por NOME):\n");
                mostrarComponentes(componentes, n);
                printf("Comparacoes durante bubble sort: %ld | Tempo: %.3f ms\n", comp, tempo_ms);

                /* busca binária (após ordenação por nome) */
                printf("\nDigite o NOME do componente-chave para buscar (busca binaria): ");
                if (fgets(chave, sizeof(chave), stdin) == NULL) chave[0] = '\0';
                limparNovoLinha(chave);
                if (strlen(chave) == 0) {
                    printf("Nenhuma chave informada. Pulando busca.\n");
                } else {
                    long comp_bin = 0;
                    clock_t inicio = clock();
                    int idx = buscaBinariaPorNome(componentes, n, chave, &comp_bin);
                    clock_t fim = clock();
                    double tempoBusca = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000.0;
                    if (idx >= 0) {
                        printf("Componente-CHAVE encontrado no indice %d:\n", idx);
                        printf("  Nome: %s | Tipo: %s | Prioridade: %d\n",
                               componentes[idx].nome, componentes[idx].tipo, componentes[idx].prioridade);
                    } else {
                        printf("Componente-CHAVE NAO encontrado pela busca binaria.\n");
                    }
                    printf("Comparacoes (busca binaria): %ld | Tempo: %.3f ms\n", comp_bin, tempoBusca);
                }
                break;

            case 2:
                copiarVetor(backup, componentes, n);
                comp = 0;
                tempo_ms = insertionSortTipo(componentes, n, &comp);
                printf("\nResultado da ordenacao (Insertion sort por TIPO):\n");
                mostrarComponentes(componentes, n);
                printf("Comparacoes durante insertion sort: %ld | Tempo: %.3f ms\n", comp, tempo_ms);
                break;

            case 3:
                copiarVetor(backup, componentes, n);
                comp = 0;
                tempo_ms = selectionSortPrioridade(componentes, n, &comp);
                printf("\nResultado da ordenacao (Selection sort por PRIORIDADE - decrescente):\n");
                mostrarComponentes(componentes, n);
                printf("Comparacoes durante selection sort: %ld | Tempo: %.3f ms\n", comp, tempo_ms);
                break;

            case 4:
                printf("\nVetor atual de componentes:\n");
                mostrarComponentes(componentes, n);
                break;

            case 5:
                copiarVetor(backup, componentes, n);
                printf("Vetor restaurado ao estado original de cadastro.\n");
                break;

            case 0:
                printf("Encerrando modulo. Boa sorte na fuga!\n");
                break;

            default:
                printf("Opcao invalida.\n");
                break;
        }

    } while (opc != 0);

    return 0;
}

/* -------------------------
   Implementações
   ------------------------- */

/* Remove '\n' caso exista ao final da string lida por fgets */
void limparNovoLinha(char *s) {
    size_t L = strlen(s);
    if (L == 0) return;
    if (s[L - 1] == '\n') s[L - 1] = '\0';
}

/* Leitura segura dos componentes (fgets para strings) */
void cadastrarComponentes(Componente arr[], int *n) {
    int quantidade = 0;
    printf("Quantos componentes deseja cadastrar? (max %d): ", MAX_COMPONENTES);
    if (scanf("%d", &quantidade) != 1) {
        int c; while ((c = getchar()) != '\n' && c != EOF) {}
        printf("Entrada invalida. Encerrando cadastro.\n");
        *n = 0;
        return;
    }
    if (quantidade < 0) quantidade = 0;
    if (quantidade > MAX_COMPONENTES) quantidade = MAX_COMPONENTES;
    int c = getchar(); /* consome newline */

    for (int i = 0; i < quantidade; i++) {
        printf("\n--- Cadastro do componente %d ---\n", i + 1);

        printf("Nome (ex: chip central): ");
        if (fgets(arr[i].nome, sizeof(arr[i].nome), stdin) == NULL) arr[i].nome[0] = '\0';
        limparNovoLinha(arr[i].nome);

        printf("Tipo (ex: controle/suporte/propulsao): ");
        if (fgets(arr[i].tipo, sizeof(arr[i].tipo), stdin) == NULL) arr[i].tipo[0] = '\0';
        limparNovoLinha(arr[i].tipo);

        printf("Prioridade (1 a 10): ");
        while (scanf("%d", &arr[i].prioridade) != 1 || arr[i].prioridade < 1 || arr[i].prioridade > 10) {
            int ch; while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("Valor invalido. Digite um inteiro entre 1 e 10: ");
        }
        int ch; while ((ch = getchar()) != '\n' && ch != EOF) {}
    }
    *n = quantidade;
}

/* Imprime o vetor de componentes em formato de tabela */
void mostrarComponentes(const Componente arr[], int n) {
    if (n == 0) {
        printf("(Nenhum componente)\n");
        return;
    }
    printf("Idx | Nome                         | Tipo               | Prioridade\n");
    printf("----+------------------------------+--------------------+-----------\n");
    for (int i = 0; i < n; i++) {
        printf("%3d | %-28s | %-18s | %9d\n",
               i, arr[i].nome, arr[i].tipo, arr[i].prioridade);
    }
}

/* Troca dois componentes */
void trocarComponente(Componente *a, Componente *b) {
    Componente tmp = *a;
    *a = *b;
    *b = tmp;
}

/* Copia vetor src para dst */
void copiarVetor(const Componente src[], Componente dst[], int n) {
    for (int i = 0; i < n; i++) dst[i] = src[i];
}

/* -------------------------
   Bubble Sort por NOME (ordem alfabetica crescente)
   Conta comparacoes no ponteiro comparacoes e retorna tempo em ms
   ------------------------- */
double bubbleSortNome(Componente arr[], int n, long *comparacoes) {
    clock_t inicio = clock();
    *comparacoes = 0;
    if (n <= 1) {
        return 0.0;
    }
    bool trocou;
    for (int i = 0; i < n - 1; i++) {
        trocou = false;
        for (int j = 0; j < n - 1 - i; j++) {
            (*comparacoes)++;
            if (strcmp(arr[j].nome, arr[j + 1].nome) > 0) {
                trocarComponente(&arr[j], &arr[j + 1]);
                trocou = true;
            }
        }
        if (!trocou) break;
    }
    clock_t fim = clock();
    return (double)(fim - inicio) / CLOCKS_PER_SEC * 1000.0;
}

/* -------------------------
   Insertion Sort por TIPO (ordem alfabetica crescente)
   Conta comparacoes no ponteiro comparacoes e retorna tempo em ms
   ------------------------- */
double insertionSortTipo(Componente arr[], int n, long *comparacoes) {
    clock_t inicio = clock();
    *comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = arr[i];
        int j = i - 1;
        /* enquanto j >= 0 e arr[j].tipo > chave.tipo */
        while (j >= 0) {
            (*comparacoes)++;
            if (strcmp(arr[j].tipo, chave.tipo) > 0) {
                arr[j + 1] = arr[j];
                j--;
            } else break;
        }
        arr[j + 1] = chave;
    }
    clock_t fim = clock();
    return (double)(fim - inicio) / CLOCKS_PER_SEC * 1000.0;
}

/* -------------------------
   Selection Sort por PRIORIDADE (ordem decrescente: maior prioridade primeiro)
   Conta comparacoes no ponteiro comparacoes e retorna tempo em ms
   ------------------------- */
double selectionSortPrioridade(Componente arr[], int n, long *comparacoes) {
    clock_t inicio = clock();
    *comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int melhor = i; /* índice do maior prioridade */
        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (arr[j].prioridade > arr[melhor].prioridade) {
                melhor = j;
            }
        }
        if (melhor != i) {
            trocarComponente(&arr[i], &arr[melhor]);
        }
    }
    clock_t fim = clock();
    return (double)(fim - inicio) / CLOCKS_PER_SEC * 1000.0;
}

/* -------------------------
   Busca Binária por NOME (vetor deve estar ordenado por nome)
   Conta comparacoes realizadas em comparacoes (passado por ponteiro)
   Retorna índice ou -1 se não encontrado
   ------------------------- */
int buscaBinariaPorNome(const Componente arr[], int n, const char chave[], long *comparacoes) {
    int left = 0, right = n - 1;
    *comparacoes = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        (*comparacoes)++;
        int cmp = strcmp(arr[mid].nome, chave);
        if (cmp == 0) return mid;
        else if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}