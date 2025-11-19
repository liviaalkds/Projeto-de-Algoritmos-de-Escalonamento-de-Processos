#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int tempo_burst;
    int prioridade;
    int tempo_espera;
    int tempo_retorno;
} Processo;

int comparar_prioridade(const void *a, const void *b) {
    Processo *p1 = (Processo *)a;
    Processo *p2 = (Processo *)b;

    if (p1->prioridade != p2->prioridade)
        return p1->prioridade - p2->prioridade;

    return p1->id - p2->id;
}

void priority_scheduling(Processo processos[], int n) {
    printf("============================================================\n");
    printf("ESCALONAMENTO POR PRIORIDADE (Priority Scheduling)\n");
    printf("============================================================\n");

    printf("\nProcessos recebidos:\n");
    printf("%-8s %-10s %-12s\n", "ID", "Burst", "Prioridade");
    printf("-----------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%-7d %-10d %-12d\n",
               processos[i].id,
               processos[i].tempo_burst,
               processos[i].prioridade);
    }

    qsort(processos, n, sizeof(Processo), comparar_prioridade);

    printf("\n============================================================\n");
    printf("ORDEM DE EXECUCAO (por prioridade):\n");
    printf("============================================================\n");

    int tempo_atual = 0;

    for (int i = 0; i < n; i++) {
        processos[i].tempo_espera = tempo_atual;
        tempo_atual += processos[i].tempo_burst;
        processos[i].tempo_retorno = tempo_atual;

        printf("\n[Tempo %3d-%3d] Executando P%d\n",
               processos[i].tempo_espera,
               processos[i].tempo_retorno,
               processos[i].id);

        printf("   - Prioridade: %d\n", processos[i].prioridade);
        printf("   - Burst Time: %d\n", processos[i].tempo_burst);
        printf("   - Tempo de Espera: %d\n", processos[i].tempo_espera);
    }

    float tempo_espera_medio = 0;
    float tempo_retorno_medio = 0;

    for (int i = 0; i < n; i++) {
        tempo_espera_medio += processos[i].tempo_espera;
        tempo_retorno_medio += processos[i].tempo_retorno;
    }

    tempo_espera_medio /= n;
    tempo_retorno_medio /= n;

    printf("RESULTADOS FINAIS:\n");
    printf("============================================================\n");
    printf("\n%-8s %-10s %-10s %-10s %-10s\n",
           "ID", "Burst", "Prior.", "Espera", "Retorno");
    printf("----------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("P%-7d %-10d %-10d %-10d %-10d\n",
               processos[i].id,
               processos[i].tempo_burst,
               processos[i].prioridade,
               processos[i].tempo_espera,
               processos[i].tempo_retorno);
    }

    printf("\n============================================================\n");
    printf("Tempo Medio de Espera: %.2f\n", tempo_espera_medio);
    printf("Tempo Medio de Retorno: %.2f\n", tempo_retorno_medio);
    printf("============================================================\n");
}

int main() {
    int n;

    printf("Quantos processos deseja inserir? ");
    scanf("%d", &n);

    Processo *processos = malloc(n * sizeof(Processo));

    printf("\n=== Insercao dos Processos ===\n");
    for (int i = 0; i < n; i++) {
        printf("\nProcesso %d:\n", i + 1);

        printf("ID: ");
        scanf("%d", &processos[i].id);

        printf("Burst Time: ");
        scanf("%d", &processos[i].tempo_burst);

        printf("Prioridade: ");
        scanf("%d", &processos[i].prioridade);

        processos[i].tempo_espera = 0;
        processos[i].tempo_retorno = 0;
    }

    printf("\n\n=== INICIANDO ESCALONAMENTO ===\n\n");
    priority_scheduling(processos, n);

    free(processos);

    return 0;
}
