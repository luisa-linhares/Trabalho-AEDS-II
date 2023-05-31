#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcionario.h"


// Função para inserir funcionários no arquivo
void insere_funcionarios_ordenados(FILE* out, int tamanhoBase) {
    printf("Inserindo funcionarios no arquivo...\n");

    for (int i = 0; i < tamanhoBase; i++) {
        TFunc* func = funcionario_aleatorio(i + 1);
        salva(func, out);
        free(func);
    }
}

void insere_funcionarios_desordenados(FILE* out, int num_funcionarios) {
    printf("Inserindo %d funcionários no arquivo...\n", num_funcionarios);

    // Cria um vetor de ponteiros para TFunc
    TFunc** funcionarios = (TFunc**)malloc(num_funcionarios * sizeof(TFunc*));
    if (funcionarios == NULL) {
        printf("Erro ao alocar memória para o vetor de funcionários.\n");
        return;
    }

    // Gera funcionários aleatórios
    for (int i = 0; i < num_funcionarios; i++) {
        TFunc* func = funcionario_aleatorio(i + 1);
        funcionarios[i] = func;
    }

    // Embaralha aleatoriamente o vetor de funcionários
    for (int i = num_funcionarios - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        TFunc* temp = funcionarios[i];
        funcionarios[i] = funcionarios[j];
        funcionarios[j] = temp;
    }

    // Salva os funcionários no arquivo na ordem atual do vetor embaralhado
    for (int i = 0; i < num_funcionarios; i++) {
        salva(funcionarios[i], out);
        free(funcionarios[i]);
    }

    free(funcionarios);

    printf("Base de dados desordenada gerada com sucesso!\n");
}

// Função para ler os funcionários do arquivo
void le_funcionarios(FILE *in) {
    printf("\n\nLendo funcionarios do arquivo...\n\n");
    rewind(in);
    TFunc *f;
    while ((f = le(in)) != NULL) {
        imprime(f);
        free(f);
    }
}

void busca_funcionario_especifico(FILE *in, int cod, int opcaoBase){
    rewind(in);
    TFunc *func;
    if(opcaoBase == 1){
    //TFunc* func = busca_por_codigo(in, cod);
        func = busca_binaria_por_codigo(in, cod);
    }else{
        func = busca_sequencial_por_codigo(in, cod);
    }

    if (func != NULL) {
        printf("\n\nFuncionario encontrado:\n\n");
        imprime(func);
        free(func);
    } else {
        printf("\n\nFuncionario nao encontrado!\n\n");
    }
}

int main(int argc, char** argv)
{
    //declara ponteiro para arquivo
    FILE *out;
    srand(time(NULL));
    int tamanhoBase = 0;

    //abre arquivo
    if ((out = fopen("funcionario.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    else {
        int opcao = 0;
        int opcaoBase= 0;
        int codFuncionario = 0;
        printf("Informe a ordem da base: [1] - Cria base ordenada\t[2] - Cria base desordenada\t");
        scanf("%d", &opcaoBase);
        if(opcaoBase == 1){
            printf("\nInforme o tamanho da base de dados: ");
            scanf("%d", &tamanhoBase);

            //Cria base de dados no arquivo
            insere_funcionarios_ordenados(out, tamanhoBase);


            printf("Informe o processo a ser execultado: ");
            printf("[1] - Imprime base\t[2] - Busca funcinario especifico\t");
            scanf("%d", &opcao);

            switch (opcao){
                case 1:
                    //Imprimir base de dados
                    le_funcionarios(out);
                    break;
                case 2:
                    //Busca Sequencial
                    printf("\nInforme o codigo do funcionario desejado: ");
                    scanf("%d", &codFuncionario);
                    busca_funcionario_especifico(out, codFuncionario, opcaoBase);
                    break;
                default:
                    printf("Processo inválido!");
            }
        }else if(opcaoBase == 2){
            printf("\nInforme o tamanho da base de dados: ");
            scanf("%d", &tamanhoBase);

            //Cria base de dados desordenada
            insere_funcionarios_desordenados(out, tamanhoBase);

            printf("Informe o processo a ser execultado: ");
            printf("[1] - Imprime base\t[2] - Busca funcinario especifico\t");
            scanf("%d", &opcao);

            switch (opcao){
                case 1:
                    //Imprimir base de dados
                    le_funcionarios(out);
                    break;
                case 2:
                    //Busca Sequencial
                    printf("\nInforme o codigo do funcionario desejado: ");
                    scanf("%d", &codFuncionario);
                    busca_funcionario_especifico(out, codFuncionario, opcaoBase);
                    break;
                default:
                    printf("Processo inválido!");
            }
        }else{
            printf("Ordem da base de dados selecionada inválida!");
        }

        //fecha arquivo
        fclose(out);
    }
}
