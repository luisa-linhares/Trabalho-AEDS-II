#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcionario.h"


// Função para inserir funcionários no arquivo
void insere_funcionarios(FILE* out, int tamanhoBase) {
    printf("Inserindo funcionarios no arquivo...\n");

    for (int i = 0; i < tamanhoBase; i++) {
        TFunc* func = funcionario_aleatorio(i + 1);
        salva(func, out);
        free(func);
    }
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

void busca_funcionario_especifico(FILE *in, int cod){
    rewind(in);
    TFunc* func = busca_por_codigo(in, cod);
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
        printf("\nInforme o tamanho da base de dados: ");
        scanf("%d", &tamanhoBase);
        //Cria base de dados no arquivo
        insere_funcionarios(out, tamanhoBase);

        le_funcionarios(out);

        int codFuncionario = 0;
        printf("\nInforme o codigo do funcionario desejado: ");
        scanf("%d", &codFuncionario);

        busca_funcionario_especifico(out, codFuncionario);


        //fecha arquivo
        fclose(out);
    }
}
