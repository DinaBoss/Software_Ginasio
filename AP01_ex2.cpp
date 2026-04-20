//Autor: Dinis Monteiro
//Data: 25/03/2026


#include <iostream>
#include <string>
using namespace std;

// Estrutura para armazenar registo de um aluno
struct Aluno {
    int numeroTurma;
    string nome;
    float notas[5]; // Array para armazenar notas de 5 módulos
    int numModulos; // Número de módulos efetivamente preenchidos
};

// Função para exibir dados do aluno
void exibirAluno(const Aluno& aluno) {
    cout << "\n=== REGISTO DO ALUNO ===" << endl;
    cout << "Número da Turma: " << aluno.numeroTurma << endl;
    cout << "Nome: " << aluno.nome << endl;
    cout << "Notas dos módulos (PSI): ";
    
    for (int i = 0; i < aluno.numModulos; i++) {
        cout << aluno.notas[i];
        if (i < aluno.numModulos - 1) {
            cout << ", ";
        }
    }
    cout << endl;
    
    // Calcular média
    float soma = 0;
    for (int i = 0; i < aluno.numModulos; i++) {
        soma += aluno.notas[i];
    }
    float media = soma / aluno.numModulos;
    cout << "Média: " << media << endl;
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    
    Aluno aluno;
    
    cout << "=== REGISTO DE ALUNO - PSI ===" << endl;
    
    // Ler número da turma
    cout << "Digite o número da turma: ";
    cin >> aluno.numeroTurma;
    cin.ignore(); // Limpar buffer
    
    // Ler nome
    cout << "Digite o nome do aluno: ";
    getline(cin, aluno.nome);
    
    // Ler número de módulos
    cout << "Quantos módulos de PSI deseja registar (máximo 5): ";
    cin >> aluno.numModulos;
    
    // Validar número de módulos
    if (aluno.numModulos < 1 || aluno.numModulos > 5) {
        cout << "Número de módulos inválido! Deve ser entre 1 e 5." << endl;
        return 1;
    }
    
    // Ler notas dos módulos
    for (int i = 0; i < aluno.numModulos; i++) {
        cout << "Digite a nota do módulo " << i + 1 << " (0-20): ";
        cin >> aluno.notas[i];
        
        // Validar nota
        if (aluno.notas[i] < 0 || aluno.notas[i] > 20) {
            cout << "Nota inválida! Deve estar entre 0 e 20." << endl;
            i--; // Repetir a leitura deste módulo
        }
    }
    
    // Exibir dados do aluno
    exibirAluno(aluno);
    
    return 0;
}