<<<<<<< HEAD
=======
//
// Created by Vanessa Braganholo on 16/09/2018.
//

>>>>>>> f17826373e93bee94fb1344d600d350d93b13972
#include "funcionario.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
<<<<<<< HEAD
#include <time.h>
=======
#include<time.h>
>>>>>>> f17826373e93bee94fb1344d600d350d93b13972

// Imprime funcionario
void imprime(TFunc *func) {
    printf("**********************************************");
<<<<<<< HEAD
    printf("\nFuncionario de codigo ");
=======
    printf("\nFuncionario de c√≥digo ");
>>>>>>> f17826373e93bee94fb1344d600d350d93b13972
    printf("%d", func->cod);
    printf("\nNome: ");
    printf("%s", func->nome);
    printf("\nCPF: ");
    printf("%s", func->cpf);
    printf("\nData de Nascimento: ");
    printf("%s", func->data_nascimento);
<<<<<<< HEAD
    printf("\nSalario: ");
=======
    printf("\nSal√°rio: ");
>>>>>>> f17826373e93bee94fb1344d600d350d93b13972
    printf("%4.2f", func->salario);
    printf("\n**********************************************");
}

<<<<<<< HEAD
// FunÁ„o auxiliar para gerar uma string aleatÛria
=======
// Fun√ß√£o auxiliar para gerar uma string aleat√≥ria
>>>>>>> f17826373e93bee94fb1344d600d350d93b13972
void gera_string_aleatoria(char* str, int tamanho) {
    static const char caracteres[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int i;
    for (i = 0; i < tamanho - 1; ++i) {
        str[i] = caracteres[rand() % (sizeof(caracteres) - 1)];
    }
    str[tamanho - 1] = '\0';
}

<<<<<<< HEAD
// FunÁ„o auxiliar para gerar um CPF aleatÛrio
=======
// Fun√ß√£o auxiliar para gerar um CPF aleat√≥rio
>>>>>>> f17826373e93bee94fb1344d600d350d93b13972
void gera_cpf_aleatorio(char* cpf) {
    sprintf(cpf, "%03d.%03d.%03d-%02d", rand() % 1000, rand() % 1000, rand() % 1000, rand() % 100);
}

<<<<<<< HEAD
// Gera um funcion·rio aleatÛrio
=======
// Gera um funcion√°rio aleat√≥rio
>>>>>>> f17826373e93bee94fb1344d600d350d93b13972
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
<<<<<<< HEAD
    //func->nome ao invÈs de &func->nome, pois string j· È ponteiro
=======
    //func->nome ao inv√©s de &func->nome, pois string j√° √© ponteiro
>>>>>>> f17826373e93bee94fb1344d600d350d93b13972
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

<<<<<<< HEAD
TFunc* busca_sequencial_por_codigo(FILE* in, int codigo) {
    TFunc* func;
    rewind(in); // Retorna ao inÌcio do arquivo

    clock_t start_time = clock(); // Inicia a contagem de tempo

     int comparacoes = 0; // Vari·vel para contar o n˙mero de comparaÁıes

    while ((func = le(in)) != NULL) {

        comparacoes++; // Incrementa o contador de comparaÁıes

=======
TFunc* busca_por_codigo(FILE* in, int codigo) {
    TFunc* func;

    rewind(in); // Retorna ao in√≠cio do arquivo

    while ((func = le(in)) != NULL) {
        if (func->cod == codigo) {
            return func; // Retorna o funcion√°rio encontrado
        }
        free(func);
    }

    return NULL; // Funcion√°rio n√£o encontrado
}

TFunc* busca_sequencial_por_codigo(FILE* in, int codigo) {
    TFunc* func;
    rewind(in); // Retorna ao in√≠cio do arquivo

    clock_t start_time = clock(); // Inicia a contagem de tempo

     int comparacoes = 0; // Vari√°vel para contar o n√∫mero de compara√ß√µes

    while ((func = le(in)) != NULL) {

        comparacoes++; // Incrementa o contador de compara√ß√µes
      
>>>>>>> f17826373e93bee94fb1344d600d350d93b13972
        if (func->cod == codigo) {
            clock_t end_time = clock(); // Finaliza a contagem de tempo
            double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; // Calcula o tempo decorrido em segundos
            printf("\nTempo de busca: %.4f segundos\n", elapsed_time);

<<<<<<< HEAD
            printf("\nNumero de comparacoes: %d\n", comparacoes);

            return func; // Retorna o funcion·rio encontrado
        }

=======
            printf("\nNumero de compara√ß√µes: %d\n", comparacoes);
          
            return func; // Retorna o funcion√°rio encontrado
        }
      
>>>>>>> f17826373e93bee94fb1344d600d350d93b13972
        free(func);
    }

    clock_t end_time = clock(); // Finaliza a contagem de tempo
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; // Calcula o tempo decorrido em segundos
    printf("\nTempo de busca: %.4f segundos\n", elapsed_time);
<<<<<<< HEAD
    printf("\nNumero de comparacoes: %d\n", comparacoes);
    return NULL; // Funcion·rio n„o encontrado
=======
    printf("\nNumero de compara√ß√µes: %d\n", comparacoes);
    return NULL; // Funcion√°rio n√£o encontrado
>>>>>>> f17826373e93bee94fb1344d600d350d93b13972
}

TFunc*  busca_binaria_por_codigo(FILE* in, int codigo) {
    fseek(in, 0, SEEK_END); // Move o cursor para o final do arquivo
<<<<<<< HEAD
    long size = ftell(in); // ObtÈm o tamanho total do arquivo em bytes

    int num_regs = size / tamanho(); // Calcula o n˙mero de registros no arquivo

    int left = 0; // Õndice inicial da busca
    int right = num_regs - 1; // Õndice final da busca

    clock_t start_time = clock(); // Inicia a contagem de tempo

    int comparacoes = 0; // Vari·vel para contar o n˙mero de comparaÁıes

    while (left <= right) {
        int mid = left + (right - left) / 2; // Calcula o Ìndice do elemento do meio

        fseek(in, mid * tamanho(), SEEK_SET); // Move o cursor para a posiÁ„o do meio

        TFunc* func = le(in); // LÍ o registro na posiÁ„o atual

        comparacoes++; // Incrementa o contador de comparaÁıes

        if (func == NULL) {
            break; // SaÌ do loop se ocorrer um erro de leitura
=======
    long size = ftell(in); // Obt√©m o tamanho total do arquivo em bytes

    int num_regs = size / tamanho(); // Calcula o n√∫mero de registros no arquivo

    int left = 0; // √çndice inicial da busca
    int right = num_regs - 1; // √çndice final da busca

    clock_t start_time = clock(); // Inicia a contagem de tempo
  
    int comparacoes = 0; // Vari√°vel para contar o n√∫mero de compara√ß√µes

    while (left <= right) {
        int mid = left + (right - left) / 2; // Calcula o √≠ndice do elemento do meio

        fseek(in, mid * tamanho(), SEEK_SET); // Move o cursor para a posi√ß√£o do meio

        TFunc* func = le(in); // L√™ o registro na posi√ß√£o atual

        comparacoes++; // Incrementa o contador de compara√ß√µes

        if (func == NULL) {
            break; // Sa√≠ do loop se ocorrer um erro de leitura
>>>>>>> f17826373e93bee94fb1344d600d350d93b13972
        }

        if (func->cod == codigo) {
           clock_t end_time = clock(); // Finaliza a contagem de tempo
           double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; // Calcula o tempo decorrido em segundos
           printf("\nTempo de busca: %.4f segundos\n", elapsed_time);
<<<<<<< HEAD
           printf("\nNumero de comparacoes: %d\n", comparacoes);
           return func; // Retorna o funcion·rio encontrado
        } else if (func->cod < codigo) {
            left = mid + 1; // Atualiza o Ìndice inicial para a busca na metade superior
        } else {
            right = mid - 1; // Atualiza o Ìndice final para a busca na metade inferior
=======
           printf("\nNumero de compara√ß√µes: %d\n", comparacoes);
           return func; // Retorna o funcion√°rio encontrado
        } else if (func->cod < codigo) {
            left = mid + 1; // Atualiza o √≠ndice inicial para a busca na metade superior
        } else {
            right = mid - 1; // Atualiza o √≠ndice final para a busca na metade inferior
>>>>>>> f17826373e93bee94fb1344d600d350d93b13972
        }

        free(func);
    }

    clock_t end_time = clock(); // Finaliza a contagem de tempo
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; // Calcula o tempo decorrido em segundos
   printf("\nTempo de busca: %.4f segundos\n", elapsed_time);

<<<<<<< HEAD
  printf("\nNumero de comparacoes: %d\n", comparacoes);

    return NULL; // Funcion·rio n„o encontrado
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
    //grava vetor no arquivo, por cima do conte√∫do anterior
    rewind(arq);
    for (int i = 0; i < tam; i++) {
        salva(v[i], arq);
    }
    //descarrega o buffer para ter certeza que dados foram gravados
    fflush(arq);

=======
  printf("\nNumero de compara√ß√µes: %d\n", comparacoes);

    return NULL; // Funcion√°rio n√£o encontrado
>>>>>>> f17826373e93bee94fb1344d600d350d93b13972
}

// Retorna tamanho do funcionario em bytes
int tamanho() {
    return sizeof(int)  //cod
           + sizeof(char) * 50 //nome
           + sizeof(char) * 15 //cpf
           + sizeof(char) * 11 //data_nascimento
           + sizeof(double); //salario
}

<<<<<<< HEAD
int qtdRegistros(FILE *in){
    fseek(in, 0, SEEK_END);
    int tam = trunc(ftell(in))/tamanho();
    return tam;
}

=======
>>>>>>> f17826373e93bee94fb1344d600d350d93b13972


