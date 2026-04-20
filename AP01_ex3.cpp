//Autor:Dinis Monteiro
//Data:25/03/2026

#include <iostream>
using namespace std;

// Estrutura para armazenar uma data
struct Data {
    int dia;
    int mes;
    int ano;
};

// Função para verificar se um ano é bissexto
bool ehBissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

// Função para obter o número de dias de um mês
int diasNoMes(int mes, int ano) {
    switch (mes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return ehBissexto(ano) ? 29 : 28;
        default:
            return 0;
    }
}

// Função para validar uma data
bool validarData(const Data& data) {
    if (data.ano < 1) return false;
    if (data.mes < 1 || data.mes > 12) return false;
    if (data.dia < 1 || data.dia > diasNoMes(data.mes, data.ano)) return false;
    return true;
}

// Função para ler uma data com validação
Data lerData(const string& mensagem) {
    Data data;
    bool valida = false;
    
    do {
        cout << mensagem << endl;
        cout << "Dia: ";
        cin >> data.dia;
        cout << "Mês: ";
        cin >> data.mes;
        cout << "Ano: ";
        cin >> data.ano;
        
        if (validarData(data)) {
            valida = true;
        } else {
            cout << "Data inválida! Por favor, insira novamente." << endl;
        }
    } while (!valida);
    
    return data;
}

// Função para converter uma data em número de dias desde 01/01/0001
long dataParaDias(const Data& data) {
    long totalDias = 0;
    
    // Adicionar dias dos anos completos
    for (int ano = 1; ano < data.ano; ano++) {
        totalDias += ehBissexto(ano) ? 366 : 365;
    }
    
    // Adicionar dias dos meses completos do ano atual
    for (int mes = 1; mes < data.mes; mes++) {
        totalDias += diasNoMes(mes, data.ano);
    }
    
    // Adicionar dias do mês atual
    totalDias += data.dia;
    
    return totalDias;
}

// Função para calcular diferença em dias entre duas datas
long diferencaDias(const Data& data1, const Data& data2) {
    long dias1 = dataParaDias(data1);
    long dias2 = dataParaDias(data2);
    
    return abs(dias2 - dias1);
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    
    cout << "=== CÁLCULO DE DIFERENÇA ENTRE DATAS ===" << endl;
    
    // Ler primeira data
    Data data1 = lerData("Insira a primeira data:");
    
    // Ler segunda data
    Data data2 = lerData("\nInsira a segunda data:");
    
    // Calcular e exibir diferença
    long diferenca = diferencaDias(data1, data2);
    
    cout << "\n=== RESULTADO ===" << endl;
    cout << "Data 1: " << data1.dia << "/" << data1.mes << "/" << data1.ano << endl;
    cout << "Data 2: " << data2.dia << "/" << data2.mes << "/" << data2.ano << endl;
    cout << "Número de dias entre as duas datas: " << diferenca << " dias" << endl;
    
    return 0;
}