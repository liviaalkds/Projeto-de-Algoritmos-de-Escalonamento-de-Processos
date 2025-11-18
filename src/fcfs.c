#include <stdio.h>

int main() {
    int n;
    printf("Quantos processos vão ser executados?\n");
    scanf("%d", &n);
    int chegada[n], duracao[n], inicio[n], fim[n], espera[n], retorno[n], processo[n], tempo_atual = 0, aux;

    for (int i = 0; i < n; i++) {
        processo[i] = i + 1;
        printf("\nProcesso P%d:\n", i + 1);
        printf("Qual o tempo de chegada do processo?\n");
        scanf("%d", &chegada[i]);
        printf("Qual a Duração (burst time) do processo?\n");
        scanf("%d", &duracao[i]);
    }

    //ordenando pelo tempo de chegada
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (chegada[j] < chegada[i]) {
                aux = chegada[i];
                chegada[i] = chegada[j];
                chegada[j] = aux;
                aux = duracao[i];
                duracao[i] = duracao[j];
                duracao[j] = aux;
                aux = processo[i];
                processo[i] = processo[j];
                processo[j] = aux;
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (tempo_atual < chegada[i]) {  
            tempo_atual = chegada[i];
        }
        inicio[i] = tempo_atual;                    
        fim[i] = inicio[i] + duracao[i];            
        espera[i] = inicio[i] - chegada[i];         
        retorno[i] = fim[i] - chegada[i];           
        tempo_atual = fim[i];                      
    }

    printf("\n====================================================================================================\n");
    printf("Processo | Chegada | Duração(Burst Time) | Inicio | Fim | Tempo de Espera | Tempo de Retorno\n");
    printf("====================================================================================================\n");
    for (int i = 0; i < n; i++) {
        printf("P%-7d | %-7d | %-19d | %-6d | %-3d | %-15d | %-16d\n", processo[i], chegada[i], duracao[i], inicio[i], fim[i], espera[i], retorno[i]);
    }
    printf("====================================================================================================\n");
    
    return 0;
}
