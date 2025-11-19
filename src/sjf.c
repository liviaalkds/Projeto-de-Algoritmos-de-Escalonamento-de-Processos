#include <stdio.h>
#include <stdlib.h>

// simula fila de uma lotérica

typedef struct {
    char nome[3]; // usa um padrão tipo: "P1"
    int qtdContas;
    int espera;
} Pessoa;

// simula a execução da fila de lotérica
void executaProcesso(Pessoa p, int *tempo_atual, float *espera_total) {
    int i, contas_pagas = 0;
    
    // armazena o tempo de espera
    p.espera = *tempo_atual;
    *espera_total += p.espera;

    // imprime o inicio do serviço
    printf("\n>>> %s INICIA o pagamento. Tempo de espera: %dms.\n", p.nome, p.espera);
    printf("--- Pressione ENTER para pagar cada uma das %d contas. ---\n", p.qtdContas);

    // faz um loop para pagar uma conta por vez
    for (i = 1; i <= p.qtdContas; i++) {
        
        // a interação com o usuário
        printf("\n[%s - Conta %d/%d] Pressione ENTER para pagar...\n", p.nome, i, p.qtdContas);
        getchar(); // pausa até o usuário pressionar ENTER

        // simula o processamento da conta (aumenta o tempo)
        // adiciona uma simulação de tempo de 1ms por conta
        (*tempo_atual) += 1;
        contas_pagas++;
        
        // barra de progresso
        printf("Progresso: [");
        int j;
        for (j = 0; j < contas_pagas; j++) {
            printf("█"); // progresso
        }
        for (j = contas_pagas; j < p.qtdContas; j++) {
            printf("░"); // restante
        }
        printf("] %d/%d contas pagas.\n", contas_pagas, p.qtdContas);
    }
    
    printf(">>> %s FINALIZA o pagamento. Tempo de conclusão: %dms.\n", p.nome, *tempo_atual);
}


int main() { 
    int qtdPessoas = 0, tempo_atual = 0; 
    float espera_total = 0;
    
    printf("Quantas pessoas estão na fila?\n");

    // verifica se o usuário digitou um válido para a quantidade de pessoas
    scanf("%d", &qtdPessoas);
    if (qtdPessoas < 1) {
        printf("Erro, número de pessoas inválido\n");
        return 1;
    }
    
    // limpa a entrada após o scanf
    while (getchar() != '\n');

    // cria um vetor das pessoas que estão na fila
    Pessoa pessoas[qtdPessoas];

    // cadastro das pessoas que estão na fila
    for (int i = 0; i < qtdPessoas; i++) {

        // concatena o nome de cada pessoa para o padrão, tipo: P1, P2, P3
        sprintf(pessoas[i].nome, "P%d", i + 1);

        // registra o número de contas
        printf("Quantas contas a pessoa %s tem a pagar? ", pessoas[i].nome);

        //verifica se é um número válido
        scanf("%d", &pessoas[i].qtdContas);
        if (pessoas[i].qtdContas < 0) {
            printf("Erro, entrada inválida\n");
            return 1;
        }

        // limpa a entrada
        while (getchar() != '\n');
        
        pessoas[i].espera = 0; // todos começam com 0 de espera
    }
    
    // ordena as pessoas (conforme o sjf)
    for (int i = 0; i < qtdPessoas - 1; i++) {
        for (int j = i + 1; j < qtdPessoas; j++) {

            if (pessoas[i].qtdContas > pessoas[j].qtdContas) {
                Pessoa temp = pessoas[i];
                pessoas[i] = pessoas[j];
                pessoas[j] = temp;
            }
        }
    }

    printf("\n============================================\n");
    printf("Ordem de execução:\n");
    printf("============================================\n");
    
    // execução
    for (int i = 0; i < qtdPessoas; i++) {
        executaProcesso(pessoas[i], &tempo_atual, &espera_total);
    }
    
    // resultado final
    printf("\n============================================\n");
    printf("Todos os processos foram concluídos.\n");
    printf("Tempo total de execução (conclusão): %dms\n", tempo_atual);
    printf("Tempo médio de espera: %.2fms\n", espera_total / qtdPessoas);
    printf("============================================\n");

    return 0;
}