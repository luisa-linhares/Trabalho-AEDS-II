//
// Created by Vanessa Braganholo on 16/09/2018.
//

#include "funcionario.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include<time.h>

// Imprime funcionario
void imprime(TFunc *func) {
    printf("**********************************************");
    printf("\nFuncionario de código ");
    printf("%d", func->cod);
    printf("\nNome: ");
    printf("%s", func->nome);
    printf("\nCPF: ");
    printf("%s", func->cpf);
    printf("\nData de Nascimento: ");
    printf("%s", func->data_nascimento);
    printf("\nSalário: ");
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

TFunc* busca_por_codigo(FILE* in, int codigo) {
    TFunc* func;

    rewind(in); // Retorna ao início do arquivo

    while ((func = le(in)) != NULL) {
        if (func->cod == codigo) {
            return func; // Retorna o funcionário encontrado
        }
        free(func);
    }

    return NULL; // Funcionário não encontrado
}

// Retorna tamanho do funcionario em bytes
int tamanho() {
    return sizeof(int)  //cod
           + sizeof(char) * 50 //nome
           + sizeof(char) * 15 //cpf
           + sizeof(char) * 11 //data_nascimento
           + sizeof(double); //salario
}



