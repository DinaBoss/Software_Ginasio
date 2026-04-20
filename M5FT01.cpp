// Autor: Afonso Rosa e Dinis Monteiro
// Data: 13/04/2026
// Função: Sistema de gestão de sócios de um ginásio. Permite adicionar, listar, consultar, alterar e eliminar sócios, com validação de dados e menu interativo.

#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <ctime>
#include <locale>
#include <windows.h>
using namespace std;

// CONSTANTES

const int MAX_SOCIOS    = 100;
const int LARGURA_TABELA = 118;


// STRUCTS

// Representa a data de nascimento (ou inscrição) de um sócio
struct Data {
    int dia;
    int mes;
    int ano;
};

// Representa um sócio do ginásio
struct Socio {
    int    numero;          // Identificador único, gerado automaticamente
    string nome;
    string email;
    string telefone;
    string plano;           // "Mensal", "Trimestral" ou "Anal"
    Data   dataNascimento;
    Data   dataInscricao;
    bool   ativo;           // true = sócio ativo, false = eliminado (slot vazio)
};


// VARIÁVEIS GLOBAIS

Socio socios[MAX_SOCIOS];
int   totalSocios    = 0;   // Número de slots ocupados (incluindo inativos)
int   proximoNumero  = 1;   // Contador para gerar IDs únicos


// UTILITÁRIOS DE DATAS


bool ehBissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int diasNoMes(int mes, int ano) {
    switch (mes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return ehBissexto(ano) ? 29 : 28;
        default: return 0;
    }
}

bool validarData(const Data& d) {
    if (d.ano < 1900 || d.ano > 2100) return false;
    if (d.mes  < 1   || d.mes  > 12)  return false;
    if (d.dia  < 1   || d.dia  > diasNoMes(d.mes, d.ano)) return false;
    return true;
}

// Devolve a data atual do sistema
Data dataAtual() {
    time_t t = time(nullptr);
    tm*    local = localtime(&t);
    Data d;
    d.dia = local->tm_mday;
    d.mes = local->tm_mon + 1;
    d.ano = local->tm_year + 1900;
    return d;
}

// Formata uma Data como "dd/mm/aaaa"
string formatarData(const Data& d) {
    char buf[11];
    snprintf(buf, sizeof(buf), "%02d/%02d/%04d", d.dia, d.mes, d.ano);
    return string(buf);
}


// UTILITÁRIOS DE INTERFACE


// Imprime uma linha horizontal com o carácter dado
void linhaH(char c = '-', int largura = LARGURA_TABELA) {
    cout << string(largura, c) << "\n";
}

// Limpa o buffer de input após leituras com cin
void limparBuffer() {
    cin.ignore(10000, '\n');
}

// Lê uma string não vazia
string lerString(const string& prompt) {
    string valor;
    do {
        cout << prompt;
        getline(cin, valor);
        if (valor.empty())
            cout << "  [!] Campo obrigatório. Tente novamente.\n";
    } while (valor.empty());
    return valor;
}

// Lê um inteiro dentro de [min, max]
int lerInteiro(const string& prompt, int min, int max) {
    int valor;
    bool ok;
    do {
        cout << prompt;
        ok = (bool)(cin >> valor);
        limparBuffer();
        if (!ok || valor < min || valor > max) {
            cout << "  [!] Valor inválido. Introduza um número entre "
                 << min << " e " << max << ".\n";
            cin.clear();
        } else {
            break;
        }
    } while (true);
    return valor;
}

// Lê e valida uma data
Data lerData(const string& titulo) {
    Data d;
    bool valida = false;
    cout << titulo << "\n";
    do {
        d.dia = lerInteiro("    Dia  : ", 1, 31);
        d.mes = lerInteiro("    Mês  : ", 1, 12);
        d.ano = lerInteiro("    Ano  : ", 1900, 2100);
        if (validarData(d)) {
            valida = true;
        } else {
            cout << "  [!] Data inválida. Verifique o dia/mês/ano e tente novamente.\n";
        }
    } while (!valida);
    return d;
}

// Valida formato simples de e-mail (contém '@' e '.')
bool validarEmail(const string& email) {
    size_t at  = email.find('@');
    size_t dot = email.rfind('.');
    return (at != string::npos && dot != string::npos && dot > at + 1);
}

// Valida telefone: 9 dígitos numéricos
bool validarTelefone(const string& tel) {
    if (tel.size() != 9) return false;
    for (char c : tel)
        if (!isdigit(c)) return false;
    return true;
}

// Valida plano de subscrição
bool validarPlano(const string& plano) {
    return (plano == "Mensal" || plano == "Trimestral" || plano == "Anual");
}


// LÓGICA DE NEGÓCIO


// Devolve o índice no array de um sócio ativo pelo número; -1 se não encontrado
int encontrarPorNumero(int numero) {
    for (int i = 0; i < totalSocios; i++)
        if (socios[i].ativo && socios[i].numero == numero)
            return i;
    return -1;
}

// Devolve o índice do primeiro sócio ativo cujo nome contenha a substring; -1 se não encontrado
int encontrarPorNome(const string& nome) {
    for (int i = 0; i < totalSocios; i++) {
        if (!socios[i].ativo) continue;
        // Comparação case-insensitive simples
        string nomeSocio = socios[i].nome;
        string nomeBusca = nome;
        for (char& c : nomeSocio) c = tolower(c);
        for (char& c : nomeBusca)  c = tolower(c);
        if (nomeSocio.find(nomeBusca) != string::npos)
            return i;
    }
    return -1;
}

// Conta o número de sócios ativos
int contarAtivos() {
    int total = 0;
    for (int i = 0; i < totalSocios; i++)
        if (socios[i].ativo) total++;
    return total;
}


// CABEÇALHO DA TABELA DE SÓCIOS

void imprimirCabecalhoTabela() {
    linhaH('=');
    cout << left
         << setw(6)  << "Nº"
         << setw(28) << "Nome"
         << setw(26) << "E-mail"
         << setw(13) << "Telefone"
         << setw(13) << "Plano"
         << setw(14) << "Nascimento"
         << setw(12) << "Inscrição"
         << "\n";
    linhaH('-');
}

void imprimirLinhaSocio(const Socio& s) {
    cout << left
         << setw(6)  << s.numero
         << setw(28) << s.nome.substr(0, 27)
         << setw(26) << s.email.substr(0, 25)
         << setw(13) << s.telefone
         << setw(13) << s.plano
         << setw(14) << formatarData(s.dataNascimento)
         << setw(12) << formatarData(s.dataInscricao)
         << "\n";
}


// OPERAÇÕES DO MENU


// 1 — Adicionar sócio
void adicionarSocio() {
    linhaH('=');
    cout << "  ADICIONAR NOVO SÓCIO\n";
    linhaH('=');

    if (contarAtivos() >= MAX_SOCIOS) {
        cout << "  [!] Capacidade máxima de sócios atingida (" << MAX_SOCIOS << ").\n";
        return;
    }

    Socio novo;
    novo.ativo   = true;
    novo.numero  = proximoNumero++;

    // Nome
    cout << "\n";
    novo.nome = lerString("  Nome completo : ");

    // E-mail com validação
    do {
        cout << "  E-mail         : ";
        getline(cin, novo.email);
        if (!validarEmail(novo.email))
            cout << "  [!] E-mail inválido. Ex: exemplo@dominio.com\n";
    } while (!validarEmail(novo.email));

    // Telefone com validação
    do {
        cout << "  Telefone (9 dígitos): ";
        getline(cin, novo.telefone);
        if (!validarTelefone(novo.telefone))
            cout << "  [!] Telefone deve ter exatamente 9 dígitos numéricos.\n";
    } while (!validarTelefone(novo.telefone));

    // Plano
    do {
        cout << "  Plano (Mensal / Trimestral / Anual): ";
        getline(cin, novo.plano);
        if (!validarPlano(novo.plano))
            cout << "  [!] Plano inválido. Escolha: Mensal, Trimestral ou Anual.\n";
    } while (!validarPlano(novo.plano));

    // Data de nascimento
    cout << "\n";
    novo.dataNascimento = lerData("  Data de nascimento:");

    // Data de inscrição = hoje
    novo.dataInscricao = dataAtual();

    // Guardar
    socios[totalSocios++] = novo;

    cout << "\n  [OK] Sócio nº " << novo.numero << " registado com sucesso!\n";
    cout << "       Data de inscrição: " << formatarData(novo.dataInscricao) << "\n";
}

// 2 — Listar todos os sócios
void listarSocios() {
    linhaH('=');
    cout << "  LISTA DE SÓCIOS\n";
    linhaH('=');

    int ativos = contarAtivos();
    if (ativos == 0) {
        cout << "  Não existem sócios registados.\n";
        return;
    }

    imprimirCabecalhoTabela();
    for (int i = 0; i < totalSocios; i++)
        if (socios[i].ativo)
            imprimirLinhaSocio(socios[i]);

    linhaH('=');
    cout << "  Total de sócios: " << ativos << "\n";
}

// 3 — Consultar sócio
void consultarSocio() {
    linhaH('=');
    cout << "  CONSULTAR SÓCIO\n";
    linhaH('=');
    cout << "  1. Por número de sócio\n";
    cout << "  2. Por nome\n";
    int opcao = lerInteiro("\n  Opção: ", 1, 2);

    int idx = -1;
    if (opcao == 1) {
        int num = lerInteiro("  Número do sócio: ", 1, 99999);
        idx = encontrarPorNumero(num);
    } else {
        limparBuffer();
        string nome = lerString("  Nome (ou parte do nome): ");
        idx = encontrarPorNome(nome);
    }

    if (idx == -1) {
        cout << "\n  [!] Sócio não encontrado.\n";
        return;
    }

    const Socio& s = socios[idx];
    cout << "\n";
    linhaH('-');
    cout << "  Número       : " << s.numero                    << "\n";
    cout << "  Nome         : " << s.nome                      << "\n";
    cout << "  E-mail       : " << s.email                     << "\n";
    cout << "  Telefone     : " << s.telefone                  << "\n";
    cout << "  Plano        : " << s.plano                     << "\n";
    cout << "  Nascimento   : " << formatarData(s.dataNascimento) << "\n";
    cout << "  Inscrição    : " << formatarData(s.dataInscricao)  << "\n";
    linhaH('-');
}

// 4 — Alterar dados de um sócio
void alterarSocio() {
    linhaH('=');
    cout << "  ALTERAR SÓCIO\n";
    linhaH('=');

    int num = lerInteiro("  Número do sócio: ", 1, 99999);
    int idx = encontrarPorNumero(num);

    if (idx == -1) {
        cout << "\n  [!] Sócio não encontrado.\n";
        return;
    }

    Socio& s = socios[idx];
    cout << "\n  A alterar: " << s.nome << " (nº " << s.numero << ")\n\n";
    cout << "  O que pretende alterar?\n";
    cout << "  1. Nome\n";
    cout << "  2. E-mail\n";
    cout << "  3. Telefone\n";
    cout << "  4. Plano\n";
    cout << "  5. Data de nascimento\n";
    cout << "  0. Cancelar\n";

    int opcao = lerInteiro("\n  Opção: ", 0, 5);
    limparBuffer();

    switch (opcao) {
        case 1:
            s.nome = lerString("  Novo nome: ");
            break;
        case 2:
            do {
                cout << "  Novo e-mail: ";
                getline(cin, s.email);
                if (!validarEmail(s.email))
                    cout << "  [!] E-mail inválido.\n";
            } while (!validarEmail(s.email));
            break;
        case 3:
            do {
                cout << "  Novo telefone (9 dígitos): ";
                getline(cin, s.telefone);
                if (!validarTelefone(s.telefone))
                    cout << "  [!] Telefone inválido.\n";
            } while (!validarTelefone(s.telefone));
            break;
        case 4:
            do {
                cout << "  Novo plano (Mensal / Trimestral / Anual): ";
                getline(cin, s.plano);
                if (!validarPlano(s.plano))
                    cout << "  [!] Plano inválido.\n";
            } while (!validarPlano(s.plano));
            break;
        case 5:
            s.dataNascimento = lerData("  Nova data de nascimento:");
            break;
        case 0:
            cout << "  Alteração cancelada.\n";
            return;
    }

    cout << "\n  [OK] Dados atualizados com sucesso!\n";
}

// 5 — Eliminar sócio (com confirmação)
void eliminarSocio() {
    linhaH('=');
    cout << "  ELIMINAR SÓCIO\n";
    linhaH('=');

    int num = lerInteiro("  Número do sócio: ", 1, 99999);
    int idx = encontrarPorNumero(num);

    if (idx == -1) {
        cout << "\n  [!] Sócio não encontrado.\n";
        return;
    }

    const Socio& s = socios[idx];
    cout << "\n  Sócio a eliminar:\n";
    imprimirCabecalhoTabela();
    imprimirLinhaSocio(s);
    linhaH('-');

    cout << "\n  Tem a certeza que pretende eliminar este sócio? (s/n): ";
    char confirm;
    cin >> confirm;
    limparBuffer();

    if (tolower(confirm) == 's') {
        socios[idx].ativo = false;
        cout << "\n  [OK] Sócio nº " << num << " eliminado com sucesso.\n";
    } else {
        cout << "\n  Operação cancelada.\n";
    }
}


// MENU PRINCIPAL


void imprimirMenu() {
    cout << "\n";
    linhaH('=');
    cout << setw(65) << "GYM MANAGER — SISTEMA DE GESTÃO DE SÓCIOS\n";
    linhaH('=');
    cout << "  Sócios ativos: " << contarAtivos() << " / " << MAX_SOCIOS << "\n";
    linhaH('-');
    cout << "  [1]  Adicionar sócio\n";
    cout << "  [2]  Listar todos os sócios\n";
    cout << "  [3]  Consultar sócio\n";
    cout << "  [4]  Alterar sócio\n";
    cout << "  [5]  Eliminar sócio\n";
    cout << "  [0]  Sair\n";
    linhaH('=');
}


// MAIN

int main() {
    // Set console to UTF-8 for both input and output
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    
    // Set locale to support Portuguese characters
    setlocale(LC_ALL, "pt_PT.UTF-8");
    
    // Enable virtual terminal processing for better character support
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    int opcao;
    do {
        imprimirMenu();
        opcao = lerInteiro("  Opção: ", 0, 5);
        cout << "\n";

        switch (opcao) {
            case 1: adicionarSocio();  break;
            case 2: listarSocios();    break;
            case 3: consultarSocio();  break;
            case 4: alterarSocio();    break;
            case 5: eliminarSocio();   break;
            case 0:
                linhaH('=');
                cout << "  Até breve!\n";
                linhaH('=');
                break;
        }

        if (opcao != 0) {
            cout << "\n  Prima ENTER para continuar...";
            cin.ignore(10000, '\n');
        }

    } while (opcao != 0);

    return 0;
}