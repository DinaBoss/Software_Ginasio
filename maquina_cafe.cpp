// Projeto Máquina de Café - ByteCoffee (C++)
// Autor: Afonso Rosa
// Data: 11/03/2026
// Descrição: Máquina de café automática com gestão completa de inventário

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

// Constantes
const int MAX_PRODUTOS = 10;
const int CAPACIDADE_STOCK = 12;
const int PIN_ADMIN = 1234;

// Estrutura para produtos
struct Produto {
    int codigo;
    string descricao;
    double preco;
    int stock;
    bool esgotado;
};

// Estrutura para movimentos
struct Movimento {
    int codigo_produto;
    string descricao;
    int quantidade_vendida;
    double valor_total;
};

// Variáveis globais
vector<Produto> produtos;
vector<Movimento> movimentos;
double total_vendido = 0.0;

// Funções principais
void inicializar_produtos();
void mostrar_menu();
void processar_venda(int index);
void modo_gestao();
bool validar_pin();
void configurar_produtos();
void consultar_movimentos();
void imprimir_talao(int codigo, double valor_pago, double troco, int quantidade);
void reabastecer_produtos();
void mostrar_estatisticas();

int main() {
    // Configurar locale para português
    setlocale(LC_ALL, "Portuguese");
    
    inicializar_produtos();
    
    cout << "=== MÁQUINA DE CAFÉ BYTECOFFEE v2.0 ===" << endl;
    cout << "Sistema atualizado com gestão completa" << endl;
    cout << "Bem-vindo!" << endl << endl;
    
    while (true) {
        mostrar_menu();
        
        int opcao;
        cout << "Digite sua opção: ";
        cin >> opcao;
        
        if (opcao == 0) {
            cout << "Encerrando máquina de café..." << endl;
            mostrar_estatisticas();
            break;
        } else if (opcao == -99) {
            modo_gestao();
        } else if (opcao > 0 && opcao <= produtos.size()) {
            processar_venda(opcao - 1);
        } else {
            cout << "Opção inválida! Tente novamente." << endl << endl;
        }
    }
    
    return 0;
}

void inicializar_produtos() {
    // Produtos pré-configurados (vazio inicialmente)
    produtos.clear();
    movimentos.clear();
    total_vendido = 0.0;
}

void mostrar_menu() {
    cout << endl << "=== MENU DE PRODUTOS ===" << endl;
    if (produtos.empty()) {
        cout << "NECESSÁRIO CONFIGURAR PRODUTOS (Modo Gestão -99)" << endl;
    } else {
        for (size_t i = 0; i < produtos.size(); i++) {
            if (produtos[i].esgotado) {
                cout << produtos[i].codigo << " - " << produtos[i].descricao << " - ESGOTADO" << endl;
            } else {
                cout << produtos[i].codigo << " - " << produtos[i].descricao 
                     << " - R$" << fixed << setprecision(2) << produtos[i].preco 
                     << " (Stock: " << produtos[i].stock << ")" << endl;
            }
        }
    }
    cout << "0 - Cancelar" << endl;
    cout << "-99 - Modo Gestão" << endl;
    cout << "========================" << endl;
}

void processar_venda(int index) {
    if (produtos[index].esgotado || produtos[index].stock <= 0) {
        cout << "Produto esgotado! Escolha outra opção." << endl;
        return;
    }
    
    cout << endl << "=== VENDA: " << produtos[index].descricao << " ===" << endl;
    cout << "Preço: R$" << fixed << setprecision(2) << produtos[index].preco << endl;
    
    double valor_inserido = 0.0;
    double moeda;
    
    while (valor_inserido < produtos[index].preco) {
        cout << "Valor inserido: R$" << fixed << setprecision(2) << valor_inserido << endl;
        cout << "Insira moeda (0 para cancelar): R$";
        cin >> moeda;
        
        if (moeda == 0) {
            cout << "Cancelamento solicitado." << endl;
            if (valor_inserido > 0) {
                cout << "Devolvendo R$" << fixed << setprecision(2) << valor_inserido << endl;
            }
            return;
        } else if (moeda < 0) {
            cout << "Valor inválido! Tente novamente." << endl;
        } else {
            valor_inserido += moeda;
        }
    }
    
    // Processar pagamento
    double troco = valor_inserido - produtos[index].preco;
    
    if (troco >= 0) {
        // Atualizar stock
        produtos[index].stock--;
        if (produtos[index].stock == 0) {
            produtos[index].esgotado = true;
        }
        
        // Atualizar total vendido
        total_vendido += produtos[index].preco;
        
        // Registrar movimento
        int mov_index = -1;
        for (size_t i = 0; i < movimentos.size(); i++) {
            if (movimentos[i].codigo_produto == produtos[index].codigo) {
                mov_index = i;
                break;
            }
        }
        
        if (mov_index == -1) {
            // Novo movimento
            Movimento novo_mov;
            novo_mov.codigo_produto = produtos[index].codigo;
            novo_mov.descricao = produtos[index].descricao;
            novo_mov.quantidade_vendida = 1;
            novo_mov.valor_total = produtos[index].preco;
            movimentos.push_back(novo_mov);
        } else {
            // Atualizar movimento existente
            movimentos[mov_index].quantidade_vendida++;
            movimentos[mov_index].valor_total += produtos[index].preco;
        }
        
        cout << endl << "=== PAGAMENTO CONCLUÍDO ===" << endl;
        cout << "Produto: " << produtos[index].descricao << endl;
        cout << "Valor pago: R$" << fixed << setprecision(2) << valor_inserido << endl;
        cout << "Preço: R$" << fixed << setprecision(2) << produtos[index].preco << endl;
        cout << "Troco: R$" << fixed << setprecision(2) << troco << endl;
        
        // Perguntar sobre talão
        int imprimir;
        cout << "Deseja imprimir talão? (1-Sim, 0-Não): ";
        cin >> imprimir;
        
        if (imprimir == 1) {
            imprimir_talao(produtos[index].codigo, valor_inserido, troco, 1);
        }
        
        cout << "Retire seu produto!" << endl << endl;
    }
}

void imprimir_talao(int codigo, double valor_pago, double troco, int quantidade) {
    cout << endl;
    cout << "==============================" << endl;
    cout << "    TALÃO DE VENDA" << endl;
    cout << "==============================" << endl;
    cout << "Data: 11/03/2026" << endl;
    cout << "Código: " << codigo << endl;
    cout << "Produto: " << produtos[codigo-1].descricao << endl;
    cout << "Quantidade: " << quantidade << endl;
    cout << "Valor pago: R$" << fixed << setprecision(2) << valor_pago << endl;
    cout << "Troco: R$" << fixed << setprecision(2) << troco << endl;
    cout << "==============================" << endl;
    cout << "   Obrigado pela compra!" << endl;
    cout << "==============================" << endl << endl;
}

bool validar_pin() {
    int pin;
    int tentativas = 3;
    
    while (tentativas > 0) {
        cout << "Digite o PIN de administrador: ";
        cin >> pin;
        
        if (pin == PIN_ADMIN) {
            return true;
        } else {
            tentativas--;
            cout << "PIN incorreto! Tentativas restantes: " << tentativas << endl;
        }
    }
    
    cout << "Acesso negado!" << endl;
    return false;
}

void configurar_produtos() {
    cout << endl << "=== CONFIGURAÇÃO DE PRODUTOS ===" << endl;
    cout << "Produtos atuais: " << produtos.size() << "/" << MAX_PRODUTOS << endl;
    
    int opcao;
    do {
        cout << endl << "--- MENU CONFIGURAÇÃO ---" << endl;
        cout << "1 - Adicionar produto" << endl;
        cout << "2 - Alterar produto existente" << endl;
        cout << "3 - Listar produtos" << endl;
        cout << "0 - Voltar" << endl;
        cout << "Opção: ";
        cin >> opcao;
        
        switch (opcao) {
            case 1: {
                if (produtos.size() >= MAX_PRODUTOS) {
                    cout << "Capacidade máxima de produtos atingida!" << endl;
                    break;
                }
                
                Produto novo;
                cout << "Código do produto: ";
                cin >> novo.codigo;
                cout << "Descrição: ";
                cin.ignore();
                getline(cin, novo.descricao);
                cout << "Preço: R$";
                cin >> novo.preco;
                cout << "Stock inicial (máx " << CAPACIDADE_STOCK << "): ";
                cin >> novo.stock;
                
                novo.esgotado = (novo.stock == 0);
                
                produtos.push_back(novo);
                cout << "Produto adicionado com sucesso!" << endl;
                break;
            }
            case 2: {
                int codigo;
                cout << "Digite o código do produto a alterar: ";
                cin >> codigo;
                
                int index = -1;
                for (size_t i = 0; i < produtos.size(); i++) {
                    if (produtos[i].codigo == codigo) {
                        index = i;
                        break;
                    }
                }
                
                if (index == -1) {
                    cout << "Produto não encontrado!" << endl;
                    break;
                }
                
                cout << "Produto atual: " << produtos[index].descricao << endl;
                cout << "1 - Alterar descrição" << endl;
                cout << "2 - Alterar preço" << endl;
                cout << "3 - Alterar stock" << endl;
                cout << "Opção: ";
                int alt;
                cin >> alt;
                
                switch (alt) {
                    case 1:
                        cout << "Nova descrição: ";
                        cin.ignore();
                        getline(cin, produtos[index].descricao);
                        break;
                    case 2:
                        cout << "Novo preço: R$";
                        cin >> produtos[index].preco;
                        break;
                    case 3:
                        cout << "Novo stock (máx " << CAPACIDADE_STOCK << "): ";
                        cin >> produtos[index].stock;
                        produtos[index].esgotado = (produtos[index].stock == 0);
                        break;
                }
                cout << "Produto atualizado!" << endl;
                break;
            }
            case 3:
                cout << endl << "--- LISTA DE PRODUTOS ---" << endl;
                for (size_t i = 0; i < produtos.size(); i++) {
                    cout << produtos[i].codigo << " - " << produtos[i].descricao << endl;
                    cout << "   Preço: R$" << fixed << setprecision(2) << produtos[i].preco << endl;
                    cout << "   Stock: " << produtos[i].stock << " " 
                         << (produtos[i].esgotado ? "(ESGOTADO)" : "") << endl;
                }
                break;
            case 0:
                cout << "Voltando..." << endl;
                break;
            default:
                cout << "Opção inválida!" << endl;
        }
    } while (opcao != 0);
}

void reabastecer_produtos() {
    cout << endl << "=== REABASTECIMENTO ===" << endl;
    
    for (size_t i = 0; i < produtos.size(); i++) {
        cout << produtos[i].codigo << " - " << produtos[i].descricao 
             << " (Stock: " << produtos[i].stock << "/" << CAPACIDADE_STOCK << ")" << endl;
    }
    
    int codigo, quantidade;
    cout << "Digite o código do produto (0 para voltar): ";
    cin >> codigo;
    
    if (codigo == 0) return;
    
    int index = -1;
    for (size_t i = 0; i < produtos.size(); i++) {
        if (produtos[i].codigo == codigo) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        cout << "Produto não encontrado!" << endl;
        return;
    }
    
    cout << "Quantidade a adicionar (máx " << (CAPACIDADE_STOCK - produtos[index].stock) << "): ";
    cin >> quantidade;
    
    if (quantidade > 0 && quantidade <= CAPACIDADE_STOCK - produtos[index].stock) {
        produtos[index].stock += quantidade;
        produtos[index].esgotado = false;
        cout << "Reabastecido com sucesso! Novo stock: " << produtos[index].stock << endl;
    } else {
        cout << "Quantidade inválida!" << endl;
    }
}

void consultar_movimentos() {
    cout << endl << "=== RELATÓRIO DE VENDAS ===" << endl;
    cout << "Total vendido: R$" << fixed << setprecision(2) << total_vendido << endl;
    cout << "Total de transações: " << movimentos.size() << endl;
    
    if (!movimentos.empty()) {
        cout << endl << "--- VENDAS POR PRODUTO ---" << endl;
        for (size_t i = 0; i < movimentos.size(); i++) {
            cout << movimentos[i].descricao << ": " << movimentos[i].quantidade_vendida 
                 << " unidades - R$" << fixed << setprecision(2) << movimentos[i].valor_total << endl;
        }
    }
    
    cout << endl << "--- ESTOQUE ATUAL ---" << endl;
    for (size_t i = 0; i < produtos.size(); i++) {
        cout << produtos[i].descricao << ": " << produtos[i].stock << " unidades";
        if (produtos[i].esgotado) {
            cout << " (ESGOTADO)";
        }
        cout << endl;
    }
    cout << "========================" << endl;
}

void mostrar_estatisticas() {
    cout << endl << "=== ESTATÍSTICAS FINAIS ===" << endl;
    cout << "Total vendido no período: R$" << fixed << setprecision(2) << total_vendido << endl;
    cout << "Total de produtos configurados: " << produtos.size() << endl;
    cout << "Total de transações: " << movimentos.size() << endl;
    
    int produtos_esgotados = 0;
    for (size_t i = 0; i < produtos.size(); i++) {
        if (produtos[i].esgotado) produtos_esgotados++;
    }
    cout << "Produtos esgotados: " << produtos_esgotados << "/" << produtos.size() << endl;
    cout << "============================" << endl;
}

void modo_gestao() {
    cout << endl << "=== MODO DE GESTÃO ===" << endl;
    
    if (!validar_pin()) {
        return;
    }
    
    int opcao;
    do {
        cout << endl << "--- MENU GESTÃO ---" << endl;
        cout << "1 - Configurar produtos" << endl;
        cout << "2 - Consultar movimentos" << endl;
        cout << "3 - Reabastecer produtos" << endl;
        cout << "0 - Sair do modo gestão" << endl;
        cout << "Opção: ";
        cin >> opcao;
        
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
                cout << "Saindo do modo gestão..." << endl;
                break;
            default:
                cout << "Opção inválida!" << endl;
        }
    } while (opcao != 0);
}
