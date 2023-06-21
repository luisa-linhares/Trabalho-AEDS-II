<<<<<<< HEAD
#ifndef FUNCIONARIO_H_INCLUDED
#define FUNCIONARIO_H_INCLUDED
=======
//
// Created by Vanessa Braganholo on 16/09/2018.
//

#ifndef FUNCIONARIOS_FUNCIONARIO_H
#define FUNCIONARIOS_FUNCIONARIO_H
>>>>>>> f17826373e93bee94fb1344d600d350d93b13972

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

<<<<<<< HEAD
// Função auxiliar para gerar uma string aleatória
void gera_string_aleatoria(char* str, int tamanho);

// Função auxiliar para gerar um CPF aleatório
void gera_cpf_aleatorio(char* cpf);

// Gera um funcionário aleatório
=======
// FunÃ§Ã£o auxiliar para gerar uma string aleatÃ³ria
void gera_string_aleatoria(char* str, int tamanho);

// FunÃ§Ã£o auxiliar para gerar um CPF aleatÃ³rio
void gera_cpf_aleatorio(char* cpf);

// Gera um funcionÃ¡rio aleatÃ³rio
>>>>>>> f17826373e93bee94fb1344d600d350d93b13972
TFunc* funcionario_aleatorio(int cod);

// Salva funcionario no arquivo out, na posicao atual do cursor
void salva(TFunc *func, FILE *out);

// Le um funcionario do arquivo in na posicao atual do cursor
// Retorna um ponteiro para funcionario lido do arquivo
TFunc *le(FILE *in);

<<<<<<< HEAD
=======
TFunc* busca_por_codigo(FILE* in, int codigo);

>>>>>>> f17826373e93bee94fb1344d600d350d93b13972
TFunc* busca_sequencial_por_codigo(FILE* in, int codigo);

TFunc* busca_binaria_por_codigo(FILE* in, int codigo);

<<<<<<< HEAD
void insertion_sort(FILE *arq, int tam);

// Retorna tamanho do funcionario em bytes
int tamanho();
int qtdRegistros(FILE *in);


#endif // FUNCIONARIO_H_INCLUDED
=======
// Retorna tamanho do funcionario em bytes
int tamanho();

#endif //FUNCIONARIOS_FUNCIONARIO_H

>>>>>>> f17826373e93bee94fb1344d600d350d93b13972
