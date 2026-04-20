//Autor: Dinis Monteiro
//Data: 25/03/2026
//Função: Criar uma estrutura para armazenar os dados de uma pessoa (nome, idade e morada) e exibir esses dados na tela.

#include <iostream>
#include <string>

using namespace std;

//estrutura para armazenar os dados da pessoa   
struct Pessoa {
    string nome;
    int idade;
    float morada;
};

int main() {
    Pessoa pessoa1;

    //solicitar os dados da pessoa
    cout << "Digite o nome da pessoa: ";
    getline(cin, pessoa1.nome); //ler o nome da pessoa, incluindo espaços
    cout << "Digite a idade da pessoa: ";
    cin >> pessoa1.idade; //ler a idade da pessoa
    cout << "Digite a morada da pessoa: ";
    cin >> pessoa1.morada; //ler a morada da pessoa

    //exibir os dados da pessoa
    cout << "\nDados da Pessoa:" << endl;
    cout << "Nome: " << pessoa1.nome << endl;
    cout << "Idade: " << pessoa1.idade << endl;
    cout << "Morada: " << pessoa1.morada << endl;

    return 0;
}