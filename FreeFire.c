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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Iniciante
// Este programa simula a gestão inicial da mochila do jogador,
// permitindo cadastrar, remover, listar e buscar itens coletados.

// Struct Item:
// Representa um objeto coletado, com nome, tipo e quantidade.
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual)
Item mochila[10];
int numItens = 0;

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas.
void limparTela() {
    for (int i = 0; i < 40; i++) {
        printf("\n");
    }
}

// exibirMenu():
// Mostra o menu principal ao jogador.
void exibirMenu() {
    printf("=== MOCHILA DO JOGADOR ===\n");
    printf("1. Adicionar um item\n");
    printf("2. Remover um item\n");
    printf("3. Listar todos os itens\n");
    printf("4. Buscar item por nome\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

// inserirItem():
// Adiciona um item ao vetor se houver espaco.
void inserirItem() {
    if (numItens >= 10) {
        printf("A mochila esta cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("Digite o nome do item: ");
    scanf("%s", novo.nome);

    printf("Digite o tipo do item (arma, municao, cura, etc): ");
    scanf("%s", novo.tipo);

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[numItens] = novo;
    numItens++;

    printf("Item adicionado com sucesso!\n");
}

// removerItem():
// Remove um item do vetor procurando pelo nome.
void removerItem() {
    if (numItens == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item que deseja remover: ");
    scanf("%s", nomeBusca);

    bool encontrado = false;

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = true;

            // Reorganiza o vetor "puxando" os itens seguintes
            for (int j = i; j < numItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }

            numItens--;
            printf("Item removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Item nao encontrado!\n");
    }
}

// listarItens():
// Exibe todos os itens cadastrados.
void listarItens() {
    if (numItens == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    printf("\n=== ITENS NA MOCHILA ===\n");
    for (int i = 0; i < numItens; i++) {
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1,
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
}

// buscarItem():
// Realiza busca sequencial por nome.
void buscarItem() {
    if (numItens == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item que deseja buscar: ");
    scanf("%s", nomeBusca);

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }

    printf("Item nao encontrado.\n");
}

int main() {
    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);
        limparTela();

        switch (opcao) {
            case 1:
                inserirItem();
                break;

            case 2:
                removerItem();
                break;

            case 3:
                listarItens();
                break;

            case 4:
                buscarItem();
                break;

            case 0:
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }

        printf("\n");
    } while (opcao != 0);

    return 0;
}
