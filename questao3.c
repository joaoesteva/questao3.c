#include <stdio.h>
#include <string.h>

#define MAX_CONTAS 100

typedef struct {
    int numeroConta;
    char nome[100];
    char cpf[15];
    char telefone[15];
    float saldo;
} Conta;

void buscarConta(Conta cadastro[], int numeroConta, int* posicao) {
    for (int i = 0; i < MAX_CONTAS; i++) {
        if (cadastro[i].numeroConta == numeroConta) {
            *posicao = i;
            return;
        }
    }
    *posicao = -2;
}

void cadastrarConta(Conta cadastro[], int* numContas, int numeroConta) {
    int posicao;
    buscarConta(cadastro, numeroConta, &posicao);
    
    if (posicao != -2) {
        printf("Número de conta já cadastrado.\n");
        return;
    }
    
    if (*numContas >= MAX_CONTAS) {
        printf("Limite de contas atingido.\n");
        return;
    }

    Conta novaConta;
    novaConta.numeroConta = numeroConta;
    printf("Digite o nome do titular: ");
    scanf(" %[^\n]s", novaConta.nome);
    printf("Digite o CPF do titular: ");
    scanf(" %s", novaConta.cpf);
    printf("Digite o telefone do titular: ");
    scanf(" %s", novaConta.telefone);
    novaConta.saldo = 0.0;

    cadastro[*numContas] = novaConta;
    (*numContas)++;
    printf("Conta cadastrada com sucesso.\n");
}

void consultarSaldo(Conta cadastro[], int numContas, int numeroConta) {
    int posicao;
    buscarConta(cadastro, numeroConta, &posicao);
    
    if (posicao == -2) {
        printf("Conta não cadastrada.\n");
    } else {
        printf("Saldo da conta %d: %.2f\n", cadastro[posicao].numeroConta, cadastro[posicao].saldo);
    }
}

void deposito(Conta cadastro[], int numContas, int numeroConta) {
    int posicao;
    buscarConta(cadastro, numeroConta, &posicao);
    
    if (posicao == -2) {
        printf("Conta não cadastrada.\n");
        return;
    }
    
    float valor;
    printf("Digite o valor do depósito: ");
    scanf("%f", &valor);
    
    if (valor > 0) {
        cadastro[posicao].saldo += valor;
        printf("Depósito efetuado com sucesso.\n");
    } else {
        printf("Valor inválido para depósito.\n");
    }
}

void saque(Conta cadastro[], int numContas, int numeroConta) {
    int posicao;
    buscarConta(cadastro, numeroConta, &posicao);
    
    if (posicao == -2) {
        printf("Conta não cadastrada.\n");
        return;
    }
    
    float valor;
    printf("Digite o valor do saque: ");
    scanf("%f", &valor);
    
    if (valor <= 0) {
        printf("Valor inválido para saque.\n");
    } else if (cadastro[posicao].saldo >= valor) {
        cadastro[posicao].saldo -= valor;
        printf("Saque efetuado com sucesso.\n");
    } else {
        printf("Saldo insuficiente.\n");
    }
}

void exibirContas(Conta cadastro[], int numContas) {
    if (numContas == 0) {
        printf("Nenhuma conta cadastrada.\n");
        return;
    }

    for (int i = 0; i < numContas; i++) {
        printf("Número da conta: %d\n", cadastro[i].numeroConta);
        printf("Nome: %s\n", cadastro[i].nome);
        printf("Telefone: %s\n", cadastro[i].telefone);
        printf("-------------------------\n");
    }
}

int main() {
    Conta cadastro[MAX_CONTAS];
    int numContas = 0;
    int opcao, numeroConta;

    while (1) {
        printf("Menu:\n");
        printf("1 - Cadastrar conta\n");
        printf("2 - Consultar saldo\n");
        printf("3 - Fazer depósito\n");
        printf("4 - Fazer saque\n");
        printf("5 - Exibir todas as contas\n");
        printf("6 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o número da nova conta: ");
                scanf("%d", &numeroConta);
                cadastrarConta(cadastro, &numContas, numeroConta);
                break;
            case 2:
                printf("Digite o número da conta para consultar o saldo: ");
                scanf("%d", &numeroConta);
                consultarSaldo(cadastro, numContas, numeroConta);
                break;
            case 3:
                printf("Digite o número da conta para fazer o depósito: ");
                scanf("%d", &numeroConta);
                deposito(cadastro, numContas, numeroConta);
                break;
            case 4:
                printf("Digite o número da conta para fazer o saque: ");
                scanf("%d", &numeroConta);
                saque(cadastro, numContas, numeroConta);
                break;
            case 5:
                exibirContas(cadastro, numContas);
                break;
            case 6:
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opção inválida.\n");
        }
    }

    return 0;
}
