#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Para system("cls") ou system("clear") se necessário

// --- Definições Globais ---
#define MAX_ITENS 10
#define TAM_NOME 50
#define TAM_TIPO 30

// Estrutura para representar um Item da mochila
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

// Variáveis globais para o inventário
Item mochila[MAX_ITENS];
int numItens = 0;

// --- Funções Auxiliares ---

// Simula a limpeza da tela
void limparTela() {
    // Tenta limpar a tela. Pode precisar de ajuste dependendo do SO/Terminal.
    // system("cls"); // Para Windows
    // system("clear"); // Para Linux/macOS
    printf("\n\n"); // Uma alternativa simples para pular linhas
}

// Exibe o menu principal
void exibirMenu() {
    limparTela();
    printf("--- 🎒 INVENTÁRIO BÁSICO (NOVAUTO) ---\n");
    printf("Itens na Mochila: %d/%d\n", numItens, MAX_ITENS);
    printf("1. Adicionar Item\n");
    printf("2. Remover Item por Nome\n");
    printf("3. Listar Itens Cadastrados\n");
    printf("0. Sair do Programa\n");
    printf("Escolha uma opção: ");
}

// --- Funções de Funcionalidade ---

// 1. Adicionar Item
void adicionarItem() {
    if (numItens >= MAX_ITENS) {
        printf("\nMOCHILA CHEIA! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("\n--- ADICIONAR NOVO ITEM ---\n");

    // Coleta dados
    printf("Nome do Item (max %d): ", TAM_NOME - 1);
    scanf(" %49[^\n]", mochila[numItens].nome); // Leitura de string com espaços, limitando o tamanho

    printf("Tipo do Item (ex: Arma, Curativo, Munição) (max %d): ", TAM_TIPO - 1);
    scanf(" %29[^\n]", mochila[numItens].tipo);

    printf("Quantidade: ");
    while (scanf("%d", &mochila[numItens].quantidade) != 1 || mochila[numItens].quantidade <= 0) {
        printf("Quantidade inválida. Digite um número positivo: ");
        // Limpa o buffer de entrada para evitar loop infinito em caso de entrada não numérica
        while (getchar() != '\n'); 
    }
    
    // Atualiza o contador de itens
    numItens++;
    printf("\nItem \"%s\" adicionado com sucesso!\n", mochila[numItens - 1].nome);
}

// 2. Remover Item por Nome
void removerItem() {
    if (numItens == 0) {
        printf("\nA mochila está vazia. Nada para remover.\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\n--- REMOVER ITEM ---\n");
    printf("Digite o nome do item a ser removido: ");
    scanf(" %49[^\n]", nomeBusca);

    int indiceRemover = -1;

    // Busca sequencial (sem otimizações)
    for (int i = 0; i < numItens; i++) {
        // strcmp retorna 0 se as strings forem idênticas
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            indiceRemover = i;
            break; // Item encontrado
        }
    }

    if (indiceRemover != -1) {
        // Item encontrado: move os itens seguintes para preencher a lacuna
        for (int i = indiceRemover; i < numItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        numItens--;
        printf("\nItem \"%s\" removido com sucesso!\n", nomeBusca);
    } else {
        printf("\nERRO: Item \"%s\" não encontrado na mochila.\n", nomeBusca);
    }
}

// 3. Listar Itens Cadastrados
void listarItens() {
    printf("\n--- ITENS NA MOCHILA ---\n");

    if (numItens == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    // Cabeçalho da tabela
    printf("+--------------------------------------------------+------------------------------+------------+\n");
    printf("| NOME                                             | TIPO                         | QUANTIDADE |\n");
    printf("+--------------------------------------------------+------------------------------+------------+\n");

    // Exibe os dados
    for (int i = 0; i < numItens; i++) {
        printf("| %-48s | %-28s | %10d |\n", 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade);
    }

    // Rodapé da tabela
    printf("+--------------------------------------------------+------------------------------+------------+\n");
}


// --- Função Principal ---
int main() {
    int opcao;

    do {
        exibirMenu();
        if (scanf("%d", &opcao) != 1) {
            // Se a leitura falhar (ex: usuário digitou texto), limpa o buffer e define uma opção inválida
            while (getchar() != '\n'); 
            opcao = -1; 
        }

        switch (opcao) {
            case 1:
                adicionarItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 0:
                printf("\nSalvando inventário... Fuga cancelada. Até mais!\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
                break;
        }

        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            // Garante que o buffer está limpo e espera por um ENTER
            if (opcao != 1 && opcao != 2 && opcao != 3) {
                 while (getchar() != '\n'); // Limpa se a opção for inválida
            }
            if (getchar() != '\n'); // Espera pelo ENTER
        }

    } while (opcao != 0);

    return 0;
}