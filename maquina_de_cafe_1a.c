//Função: Máquina de Café
//Autores: Afonso Rosa e Dinis Monteiro
//Data: 25/11/2025
//Turma: 10ºF
//Números: 1 e 2

#include <stdio.h>
#include <math.h>

int main() {
    int opcao, repetir, acucar;
    float preco = 0, moeda, total;

    do {

        // MENU DE PRODUTOS
        printf("\n=========== MAQUINA DE CAFE ===========\n");
        printf("1 - Cafe Expresso       (0.50euros)\n");
        printf("2 - Cafe Duplo          (0.60euros)\n");
        printf("3 - Cappuccino          (0.80euros)\n");
        printf("4 - Chocolate Quente    (1.00euros)\n");
        printf("5 - Cha                 (1.20euros)\n");
        printf("=======================================\n");
        printf("Selecione uma opcao: ");
        scanf("%d", &opcao);

        // DEFINIR PREÇO
        switch (opcao) {
            case 1: preco = 0.50; break;
            case 2: preco = 0.60; break;
            case 3: preco = 0.80; break;
            case 4: preco = 1.00; break;
            case 5: preco = 1.20; break;
            default:
                printf("\nOpcao invalida!\n");
                continue;  // volta ao menu
        }

        printf("\nEscolheu uma bebida que custa %.2feuros.\n", preco);

        // NÍVEL DE AÇÚCAR
        printf("\nQuer acucar? (1-Sim/0-Nao): ");
        scanf("%d", &acucar);

        if (acucar == 1) {
        printf("\nQuantos pacotes de acucar quer? (1/2): ");
        scanf("%d", &acucar);

        if (acucar < 0 || acucar > 2) {
        printf("Quantidade invalida. Sera usado 1 pacote.\n");
        acucar = 1;
        }
    } else {
        acucar = 0;
    }

        // PAGAMENTO
        total = 0;
        printf("\n--- PAGAMENTO ---\n");
        printf("Aceita moedas: 0.10, 0.20, 0.50, 1.00, 2.00\n");
        printf("Aceita notas: 5, 10 e 20 euros\n");

        while (total < preco) {
            printf("Total inserido: %.2f€ - Insira moeda/nota: ", total);
            scanf("%f", &moeda);
            printf("\n\%f\n", moeda);

           // validar moeda/nota
            if (fabs(moeda) == 0.10f || fabs(moeda) == 0.20f || fabs(moeda) == 0.50f ||
                fabs(moeda) == 1.00f || fabs(moeda) == 2.00f || fabs(moeda) == 5.00f || fabs(moeda) == 10.00f || fabs(moeda) == 20.00f) {
                total += moeda;
            } else {
                printf("Valor invalido! Tente novamente.\n");
            }
        }

        // TROCO
        if (total > preco) {
            printf("Troco: %.2feuros\n", total - preco);
        }

        // PREPARAÇÃO DA BEBIDA
        printf("\nA preparar a sua bebida...\n");
        for (int i = 0; i < 8; i++) {
            printf(".");
        }
        printf("\nBebida pronta! \n");
        printf("Acucar: %d pacote(es).\n", acucar);

        // REPETIR?
        printf("\nDeseja pedir outra bebida? (1-Sim / 0-Nao): ");
        scanf("%d", &repetir);

    } while (repetir == 1);

    printf("\nObrigado e volte sempre! \n");


    return 0;
}