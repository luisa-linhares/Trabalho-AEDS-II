//
// Created by Vanessa Braganholo on 16/09/2018.
//

#ifndef FUNCIONARIOS_FUNCIONARIO_H
#define FUNCIONARIOS_FUNCIONARIO_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Funcionario {
    int cod;
    char nome[50];
    char cpf[15];
    char data_nascimento[11];
    double salario;
} TFunc;

// Imprime funcionario
void imprime(TFunc *func);

// Função auxiliar para gerar uma string aleatória
void gera_string_aleatoria(char* str, int tamanho);

// Função auxiliar para gerar um CPF aleatório
void gera_cpf_aleatorio(char* cpf);

// Gera um funcionário aleatório
TFunc* funcionario_aleatorio(int cod);

// Salva funcionario no arquivo out, na posicao atual do cursor
void salva(TFunc *func, FILE *out);

// Le um funcionario do arquivo in na posicao atual do cursor
// Retorna um ponteiro para funcionario lido do arquivo
TFunc *le(FILE *in);

TFunc* busca_por_codigo(FILE* in, int codigo);

// Retorna tamanho do funcionario em bytes
int tamanho();

#endif //FUNCIONARIOS_FUNCIONARIO_H

