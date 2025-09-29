#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
void limparTela() {
    system("cls");  
    printf("\n\n");
}

void exibirMenu() {
    limparTela();
    printf("--- 🛡️ MOCHILA COM BUSCA (AVENTUREIRO) ---\n");
    printf("Itens na Mochila: %d/%d\n", numItens, MAX_ITENS);
    printf("1. Adicionar Item\n");
    printf("2. Remover Item por Nome\n");
    printf("3. Listar Itens Cadastrados\n");
    printf("4. **BUSCAR ITEM POR NOME (NOVIDADE)**\n"); // Opção adicionada
    printf("0. Sair do Programa\n");
    printf("Escolha uma opção: ");
}

void adicionarItem() { 
    if (numItens >= MAX_ITENS) {
        printf("\nMOCHILA CHEIA! Não é possível adicionar mais itens.\n");
        return;
    }
    printf("\n--- ADICIONAR NOVO ITEM ---\n");
    printf("Nome do Item (max %d): ", TAM_NOME - 1);
    scanf(" %49[^\n]", mochila[numItens].nome);
    printf("Tipo do Item (ex: Arma, Curativo, Munição) (max %d): ", TAM_TIPO - 1);
    scanf(" %29[^\n]", mochila[numItens].tipo);
    printf("Quantidade: ");
    while (scanf("%d", &mochila[numItens].quantidade) != 1 || mochila[numItens].quantidade <= 0) {
        printf("Quantidade inválida. Digite um número positivo: ");
        while (getchar() != '\n'); 
    }
    numItens++;
    printf("\nItem \"%s\" adicionado com sucesso!\n", mochila[numItens - 1].nome);
}

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
    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            indiceRemover = i;
            break;
        }
    }
    if (indiceRemover != -1) {
        for (int i = indiceRemover; i < numItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        numItens--;
        printf("\nItem \"%s\" removido com sucesso!\n", nomeBusca);
    } else {
        printf("\nERRO: Item \"%s\" não encontrado na mochila.\n", nomeBusca);
    }
}

void listarItens() { 
    printf("\n--- ITENS NA MOCHILA ---\n");
    if (numItens == 0) {
        printf("A mochila está vazia.\n");
        return;
    }
    printf("+--------------------------------------------------+------------------------------+------------+\n");
    printf("| NOME                                             | TIPO                         | QUANTIDADE |\n");
    printf("+--------------------------------------------------+------------------------------+------------+\n");
    for (int i = 0; i < numItens; i++) {
        printf("| %-48s | %-28s | %10d |\n", 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade);
    }
    printf("+--------------------------------------------------+------------------------------+------------+\n");
}


// --- Buscar Item por Nome (Busca Sequencial) ---
void buscarItemPorNome() {
    if (numItens == 0) {
        printf("\nA mochila está vazia. Nada para buscar.\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\n--- BUSCA SEQUENCIAL POR NOME ---\n");
    printf("Digite o nome do item que você procura: ");
    scanf(" %49[^\n]", nomeBusca);

    int encontrado = 0; // Flag de controle (0 = não encontrado, 1 = encontrado)

    for (int i = 0; i < numItens; i++) {
        // Compara a string de busca com o nome do item atual
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n✅ Item Encontrado (Posição %d):\n", i + 1);
            printf("----------------------------------------\n");
            printf("Nome:       %s\n", mochila[i].nome);
            printf("Tipo:       %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("----------------------------------------\n");
            encontrado = 1; // Item encontrado
            break; // Sai do loop assim que encontrar o primeiro
        }
    }

    if (!encontrado) {
        printf("\n❌ ERRO AMIGÁVEL: Item \"%s\" não foi encontrado na mochila.\n", nomeBusca);
        printf("Verifique se o nome foi digitado corretamente (diferencia maiúsculas e minúsculas).\n");
    }
}


// --- Função Principal ---
int main() {
    int opcao;

    do {
        exibirMenu();
        if (scanf("%d", &opcao) != 1) {
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
            case 4: // NOVA OPÇÃO
                buscarItemPorNome();
                break;
            case 0:
                printf("\nSalvando inventário... Fuga suspensa. Até mais!\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
                break;
        }

        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            // Limpa o buffer de entrada do ENTER após as operações
            while (getchar() != '\n'); 
        }

    } while (opcao != 0);

    return 0;
}