#include "funcionario.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

// Imprime funcionario
void imprime(TFunc *func) {
    printf("**********************************************");
    printf("\nFuncionario de codigo ");
    printf("%d", func->cod);
    printf("\nNome: ");
    printf("%s", func->nome);
    printf("\nCPF: ");
    printf("%s", func->cpf);
    printf("\nData de Nascimento: ");
    printf("%s", func->data_nascimento);
    printf("\nSalario: ");
    printf("%4.2f", func->salario);
    printf("\n**********************************************");
}

// Função auxiliar para gerar uma string aleatória
void gera_string_aleatoria(char* str, int tamanho) {
    static const char caracteres[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int i;
    for (i = 0; i < tamanho - 1; ++i) {
        str[i] = caracteres[rand() % (sizeof(caracteres) - 1)];
    }
    str[tamanho - 1] = '\0';
}

// Função auxiliar para gerar um CPF aleatório
void gera_cpf_aleatorio(char* cpf) {
    sprintf(cpf, "%03d.%03d.%03d-%02d", rand() % 1000, rand() % 1000, rand() % 1000, rand() % 100);
}

// Gera um funcionário aleatório
TFunc* funcionario_aleatorio(int cod) {
    TFunc* func = (TFunc*)malloc(sizeof(TFunc));

    func->cod = cod;
    gera_string_aleatoria(func->nome, 50);
    gera_cpf_aleatorio(func->cpf);
    gera_string_aleatoria(func->data_nascimento, 11);
    func->salario = (double)(rand() % 10000) + 1000.0;

    return func;
}
// Salva funcionario no arquivo out, na posicao atual do cursor
void salva(TFunc *func, FILE *out) {
    fwrite(&func->cod, sizeof(int), 1, out);
    //func->nome ao invés de &func->nome, pois string já é ponteiro
    fwrite(func->nome, sizeof(char), sizeof(func->nome), out);
    fwrite(func->cpf, sizeof(char), sizeof(func->cpf), out);
    fwrite(func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), out);
    fwrite(&func->salario, sizeof(double), 1, out);
}

// Le um funcionario do arquivo in na posicao atual do cursor
// Retorna um ponteiro para funcionario lido do arquivo
TFunc *le(FILE *in) {
    TFunc *func = (TFunc *) malloc(sizeof(TFunc));
    if (0 >= fread(&func->cod, sizeof(int), 1, in)) {
        free(func);
        return NULL;
    }
    fread(func->nome, sizeof(char), sizeof(func->nome), in);
    fread(func->cpf, sizeof(char), sizeof(func->cpf), in);
    fread(func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), in);
    fread(&func->salario, sizeof(double), 1, in);
    return func;
}

TFunc* busca_sequencial_por_codigo(FILE* in, int codigo) {
    TFunc* func;
    rewind(in); // Retorna ao início do arquivo

    clock_t start_time = clock(); // Inicia a contagem de tempo

     int comparacoes = 0; // Variável para contar o número de comparações

    while ((func = le(in)) != NULL) {

        comparacoes++; // Incrementa o contador de comparações

        if (func->cod == codigo) {
            clock_t end_time = clock(); // Finaliza a contagem de tempo
            double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; // Calcula o tempo decorrido em segundos
            printf("\nTempo de busca: %.4f segundos\n", elapsed_time);

            printf("\nNumero de comparacoes: %d\n", comparacoes);

            return func; // Retorna o funcionário encontrado
        }

        free(func);
    }

    clock_t end_time = clock(); // Finaliza a contagem de tempo
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; // Calcula o tempo decorrido em segundos
    printf("\nTempo de busca: %.4f segundos\n", elapsed_time);
    printf("\nNumero de comparacoes: %d\n", comparacoes);
    return NULL; // Funcionário não encontrado
}

TFunc*  busca_binaria_por_codigo(FILE* in, int codigo) {
    fseek(in, 0, SEEK_END); // Move o cursor para o final do arquivo
    long size = ftell(in); // Obtém o tamanho total do arquivo em bytes

    int num_regs = size / tamanho(); // Calcula o número de registros no arquivo

    int left = 0; // Índice inicial da busca
    int right = num_regs - 1; // Índice final da busca

    clock_t start_time = clock(); // Inicia a contagem de tempo

    int comparacoes = 0; // Variável para contar o número de comparações

    while (left <= right) {
        int mid = left + (right - left) / 2; // Calcula o índice do elemento do meio

        fseek(in, mid * tamanho(), SEEK_SET); // Move o cursor para a posição do meio

        TFunc* func = le(in); // Lê o registro na posição atual

        comparacoes++; // Incrementa o contador de comparações

        if (func == NULL) {
            break; // Saí do loop se ocorrer um erro de leitura
        }

        if (func->cod == codigo) {
           clock_t end_time = clock(); // Finaliza a contagem de tempo
           double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; // Calcula o tempo decorrido em segundos
           printf("\nTempo de busca: %.4f segundos\n", elapsed_time);
           printf("\nNumero de comparacoes: %d\n", comparacoes);
           return func; // Retorna o funcionário encontrado
        } else if (func->cod < codigo) {
            left = mid + 1; // Atualiza o índice inicial para a busca na metade superior
        } else {
            right = mid - 1; // Atualiza o índice final para a busca na metade inferior
        }

        free(func);
    }

    clock_t end_time = clock(); // Finaliza a contagem de tempo
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; // Calcula o tempo decorrido em segundos
   printf("\nTempo de busca: %.4f segundos\n", elapsed_time);

  printf("\nNumero de comparacoes: %d\n", comparacoes);

    return NULL; // Funcionário não encontrado
}

void insertion_sort(FILE *arq, int tam) {
    TFunc *v[tam];
    //le o arquivo e coloca no vetor
    rewind(arq); //posiciona cursor no inicio do arquivo
    TFunc *f = le(arq);
    int i = 0;
    while (!feof(arq)) {
        v[i] = f;
        f = le(arq);
        i++;
    }
    //faz o insertion sort
    for (int j = 1; j < tam; j++) {
        TFunc *f = v[j];
        i = j - 1;
        while ((i >= 0) && (v[i]->cod > f->cod)) {
            v[i + 1] = v[i];
            i = i - 1;
        }
        v[i+1] = f;
    }
    //grava vetor no arquivo, por cima do conteÃºdo anterior
    rewind(arq);
    for (int i = 0; i < tam; i++) {
        salva(v[i], arq);
    }
    //descarrega o buffer para ter certeza que dados foram gravados
    fflush(arq);

}

// Retorna tamanho do funcionario em bytes
int tamanho() {
    return sizeof(int)  //cod
           + sizeof(char) * 50 //nome
           + sizeof(char) * 15 //cpf
           + sizeof(char) * 11 //data_nascimento
           + sizeof(double); //salario
}

int qtdRegistros(FILE *in){
    fseek(in, 0, SEEK_END);
    int tam = trunc(ftell(in))/tamanho();
    return tam;
}



