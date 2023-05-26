#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcionario.h"


// Função para inserir funcionários no arquivo
void insere_funcionarios(FILE* out) {
    printf("Inserindo funcionarios no arquivo...\n");

    for (int i = 0; i < 10; i++) {
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
    TFunc* func = busca_por_codigo(in, 8);
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
    //abre arquivo
    if ((out = fopen("funcionario.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    else {
        //insere funcion�rios
        insere_funcionarios(out);
        
        le_funcionarios(out);

        //fecha arquivo
        fclose(out);
    }
}
