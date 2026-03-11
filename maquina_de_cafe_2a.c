//Função: Máquina de Café
//Autores: Afonso Rosa e Dinis Monteiro
//Data: 05/01/2026

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void menu() {
    system("cls");
    puts("\n=========== MAQUINA DE CAFE ===========\n");
    puts("1 - Cafe Expresso            (0.50euros) \n");
    puts("2 - Cafe Duplo               (0.60euros) \n");
    puts("3 - Cappuccino               (0.80euros) \n");
    puts("4 - Chocolate Quente         (1.00euros) \n");
    puts("5 - Cha                      (1.20euros) \n");
    puts("======================================== \n");
}

int escolha() {
int op;
do {
    printf("Selecione uma opcao: ");
    scanf("%d", &op);
    fflush(stdin);

    } while (op <=0 || op > 6);

    return op;
}

float saberpreco(int op) {
float preco = 0;

    switch (op) {
        case 1: preco = 0.50; break;
        case 2: preco = 0.60; break;
        case 3: preco = 0.80; break;
        case 4: preco = 1.00; break;
        case 5: preco = 1.20; break;
    }

    return preco;
}

int escolheracucar() {
int acucar;
        // AÇÚCAR
        printf("Quer acucar? (1-Sim / 0-Nao): ");
        scanf("%d", &acucar);

        if (acucar == 1) {
            printf("Quantos pacotes de acucar quer? (1 ou 2): ");
            scanf("%d", &acucar);

        if (acucar < 1 || acucar > 2) {
                printf("Quantidade invalida. Sera usado 1 pacote.\n");
                acucar = 1;
            }
        } else {
            printf("Sem acucar.\n");
            acucar = 0;
    }
    return acucar;
}

float pagamento(float preco) {
float total = 0;
float moeda;

    while (total < preco) {
        printf("Total inserido: %.2f euros | Insira valor: ", total);
        scanf("%f", &moeda);

        if (fabs(moeda) == 0.10f || fabs(moeda) == 0.20f || fabs(moeda) == 0.50f ||
            fabs(moeda) == 1.00f || fabs(moeda) == 2.00f || fabs(moeda) == 5.00f ||
            fabs(moeda) == 10.00f || fabs(moeda) == 20.00f) {
            total += moeda;
        } else {
            printf("Valor invalido!\n");
        }
    }

    return total;
}

int main() {
int opcao, repetir, acucar;
float preco = 0, moeda, total;

    do {
        menu();
        opcao = escolha();
        preco = saberpreco(opcao);

        printf("\nEscolheu uma bebida que custa %.2f euros.\n", preco);

        acucar = escolheracucar();

        // PAGAMENTO
        total = 0;
        printf("\n--- PAGAMENTO ---\n");
        printf("Aceita moedas: 0.10, 0.20, 0.50, 1.00, 2.00\n");
        printf("Aceita notas: 5.00, 10.00, 20.00\n");

        total = pagamento(preco);

        if (total > preco) {
            printf("Troco: %.2f euros\n", total - preco);
        }

        // PREPARAÇÃO
        printf("\nA preparar a sua bebida");
        for (int i = 0; i < 6; i++) {
            printf(".");
        }
        printf("\nBebida pronta!\n");
        printf("Acucar: %d pacote(s)\n", acucar);

        printf("\nDeseja pedir outra bebida? (1-Sim / 0-Nao): ");
        scanf("%d", &repetir);

    } while (repetir == 1);

    printf("\nObrigado e volte sempre!\n");
    return 0;
}