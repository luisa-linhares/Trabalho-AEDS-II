#ifndef FUNCIONARIO_H_INCLUDED
#define FUNCIONARIO_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

typedef struct Funcionario {
    int cod;
    char nome[50];
    char cpf[15];
    char data_nascimento[11];
    double salario;
} TFunc;

//estrutura para armazenar o vetor de particoes
typedef struct vetor{
    TFunc *func;
    int aux_p;
    FILE *f;
}TVet;


// Imprime funcionario
void imprime(TFunc *func);

// Fun��o auxiliar para gerar uma string aleat�ria
void gera_string_aleatoria(char* str, int tamanho);

// Fun��o auxiliar para gerar um CPF aleat�rio
void gera_cpf_aleatorio(char* cpf);

// Gera um funcion�rio aleat�rio
TFunc* funcionario_aleatorio(int cod);

// Salva funcionario no arquivo out, na posicao atual do cursor
void salva(TFunc *func, FILE *out);

// Le um funcionario do arquivo in na posicao atual do cursor
// Retorna um ponteiro para funcionario lido do arquivo
TFunc *le(FILE *in);

TFunc* busca_sequencial_por_codigo(FILE* in, int codigo);

TFunc* busca_binaria_por_codigo(FILE* in, int codigo);

void insertion_sort(FILE *arq, int tam);

// Retorna tamanho do funcionario em bytes
int tamanho();
int qtdRegistros(FILE *in);


#endif // FUNCIONARIO_H_INCLUDED
