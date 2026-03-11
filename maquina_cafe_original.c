// Projeto Máquina de Café - Versão Original
// Autor: Afonso Rosa
// Data: 11/03/2026
// Descrição: Simulação de máquina de café automática com painel de seleção

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 10
#define CAPACIDADE_STOCK 12
#define PIN_ADMIN 1234

// Estrutura para produtos
typedef struct {
    int codigo;
    char descricao[50];
    float preco;
    int stock;
    int esgotado;
} Produto;

// Variáveis globais
Produto produtos[MAX_PRODUTOS];
int total_produtos = 0;
float total_vendido = 0.0;

// Funções principais
void inicializar_produtos();
void mostrar_menu();
void processar_venda();
void modo_gestao();
int validar_pin();
void consultar_movimentos();
void imprimir_talao(int codigo, float valor_pago, float troco, int quantidade);

int main() {
    inicializar_produtos();
    
    printf("=== MÁQUINA DE CAFÉ BYTECOFFEE ===\n");
    printf("Bem-vindo!\n\n");
    
    while (1) {
        mostrar_menu();
        
        int opcao;
        printf("Digite sua opção: ");
        scanf("%d", &opcao);
        
        if (opcao == 0) {
            printf("Encerrando máquina de café...\n");
            break;
        } else if (opcao == -99) {
            modo_gestao();
        } else if (opcao > 0 && opcao <= total_produtos) {
            processar_venda(opcao - 1);
        } else {
            printf("Opção inválida! Tente novamente.\n\n");
        }
    }
    
    return 0;
}

void inicializar_produtos() {
    // Produtos pré-configurados
    strcpy(produtos[0].descricao, "Café Expresso");
    produtos[0].preco = 0.50;
    produtos[0].stock = 10;
    produtos[0].codigo = 1;
    produtos[0].esgotado = 0;
    
    strcpy(produtos[1].descricao, "Café com Leite");
    produtos[1].preco = 0.80;
    produtos[1].stock = 8;
    produtos[1].codigo = 2;
    produtos[1].esgotado = 0;
    
    strcpy(produtos[2].descricao, "Capuccino");
    produtos[2].preco = 1.20;
    produtos[2].stock = 5;
    produtos[2].codigo = 3;
    produtos[2].esgotado = 0;
    
    strcpy(produtos[3].descricao, "Chocolate Quente");
    produtos[3].preco = 1.00;
    produtos[3].stock = 6;
    produtos[3].codigo = 4;
    produtos[3].esgotado = 0;
    
    strcpy(produtos[4].descricao, "Chá Verde");
    produtos[4].preco = 0.70;
    produtos[4].stock = 12;
    produtos[4].codigo = 5;
    produtos[4].esgotado = 0;
    
    total_produtos = 5;
}

void mostrar_menu() {
    printf("\n=== MENU DE PRODUTOS ===\n");
    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].esgotado) {
            printf("%d - %s - ESGOTADO\n", produtos[i].codigo, produtos[i].descricao);
        } else {
            printf("%d - %s - R$%.2f (Stock: %d)\n", 
                   produtos[i].codigo, produtos[i].descricao, produtos[i].preco, produtos[i].stock);
        }
    }
    printf("0 - Cancelar\n");
    printf("-99 - Modo Gestão\n");
    printf("========================\n");
}

void processar_venda(int index) {
    if (produtos[index].esgotado || produtos[index].stock <= 0) {
        printf("Produto esgotado! Escolha outra opção.\n");
        return;
    }
    
    printf("\n=== VENDA: %s ===\n", produtos[index].descricao);
    printf("Preço: R$%.2f\n", produtos[index].preco);
    
    float valor_inserido = 0.0;
    float moeda;
    
    while (valor_inserido < produtos[index].preco) {
        printf("Valor inserido: R$%.2f\n", valor_inserido);
        printf("Insira moeda (0 para cancelar): R$");
        scanf("%f", &moeda);
        
        if (moeda == 0) {
            printf("Cancelamento solicitado.\n");
            if (valor_inserido > 0) {
                printf("Devolvendo R$%.2f\n", valor_inserido);
            }
            return;
        } else if (moeda < 0) {
            printf("Valor inválido! Tente novamente.\n");
        } else {
            valor_inserido += moeda;
        }
    }
    
    // Processar pagamento
    float troco = valor_inserido - produtos[index].preco;
    
    if (troco >= 0) {
        // Atualizar stock
        produtos[index].stock--;
        if (produtos[index].stock == 0) {
            produtos[index].esgotado = 1;
        }
        
        // Atualizar total vendido
        total_vendido += produtos[index].preco;
        
        printf("\n=== PAGAMENTO CONCLUÍDO ===\n");
        printf("Produto: %s\n", produtos[index].descricao);
        printf("Valor pago: R$%.2f\n", valor_inserido);
        printf("Preço: R$%.2f\n", produtos[index].preco);
        printf("Troco: R$%.2f\n", troco);
        
        // Perguntar sobre talão
        int imprimir;
        printf("Deseja imprimir talão? (1-Sim, 0-Não): ");
        scanf("%d", &imprimir);
        
        if (imprimir == 1) {
            imprimir_talao(produtos[index].codigo, valor_inserido, troco, 1);
        }
        
        printf("Retire seu produto!\n\n");
    }
}

void imprimir_talao(int codigo, float valor_pago, float troco, int quantidade) {
    printf("\n");
    printf("==============================\n");
    printf("    TALÃO DE VENDA\n");
    printf("==============================\n");
    printf("Data: 11/03/2026\n");
    printf("Produto: %s\n", produtos[codigo-1].descricao);
    printf("Quantidade: %d\n", quantidade);
    printf("Valor pago: R$%.2f\n", valor_pago);
    printf("Troco: R$%.2f\n", troco);
    printf("==============================\n");
    printf("   Obrigado pela compra!\n");
    printf("==============================\n\n");
}

int validar_pin() {
    int pin;
    int tentativas = 3;
    
    while (tentativas > 0) {
        printf("Digite o PIN de administrador: ");
        scanf("%d", &pin);
        
        if (pin == PIN_ADMIN) {
            return 1;
        } else {
            tentativas--;
            printf("PIN incorreto! Tentativas restantes: %d\n", tentativas);
        }
    }
    
    printf("Acesso negado!\n");
    return 0;
}

void modo_gestao() {
    printf("\n=== MODO DE GESTÃO ===\n");
    
    if (!validar_pin()) {
        return;
    }
    
    int opcao;
    do {
        printf("\n--- MENU GESTÃO ---\n");
        printf("1 - Consultar movimentos\n");
        printf("2 - Reabastecer produtos\n");
        printf("3 - Alterar preços\n");
        printf("0 - Sair do modo gestão\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                consultar_movimentos();
                break;
            case 2:
                printf("Função de reabastecimento não implementada nesta versão.\n");
                break;
            case 3:
                printf("Função de alteração de preços não implementada nesta versão.\n");
                break;
            case 0:
                printf("Saindo do modo gestão...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

void consultar_movimentos() {
    printf("\n=== RELATÓRIO DE VENDAS ===\n");
    printf("Total vendido: R$%.2f\n", total_vendido);
    
    printf("\n--- ESTOQUE ATUAL ---\n");
    for (int i = 0; i < total_produtos; i++) {
        printf("%s: %d unidades", produtos[i].descricao, produtos[i].stock);
        if (produtos[i].esgotado) {
            printf(" (ESGOTADO)");
        }
        printf("\n");
    }
    printf("========================\n");
}
