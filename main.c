#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcionario.h"
#include "pilha.h"

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

void divide_arquivo_em_particoes(FILE* in, int tamanho_particao) {
    printf("Dividindo o arquivo em partições...\n");

    rewind(in); // Volta ao início do arquivo

    // Cria um vetor de ponteiros para TFunc
    TFunc** funcionarios = (TFunc**)malloc(tamanho_particao * sizeof(TFunc*));
    if (funcionarios == NULL) {
        printf("Erro ao alocar memória para o vetor de funcionários.\n");
        return;
    }

    int num_particao = 1;
    char nome_arquivo_particao[20];
    FILE* out;

    TFunc* func;

    while ((func = le(in)) != NULL) {
        // Adiciona o funcionário atual ao vetor
        funcionarios[0] = func;

        // Lê os funcionários adicionais até preencher o vetor
        int registros_lidos = 1;
        while (registros_lidos < tamanho_particao && (func = le(in)) != NULL) {
            funcionarios[registros_lidos] = func;
            registros_lidos++;
        }

        // Ordena o vetor utilizando o insertion sort
        for (int j = 1; j < registros_lidos; j++) {
            TFunc* f = funcionarios[j];
            int i = j - 1;
            while (i >= 0 && funcionarios[i]->cod > f->cod) {
                funcionarios[i + 1] = funcionarios[i];
                i--;
            }
            funcionarios[i + 1] = f;

        }

        // Abre um novo arquivo para cada partição
        snprintf(nome_arquivo_particao, sizeof(nome_arquivo_particao), "particao%d.dat", num_particao);
        out = fopen(nome_arquivo_particao, "w+b");
        if (out == NULL) {
            printf("Erro ao criar o arquivo da partição %d.\n", num_particao);
            break;
        }

        // Escreve a partição atual no novo arquivo
        for (int i = 0; i < registros_lidos; i++) {
            salva(funcionarios[i], out);
            free(funcionarios[i]);
        }
        le_funcionarios(out);
        // Fecha o arquivo da partição atual
        fclose(out);

        printf("Partição %d criada com sucesso.\n", num_particao);
        num_particao++;
    }

    free(funcionarios);

    printf("Arquivo dividido em %d partições.\n", num_particao - 1);
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
        int tamanhoParticao = 0;

        printf("Informe a ordem da base: [1] - Cria base ordenada\t[2] - Cria base desordenada\t");
        scanf("%d", &opcaoBase);
        if (opcaoBase == 1) {
            printf("\nInforme o tamanho da base de dados: ");
            scanf("%d", &tamanhoBase);

            insere_funcionarios_ordenados(out, tamanhoBase);

            printf("Informe o processo a ser executado: ");
            printf("[1] - Imprime base\t[2] - Busca funcionário específico\t");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    le_funcionarios(out);
                    break;
                case 2:
                    printf("\nInforme o código do funcionário desejado: ");
                    scanf("%d", &codFuncionario);
                    busca_funcionario_especifico(out, codFuncionario, opcaoBase);
                    break;
                default:
                    printf("Processo inválido!\n");
                    break;
            }
        }else if(opcaoBase == 2){
            printf("\nInforme o tamanho da base de dados: ");
            scanf("%d", &tamanhoBase);

            //Cria base de dados desordenada
            insere_funcionarios_desordenados(out, tamanhoBase);
            //insertion_sort(out, tamanhoBase);
            printf("Informe o processo a ser execultado: \n");
            printf("[1] - Imprime base\t[2] - Busca funcinario especifico\t[3] - Dividir arquivo em partições\t\n");
            scanf("%d", &opcao);

            switch (opcao){
                case 1:
                    //Imprimir base de dados
                    le_funcionarios(out);
                    break;
                case 2:
                    //Busca Sequencial
                    printf("\nInforme o codigo do funcionario desejado: \n");
                    scanf("%d", &codFuncionario);
                    busca_funcionario_especifico(out, codFuncionario, opcaoBase);
                    break;
                case 3:
                    //Ordena arquivo
                    printf("\nInforme o tamanho de cada partição: \n");
                    scanf("%d", &tamanhoParticao);
                    //divide_arquivo_em_particoes(out, tamanhoParticao);
                    classificacaoInterna(out, tamanhoParticao);
                    printf("\n\nComeca a intercalacao\n");
                    intercalacao_basico(out, tamanhoParticao);
                    le_funcionarios(out);
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
