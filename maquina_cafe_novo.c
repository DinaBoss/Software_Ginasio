// Projeto Máquina de Café - Versão Atualizada
// Autor: Afonso Rosa
// Data: 11/03/2026
// Descrição: Versão atualizada com gestão completa de inventário

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

// Estrutura para movimentos
typedef struct {
    int codigo_produto;
    char descricao[50];
    int quantidade_vendida;
    float valor_total;
} Movimento;

// Variáveis globais
Produto produtos[MAX_PRODUTOS];
Movimento movimentos[100];
int total_produtos = 0;
int total_movimentos = 0;
float total_vendido = 0.0;

// Funções principais
void inicializar_produtos();
void mostrar_menu();
void processar_venda();
void modo_gestao();
int validar_pin();
void configurar_produtos();
void consultar_movimentos();
void imprimir_talao(int codigo, float valor_pago, float troco, int quantidade);
void reabastecer_produtos();
void mostrar_estatisticas();

int main() {
    inicializar_produtos();
    
    printf("=== MÁQUINA DE CAFÉ BYTECOFFEE v2.0 ===\n");
    printf("Sistema atualizado com gestão completa\n");
    printf("Bem-vindo!\n\n");
    
    while (1) {
        mostrar_menu();
        
        int opcao;
        printf("Digite sua opção: ");
        scanf("%d", &opcao);
        
        if (opcao == 0) {
            printf("Encerrando máquina de café...\n");
            mostrar_estatisticas();
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
    // Produtos pré-configurados (vazio inicialmente)
    total_produtos = 0;
    total_movimentos = 0;
    total_vendido = 0.0;
}

void mostrar_menu() {
    printf("\n=== MENU DE PRODUTOS ===\n");
    if (total_produtos == 0) {
        printf("NECESSÁRIO CONFIGURAR PRODUTOS (Modo Gestão -99)\n");
    } else {
        for (int i = 0; i < total_produtos; i++) {
            if (produtos[i].esgotado) {
                printf("%d - %s - ESGOTADO\n", produtos[i].codigo, produtos[i].descricao);
            } else {
                printf("%d - %s - R$%.2f (Stock: %d)\n", 
                       produtos[i].codigo, produtos[i].descricao, produtos[i].preco, produtos[i].stock);
            }
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
        
        // Registrar movimento
        int mov_index = -1;
        for (int i = 0; i < total_movimentos; i++) {
            if (movimentos[i].codigo_produto == produtos[index].codigo) {
                mov_index = i;
                break;
            }
        }
        
        if (mov_index == -1) {
            // Novo movimento
            movimentos[total_movimentos].codigo_produto = produtos[index].codigo;
            strcpy(movimentos[total_movimentos].descricao, produtos[index].descricao);
            movimentos[total_movimentos].quantidade_vendida = 1;
            movimentos[total_movimentos].valor_total = produtos[index].preco;
            total_movimentos++;
        } else {
            // Atualizar movimento existente
            movimentos[mov_index].quantidade_vendida++;
            movimentos[mov_index].valor_total += produtos[index].preco;
        }
        
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
    printf("Código: %d\n", codigo);
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

void configurar_produtos() {
    printf("\n=== CONFIGURAÇÃO DE PRODUTOS ===\n");
    printf("Produtos atuais: %d/%d\n", total_produtos, MAX_PRODUTOS);
    
    int opcao;
    do {
        printf("\n--- MENU CONFIGURAÇÃO ---\n");
        printf("1 - Adicionar produto\n");
        printf("2 - Alterar produto existente\n");
        printf("3 - Listar produtos\n");
        printf("0 - Voltar\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1: {
                if (total_produtos >= MAX_PRODUTOS) {
                    printf("Capacidade máxima de produtos atingida!\n");
                    break;
                }
                
                Produto novo;
                printf("Código do produto: ");
                scanf("%d", &novo.codigo);
                printf("Descrição: ");
                scanf(" %[^\n]", novo.descricao);
                printf("Preço: R$");
                scanf("%f", &novo.preco);
                printf("Stock inicial (máx %d): ", CAPACIDADE_STOCK);
                scanf("%d", &novo.stock);
                
                novo.esgotado = (novo.stock == 0) ? 1 : 0;
                
                produtos[total_produtos] = novo;
                total_produtos++;
                printf("Produto adicionado com sucesso!\n");
                break;
            }
            case 2: {
                int codigo;
                printf("Digite o código do produto a alterar: ");
                scanf("%d", &codigo);
                
                int index = -1;
                for (int i = 0; i < total_produtos; i++) {
                    if (produtos[i].codigo == codigo) {
                        index = i;
                        break;
                    }
                }
                
                if (index == -1) {
                    printf("Produto não encontrado!\n");
                    break;
                }
                
                printf("Produto atual: %s\n", produtos[index].descricao);
                printf("1 - Alterar descrição\n");
                printf("2 - Alterar preço\n");
                printf("3 - Alterar stock\n");
                printf("Opção: ");
                int alt;
                scanf("%d", &alt);
                
                switch (alt) {
                    case 1:
                        printf("Nova descrição: ");
                        scanf(" %[^\n]", produtos[index].descricao);
                        break;
                    case 2:
                        printf("Novo preço: R$");
                        scanf("%f", &produtos[index].preco);
                        break;
                    case 3:
                        printf("Novo stock (máx %d): ", CAPACIDADE_STOCK);
                        scanf("%d", &produtos[index].stock);
                        produtos[index].esgotado = (produtos[index].stock == 0) ? 1 : 0;
                        break;
                }
                printf("Produto atualizado!\n");
                break;
            }
            case 3:
                printf("\n--- LISTA DE PRODUTOS ---\n");
                for (int i = 0; i < total_produtos; i++) {
                    printf("%d - %s\n", produtos[i].codigo, produtos[i].descricao);
                    printf("   Preço: R$%.2f\n", produtos[i].preco);
                    printf("   Stock: %d %s\n", produtos[i].stock, 
                           produtos[i].esgotado ? "(ESGOTADO)" : "");
                }
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

void reabastecer_produtos() {
    printf("\n=== REABASTECIMENTO ===\n");
    
    for (int i = 0; i < total_produtos; i++) {
        printf("%d - %s (Stock: %d/%d)\n", 
               produtos[i].codigo, produtos[i].descricao, produtos[i].stock, CAPACIDADE_STOCK);
    }
    
    int codigo, quantidade;
    printf("Digite o código do produto (0 para voltar): ");
    scanf("%d", &codigo);
    
    if (codigo == 0) return;
    
    int index = -1;
    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].codigo == codigo) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        printf("Produto não encontrado!\n");
        return;
    }
    
    printf("Quantidade a adicionar (máx %d): ", CAPACIDADE_STOCK - produtos[index].stock);
    scanf("%d", &quantidade);
    
    if (quantidade > 0 && quantidade <= CAPACIDADE_STOCK - produtos[index].stock) {
        produtos[index].stock += quantidade;
        produtos[index].esgotado = 0;
        printf("Reabastecido com sucesso! Novo stock: %d\n", produtos[index].stock);
    } else {
        printf("Quantidade inválida!\n");
    }
}

void consultar_movimentos() {
    printf("\n=== RELATÓRIO DE VENDAS ===\n");
    printf("Total vendido: R$%.2f\n", total_vendido);
    printf("Total de transações: %d\n", total_movimentos);
    
    if (total_movimentos > 0) {
        printf("\n--- VENDAS POR PRODUTO ---\n");
        for (int i = 0; i < total_movimentos; i++) {
            printf("%s: %d unidades - R$%.2f\n", 
                   movimentos[i].descricao, movimentos[i].quantidade_vendida, movimentos[i].valor_total);
        }
    }
    
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

void mostrar_estatisticas() {
    printf("\n=== ESTATÍSTICAS FINAIS ===\n");
    printf("Total vendido no período: R$%.2f\n", total_vendido);
    printf("Total de produtos configurados: %d\n", total_produtos);
    printf("Total de transações: %d\n", total_movimentos);
    
    int produtos_esgotados = 0;
    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].esgotado) produtos_esgotados++;
    }
    printf("Produtos esgotados: %d/%d\n", produtos_esgotados, total_produtos);
    printf("============================\n");
}

void modo_gestao() {
    printf("\n=== MODO DE GESTÃO ===\n");
    
    if (!validar_pin()) {
        return;
    }
    
    int opcao;
    do {
        printf("\n--- MENU GESTÃO ---\n");
        printf("1 - Configurar produtos\n");
        printf("2 - Consultar movimentos\n");
        printf("3 - Reabastecer produtos\n");
        printf("0 - Sair do modo gestão\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                configurar_produtos();
                break;
            case 2:
                consultar_movimentos();
                break;
            case 3:
                reabastecer_produtos();
                break;
            case 0:
                printf("Saindo do modo gestão...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}
