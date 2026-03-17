// Projeto Maquina de Cafe - snacks
// Autor: Afonso Rosa e Dinis Monteiro
// Data: 17/03/2026
// Descricao: Maquina de cafe automatica

#include <iostream>
#include <string>
#include <iomanip>
#include <locale>

using namespace std;

// Constantes
const int MAX_PRODUTOS = 5;
const int PIN_ADMIN = 1234;

// Estrutura para produtos
struct Produto {
    int codigo;
    string descricao;
    double preco;
    int stock;
};

// Variáveis globais
Produto produtos[MAX_PRODUTOS];
int total_produtos = 0;
double total_vendido = 0.0;

// Funções principais
void inicializar_produtos();
void mostrar_menu();
void processar_venda(int opcao);
void modo_admin();
void mostrar_estatisticas();
void adicionar_produto();

int main() {
    // Configurar locale para portugues
    setlocale(LC_ALL, "Portuguese");
    
    inicializar_produtos();
    
    cout << "=== MAQUINA DE CAFE BYTECOFFEE ===" << endl;
    cout << "Bem-vindo!" << endl << endl;
    
    while (true) {
        mostrar_menu();
        
        int opcao;
        cout << "Digite sua opção: ";
        cin >> opcao;
        
        if (opcao == 0) {
            cout << "Encerrando maquina de cafe..." << endl;
            mostrar_estatisticas();
            break;
        } else if (opcao == -99) {
            modo_admin();
        } else if (opcao > 0 && opcao <= total_produtos) {
            processar_venda(opcao);
        } else {
            cout << "Opção inválida! Tente novamente." << endl << endl;
        }
    }
    
    return 0;
}

void inicializar_produtos() {
    // Produtos pré-configurados
    produtos[0] = {1, "Café Expresso", 1.20, 10};
    produtos[1] = {2, "Café com Leite", 1.50, 8};
    produtos[2] = {3, "Capuccino", 1.80, 6};
    produtos[3] = {4, "Chocolate Quente", 2.00, 5};
    produtos[4] = {5, "Sandes de Presunto", 2.50, 4};
    
    total_produtos = 5;
    total_vendido = 0.0;
}

void mostrar_menu() {
    cout << endl << "=== MENU DE PRODUTOS ===" << endl;
    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].stock > 0) {
            cout << produtos[i].codigo << " - " << produtos[i].descricao 
                 << " - €" << fixed << setprecision(2) << produtos[i].preco 
                 << " (Stock: " << produtos[i].stock << ")" << endl;
        } else {
            cout << produtos[i].codigo << " - " << produtos[i].descricao << " - ESGOTADO" << endl;
        }
    }
    cout << "0 - Cancelar" << endl;
    cout << "-99 - Modo Admin" << endl;
    cout << "========================" << endl;
}

void processar_venda(int opcao) {
    int index = opcao - 1;
    
    if (produtos[index].stock <= 0) {
        cout << "Produto esgotado! Escolha outra opcao." << endl;
        return;
    }
    
    cout << endl << "=== VENDA: " << produtos[index].descricao << " ===" << endl;
    cout << "Preço: €" << fixed << setprecision(2) << produtos[index].preco << endl;
    
    double valor_inserido = 0.0;
    double moeda;
    
    while (valor_inserido < produtos[index].preco) {
        cout << "Valor inserido: €" << fixed << setprecision(2) << valor_inserido << endl;
        cout << "Insira moeda (0 para cancelar): €";
        cin >> moeda;
        
        if (moeda == 0) {
            cout << "Cancelamento solicitado." << endl;
            if (valor_inserido > 0) {
                cout << "Devolvendo €" << fixed << setprecision(2) << valor_inserido << endl;
            }
            return;
        } else if (moeda > 0) {
            valor_inserido += moeda;
        } else {
            cout << "Valor invalido! Tente novamente." << endl;
        }
    }
    
    // Processar pagamento
    double troco = valor_inserido - produtos[index].preco;
    
    // Atualizar stock
    produtos[index].stock--;
    
    // Atualizar total vendido
    total_vendido += produtos[index].preco;
    
    cout << endl << "=== PAGAMENTO CONCLUIDO ===" << endl;
    cout << "Produto: " << produtos[index].descricao << endl;
    cout << "Valor pago: €" << fixed << setprecision(2) << valor_inserido << endl;
    cout << "Preco: €" << fixed << setprecision(2) << produtos[index].preco << endl;
    cout << "Troco: €" << fixed << setprecision(2) << troco << endl;
    cout << "Retire seu produto!" << endl << endl;
}

void modo_admin() {
    int pin;
    cout << "Digite o PIN de administrador: ";
    cin >> pin;
    
    if (pin != PIN_ADMIN) {
        cout << "PIN incorreto! Acesso negado." << endl;
        return;
    }
    
    int opcao;
    do {
        cout << endl << "=== MODO ADMIN ===" << endl;
        cout << "1 - Adicionar produto" << endl;
        cout << "2 - Mostrar estatisticas" << endl;
        cout << "3 - Reabastecer stock" << endl;
        cout << "0 - Sair" << endl;
        cout << "Opção: ";
        cin >> opcao;
        
        switch (opcao) {
            case 1:
                adicionar_produto();
                break;
            case 2:
                mostrar_estatisticas();
                break;
            case 3: {
                int codigo, quantidade;
                cout << "Digite o código do produto: ";
                cin >> codigo;
                cout << "Quantidade a adicionar: ";
                cin >> quantidade;
                
                for (int i = 0; i < total_produtos; i++) {
                    if (produtos[i].codigo == codigo) {
                        produtos[i].stock += quantidade;
                        cout << "Stock atualizado! Novo stock: " << produtos[i].stock << endl;
                        break;
                    }
                }
                break;
            }
            case 0:
                cout << "Saindo do modo admin..." << endl;
                break;
            default:
                cout << "Opção inválida!" << endl;
        }
    } while (opcao != 0);
}

void adicionar_produto() {
    if (total_produtos >= MAX_PRODUTOS) {
        cout << "Capacidade maxima de produtos atingida!" << endl;
        return;
    }
    
    cout << "Código do produto: ";
    cin >> produtos[total_produtos].codigo;
    
    cout << "Descrição: ";
    cin.ignore();
    getline(cin, produtos[total_produtos].descricao);
    
    cout << "Preço: €";
    cin >> produtos[total_produtos].preco;
    
    cout << "Stock inicial: ";
    cin >> produtos[total_produtos].stock;
    
    total_produtos++;
    cout << "Produto adicionado com sucesso!" << endl;
}

void mostrar_estatisticas() {
    cout << endl << "=== ESTATÍSTICAS ===" << endl;
    cout << "Total vendido: €" << fixed << setprecision(2) << total_vendido << endl;
    cout << "Total de produtos: " << total_produtos << endl;
    
    int produtos_esgotados = 0;
    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].stock == 0) {
            produtos_esgotados++;
        }
    }
    cout << "Produtos esgotados: " << produtos_esgotados << "/" << total_produtos << endl;
    cout << "====================" << endl;
}
