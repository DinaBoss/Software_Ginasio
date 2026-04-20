//Autor:Dinis Monteiro
//Data:25/03/2026

#include <iostream>
#include <algorithm>
using namespace std;

// Estrutura para armazenar registo de um aluno
struct Aluno {
    int numeroTurma;
    string nome;
    float notas[5]; // Array para armazenar notas de 5 módulos
    int numModulos; // Número de módulos efetivamente preenchidos
    float media; // Média calculada
};

// Função para calcular a média de um aluno
float calcularMedia(const Aluno& aluno) {
    float soma = 0;
    for (int i = 0; i < aluno.numModulos; i++) {
        soma += aluno.notas[i];
    }
    return soma / aluno.numModulos;
}

// Função para ler dados de um aluno
Aluno lerAluno(int indice) {
    Aluno aluno;
    
    cout << "\n=== ALUNO " << indice + 1 << " ===" << endl;
    
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
    while (aluno.numModulos < 1 || aluno.numModulos > 5) {
        cout << "Número de módulos inválido! Deve ser entre 1 e 5: ";
        cin >> aluno.numModulos;
    }
    
    // Ler notas dos módulos
    for (int i = 0; i < aluno.numModulos; i++) {
        cout << "Digite a nota do módulo " << i + 1 << " (0-20): ";
        cin >> aluno.notas[i];
        
        // Validar nota
        while (aluno.notas[i] < 0 || aluno.notas[i] > 20) {
            cout << "Nota inválida! Deve estar entre 0 e 20: ";
            cin >> aluno.notas[i];
        }
    }
    
    // Calcular média
    aluno.media = calcularMedia(aluno);
    
    return aluno;
}

// Função para exibir dados de um aluno
void exibirAluno(const Aluno& aluno) {
    cout << "Turma: " << aluno.numeroTurma << " | ";
    cout << "Nome: " << aluno.nome << " | ";
    cout << "Média: " << aluno.media << endl;
}

// Função para encontrar o aluno com a maior média
int encontrarMaiorMedia(const Aluno alunos[], int numAlunos) {
    int indiceMaior = 0;
    
    for (int i = 1; i < numAlunos; i++) {
        if (alunos[i].media > alunos[indiceMaior].media) {
            indiceMaior = i;
        }
    }
    
    return indiceMaior;
}

// Função para ordenar alunos por média (ordem descendente)
void ordenarPorMedia(Aluno alunos[], int numAlunos) {
    // Usar bubble sort para ordenação
    for (int i = 0; i < numAlunos - 1; i++) {
        for (int j = 0; j < numAlunos - i - 1; j++) {
            if (alunos[j].media < alunos[j + 1].media) {
                // Trocar alunos
                Aluno temp = alunos[j];
                alunos[j] = alunos[j + 1];
                alunos[j + 1] = temp;
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    
    const int MAX_ALUNOS = 50;
    Aluno alunos[MAX_ALUNOS];
    int numAlunos;
    
    cout << "=== GESTÃO DE ALUNOS DO TURNO ===" << endl;
    
    // Ler número de alunos
    cout << "Digite o número total de alunos do turno (máximo " << MAX_ALUNOS << "): ";
    cin >> numAlunos;
    
    // Validar número de alunos
    while (numAlunos < 1 || numAlunos > MAX_ALUNOS) {
        cout << "Número inválido! Deve ser entre 1 e " << MAX_ALUNOS << ": ";
        cin >> numAlunos;
    }
    
    // Ler dados de todos os alunos
    for (int i = 0; i < numAlunos; i++) {
        alunos[i] = lerAluno(i);
    }
    
    // Encontrar e exibir aluno com maior média
    int indiceMaior = encontrarMaiorMedia(alunos, numAlunos);
    
    cout << "\n=== ALUNO COM MAIOR MÉDIA ===" << endl;
    exibirAluno(alunos[indiceMaior]);
    
    // Ordenar alunos por média (ordem descendente)
    ordenarPorMedia(alunos, numAlunos);
    
    // Exibir todos os alunos ordenados
    cout << "\n=== ALUNOS ORDENADOS POR MÉDIA (DESCENDENTE) ===" << endl;
    for (int i = 0; i < numAlunos; i++) {
        cout << i + 1 << ". ";
        exibirAluno(alunos[i]);
    }
    
    return 0;
}