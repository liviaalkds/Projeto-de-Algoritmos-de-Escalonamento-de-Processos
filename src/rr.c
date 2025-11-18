#include <stdlib.h>
#include <stdio.h>
#define tam 30 //numero máximo de pessoas

int pessoas[tam];           //Fila de pessoas
int NumEscolhidodepessoas;  //Numero de pessoas na fila
int quantum;                //Numero de contas pra pagar no caixa

// Função para exibir a linha do tempo de execução ( gráfico Gantt)
void mostrarGrafico(int pessoa, int pago, int restante, int rodada) {
    int i;

    printf("\n====================================================");
    printf("\n        VISUALIZAÇÃO GRÁFICA DO ROUND ROBIN        ");
    printf("\n====================================================\n");

    printf("\nRodada %d:", rodada);
    printf("\nPessoa P%d foi atendida", pessoa);
    printf("\nPagou ........: %d contas", pago);
    printf("\nRestaram .....: %d contas", restante);

    printf("\n\n--- Linha do tempo (P%d) ---\n", pessoa);

    printf("[");
    for(i = 0; i < pago; i++) printf("█");   //pago neste quantum
    for(i = 0; i < restante; i++) printf("░"); //restante
    printf("]");

    printf("\nLegenda: █ = pago   ░ = faltando\n");
    printf("====================================================\n\n");
}

void contas(){              //Para que o usuario possa testar com diferentes quantidades de contas
    int numero;
    int i;

    for (i=1; i<=NumEscolhidodepessoas; i++){
        printf("\nDigite o numero de contas a pagar da pessoa %d: ", i);
        scanf("%d", &numero);            //Leitura de valor inserido pelo usuario
        pessoas[i]= numero;              //cada pessoa recebe o valor informado
    }
}

void fila(){
    int contadorFila=NumEscolhidodepessoas;   //contagem de pessoas que estão na fila
    int frenteFila = 1;          //Primeira posição da fila
    int rodada = 1;        //contador de rodada      

    while(contadorFila !=0){
        while(pessoas[frenteFila] <= 0 && contadorFila > 0){      //Tira pessoas que não tem contas da primeira posição
            frenteFila++;       
            if(frenteFila > NumEscolhidodepessoas) //Faz a rotação
                frenteFila=1;
        }

        printf("\n\nA pessoa %d vai para o caixa com %d contas", frenteFila , pessoas[frenteFila]);
        printf("\nPaga ate %d contas", quantum);

        // ============================
        // Cálculo correto das contas pagas:
        // paga somente o que realmente tem, evitando valores negativos
        // ============================
        int pago_real = pessoas[frenteFila] < quantum ? pessoas[frenteFila] : quantum;

        pessoas[frenteFila] = pessoas[frenteFila] - pago_real;  //Pagamento correto das contas

        mostrarGrafico(frenteFila, pago_real, pessoas[frenteFila], rodada);
        rodada++; //sempre quando um novo quantun é processado

        if(pessoas[frenteFila] <= 0){
            printf("\nE sai da fila.\n");
            contadorFila--;
        }
        else{
            printf("\nE vai pro final da fila com %d contas restantes.\n", pessoas[frenteFila]);
        }

        frenteFila++;                   //Atualiza primeira posição
        if(frenteFila > NumEscolhidodepessoas)   //Faz a rotação
            frenteFila=1;

        // Pausa no Linux
        printf("Pressione ENTER para continuar...");
        getchar();
        getchar();
    }
}


int main(){
    printf("\nDigite o numero maximo de contas a pagar no caixa (quantum): ");
    scanf("%d", &quantum);

    printf("\nDigite o numero de pessoas na fila: ");
    scanf("%d", &NumEscolhidodepessoas);

    contas();
    fila();

    printf("\n\n:::::::::::: Fim :::::::::::::\n");
}
