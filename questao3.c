#include <stdio.h>
#include <string.h>

#define MAX_CONTAS 100

typedef struct {
    int numero;
    char nome[50];
    char cpf[15];
    char telefone[15];
    float saldo;
} Conta;

int procurar_conta(Conta contas[MAX_CONTAS], int numero, int total_contas) {
    if (total_contas == 0) return -1;
    for (int i = 0; i < total_contas; i++) {
        if (contas[i].numero == numero) return i;
    }
    return -2;
}

void adicionar_conta(Conta contas[MAX_CONTAS], int *total_contas, int numero) {
    if (procurar_conta(contas, numero, *total_contas) != -2) {
        printf("Número de conta já cadastrado.\n");
        return;
    }

    if (*total_contas < MAX_CONTAS) {
        Conta nova;
        nova.numero = numero;
        
        printf("Nome do titular: ");
        getchar();
        fgets(nova.nome, sizeof(nova.nome), stdin);
        nova.nome[strcspn(nova.nome, "\n")] = 0;

        printf("CPF do titular: ");
        fgets(nova.cpf, sizeof(nova.cpf), stdin);
        nova.cpf[strcspn(nova.cpf, "\n")] = 0;

        printf("Telefone do titular: ");
        fgets(nova.telefone, sizeof(nova.telefone), stdin);
        nova.telefone[strcspn(nova.telefone, "\n")] = 0;

        nova.saldo = 0.0f;

        contas[*total_contas] = nova;
        (*total_contas)++;
        printf("Conta cadastrada com sucesso!\n");
    } else {
        printf("Não é possível adicionar mais contas.\n");
    }
}

void exibir_saldo(Conta contas[MAX_CONTAS], int total_contas, int numero) {
    int idx = procurar_conta(contas, numero, total_contas);
    if (idx >= 0) {
        printf("Saldo da conta %d: R$ %.2f\n", numero, contas[idx].saldo);
    } else {
        printf("Conta não encontrada.\n");
    }
}

void realizar_deposito(Conta contas[MAX_CONTAS], int total_contas, int numero) {
    int idx = procurar_conta(contas, numero, total_contas);
    if (idx >= 0) {
        float valor;
        printf("Digite o valor do depósito: ");
        scanf("%f", &valor);
        contas[idx].saldo += valor;
        printf("Depósito realizado.\n");
    } else {
        printf("Conta não localizada.\n");
    }
}

void realizar_saque(Conta contas[MAX_CONTAS], int total_contas, int numero) {
    int idx = procurar_conta(contas, numero, total_contas);
    if (idx >= 0) {
        float valor;
        printf("Digite o valor do saque: ");
        scanf("%f", &valor);
        if (contas[idx].saldo >= valor) {
            contas[idx].saldo -= valor;
            printf("Saque realizado.\n");
        } else {
            printf("Saldo insuficiente.\n");
        }
    } else {
        printf("Conta não encontrada.\n");
    }
}

void listar_contas(Conta contas[MAX_CONTAS], int total_contas) {
    if (total_contas == 0) {
        printf("Nenhuma conta cadastrada.\n");
        return;
    }
    for (int i = 0; i < total_contas; i++) {
        printf("Conta %d - Titular: %s, Telefone: %s\n", contas[i].numero, contas[i].nome, contas[i].telefone);
    }
}

int main() {
    Conta contas[MAX_CONTAS];
    int total_contas = 0;
    int opcao, numero_conta;

    while (1) {
        printf("\nBanco Dinheiro Certo\n");
        printf("1. Cadastrar nova conta\n");
        printf("2. Consultar saldo\n");
        printf("3. Realizar depósito\n");
        printf("4. Realizar saque\n");
        printf("5. Listar todas as contas\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o número da nova conta: ");
                scanf("%d", &numero_conta);
                adicionar_conta(contas, &total_contas, numero_conta);
                break;
            case 2:
                printf("Digite o número da conta para consultar saldo: ");
                scanf("%d", &numero_conta);
                exibir_saldo(contas, total_contas, numero_conta);
                break;
            case 3:
                printf("Digite o número da conta para depósito: ");
                scanf("%d", &numero_conta);
                realizar_deposito(contas, total_contas, numero_conta);
                break;
            case 4:
                printf("Digite o número da conta para saque: ");
                scanf("%d", &numero_conta);
                realizar_saque(contas, total_contas, numero_conta);
                break;
            case 5:
                listar_contas(contas, total_contas);
                break;
            case 6:
                printf("Saindo do programa...\n");
                return 0;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}
