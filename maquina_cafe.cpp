// Projeto Maquina de Cafe - snacks
// Autor: Afonso Rosa e Dinis Monteiro
// Data: 11/03/2026
// Descricao: Maquina de cafe automatica com gestao completa de inventario

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <locale>
#include <algorithm>
#include <limits>

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

// Funções de validação robustas
int ler_inteiro(const string& mensagem) {
    int valor;
    while (true) {
        cout << mensagem;
        cin >> valor;
        if (cin.good()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        } else {
            cout << "Valor invalido! Digite um numero inteiro." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

double ler_decimal(const string& mensagem) {
    double valor;
    while (true) {
        cout << mensagem;
        cin >> valor;
        if (cin.good()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        } else {
            cout << "Valor invalido! Digite um numero decimal." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

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
    // Configurar locale para portugues
    setlocale(LC_ALL, "Portuguese");
    
    inicializar_produtos();
    
    cout << "=== MAQUINA DE CAFE BYTECOFFEE v2.0 ===" << endl;
    cout << "Sistema atualizado com gestao completa" << endl;
    cout << "Bem-vindo!" << endl << endl;
    
    while (true) {
        mostrar_menu();
        
        int opcao;
        cout << "Digite sua opção: ";
        opcao = ler_inteiro("");
        
        if (opcao == 0) {
            cout << "Encerrando maquina de cafe..." << endl;
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
        cout << "NECESSARIO CONFIGURAR PRODUTOS (Modo Gestao -99)" << endl;
    } else {
        for (size_t i = 0; i < produtos.size(); i++) {
            if (produtos[i].esgotado) {
                cout << produtos[i].codigo << " - " << produtos[i].descricao << " - ESGOTADO" << endl;
            } else {
                cout << produtos[i].codigo << " - " << produtos[i].descricao 
                     << " - €" << fixed << setprecision(2) << produtos[i].preco 
                     << " (Stock: " << produtos[i].stock << ")" << endl;
            }
        }
    }
    cout << "0 - Cancelar" << endl;
    cout << "-99 - Modo Gestao" << endl;
    cout << "========================" << endl;
}

void processar_venda(int index) {
    if (produtos[index].esgotado || produtos[index].stock <= 0) {
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
        moeda = ler_decimal("");
        
        if (moeda == 0) {
            cout << "Cancelamento solicitado." << endl;
            if (valor_inserido > 0) {
                cout << "Devolvendo €" << fixed << setprecision(2) << valor_inserido << endl;
            }
            return;
        } else if (moeda < 0) {
            cout << "Valor invalido! Tente novamente." << endl;
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
        
        cout << endl << "=== PAGAMENTO CONCLUIDO ===" << endl;
        cout << "Produto: " << produtos[index].descricao << endl;
        cout << "Valor pago: €" << fixed << setprecision(2) << valor_inserido << endl;
        cout << "Preco: €" << fixed << setprecision(2) << produtos[index].preco << endl;
        cout << "Troco: €" << fixed << setprecision(2) << troco << endl;
        
        // Perguntar sobre talao
        int imprimir;
        cout << "Deseja imprimir talao? (1-Sim, 0-Nao): ";
        imprimir = ler_inteiro("");
        
        if (imprimir == 1) {
            imprimir_talao(produtos[index].codigo, valor_inserido, troco, 1);
        }
        
        cout << "Retire seu produto!" << endl << endl;
    }
}

void imprimir_talao(int codigo, double valor_pago, double troco, int quantidade) {
    // Encontrar produto pelo código
    string descricao_produto = "Produto nao encontrado";
    for (size_t i = 0; i < produtos.size(); i++) {
        if (produtos[i].codigo == codigo) {
            descricao_produto = produtos[i].descricao;
            break;
        }
    }
    
    cout << endl;
    cout << "==============================" << endl;
    cout << "    TALAO DE VENDA" << endl;
    cout << "==============================" << endl;
    cout << "Data: 11/03/2026" << endl;
    cout << "Código: " << codigo << endl;
    cout << "Produto: " << descricao_produto << endl;
    cout << "Quantidade: " << quantidade << endl;
    cout << "Valor pago: €" << fixed << setprecision(2) << valor_pago << endl;
    cout << "Troco: €" << fixed << setprecision(2) << troco << endl;
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
    cout << endl << "=== CONFIGURACAO DE PRODUTOS ===" << endl;
    cout << "Produtos atuais: " << produtos.size() << "/" << MAX_PRODUTOS << endl;
    
    int opcao;
    do {
        cout << endl << "--- MENU CONFIGURACAO ---" << endl;
        cout << "1 - Adicionar produto" << endl;
        cout << "2 - Alterar produto existente" << endl;
        cout << "3 - Listar produtos" << endl;
        cout << "0 - Voltar" << endl;
        cout << "Opção: ";
        opcao = ler_inteiro("");
        
        switch (opcao) {
            case 1: {
                if (produtos.size() >= MAX_PRODUTOS) {
                    cout << "Capacidade maxima de produtos atingida!" << endl;
                    break;
                }
                
                Produto novo;
                cout << "Código do produto: ";
                novo.codigo = ler_inteiro("");
                cout << "Descrição: ";
                cin.ignore();
                getline(cin, novo.descricao);
                cout << "Preço: €";
                novo.preco = ler_decimal("");
                
                // Validar stock
                do {
                    cout << "Stock inicial (máx " << CAPACIDADE_STOCK << "): ";
                    novo.stock = ler_inteiro("");
                    if (novo.stock < 0 || novo.stock > CAPACIDADE_STOCK) {
                        cout << "Stock inválido! Digite um valor entre 0 e " << CAPACIDADE_STOCK << endl;
                    }
                } while (novo.stock < 0 || novo.stock > CAPACIDADE_STOCK);
                
                novo.esgotado = (novo.stock == 0);
                
                produtos.push_back(novo);
                cout << "Produto adicionado com sucesso!" << endl;
                break;
            }
            case 2: {
                int codigo;
                cout << "Digite o código do produto a alterar: ";
                codigo = ler_inteiro("");
                
                int index = -1;
                for (size_t i = 0; i < produtos.size(); i++) {
                    if (produtos[i].codigo == codigo) {
                        index = i;
                        break;
                    }
                }
                
                if (index == -1) {
                    cout << "Produto nao encontrado!" << endl;
                    break;
                }
                
                cout << "Produto atual: " << produtos[index].descricao << endl;
                cout << "1 - Alterar descrição" << endl;
                cout << "2 - Alterar preço" << endl;
                cout << "3 - Alterar stock" << endl;
                cout << "Opção: ";
                int alt = ler_inteiro("");
                
                switch (alt) {
                    case 1:
                        cout << "Nova descrição: ";
                        cin.ignore();
                        getline(cin, produtos[index].descricao);
                        break;
                    case 2:
                        cout << "Novo preço: €";
                        produtos[index].preco = ler_decimal("");
                        break;
                    case 3:
                        do {
                            cout << "Novo stock (max " << CAPACIDADE_STOCK << "): ";
                            produtos[index].stock = ler_inteiro("");
                            if (produtos[index].stock < 0 || produtos[index].stock > CAPACIDADE_STOCK) {
                                cout << "Stock inválido! Digite um valor entre 0 e " << CAPACIDADE_STOCK << endl;
                            }
                        } while (produtos[index].stock < 0 || produtos[index].stock > CAPACIDADE_STOCK);
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
                    cout << "   Preço: €" << fixed << setprecision(2) << produtos[i].preco << endl;
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
    codigo = ler_inteiro("");
    
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
    quantidade = ler_inteiro("");
    
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
    cout << "Total vendido: €" << fixed << setprecision(2) << total_vendido << endl;
    cout << "Total de transações: " << movimentos.size() << endl;
    
    if (!movimentos.empty()) {
        // Criar cópia para ordenação alfabética
        vector<Movimento> movimentos_ordenados = movimentos;
        
        // Ordenar alfabeticamente por descrição
        sort(movimentos_ordenados.begin(), movimentos_ordenados.end(), 
             [](const Movimento& a, const Movimento& b) {
                 return a.descricao < b.descricao;
             });
        
        cout << endl << "--- VENDAS POR PRODUTO (Ordem Alfabética) ---" << endl;
        for (size_t i = 0; i < movimentos_ordenados.size(); i++) {
            cout << movimentos_ordenados[i].descricao << ": " << movimentos_ordenados[i].quantidade_vendida 
                 << " unidades - €" << fixed << setprecision(2) << movimentos_ordenados[i].valor_total << endl;
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
    cout << "Total vendido no período: €" << fixed << setprecision(2) << total_vendido << endl;
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
        opcao = ler_inteiro("");
        
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
