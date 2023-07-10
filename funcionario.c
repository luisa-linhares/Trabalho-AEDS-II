#include "funcionario.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <math.h>
#include "pilha.h"

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

// FunÁ„o auxiliar para gerar uma string aleatÛria
void gera_string_aleatoria(char* str, int tamanho) {
    static const char caracteres[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int i;
    for (i = 0; i < tamanho - 1; ++i) {
        str[i] = caracteres[rand() % (sizeof(caracteres) - 1)];
    }
    str[tamanho - 1] = '\0';
}

// FunÁ„o auxiliar para gerar um CPF aleatÛrio
void gera_cpf_aleatorio(char* cpf) {
    sprintf(cpf, "%03d.%03d.%03d-%02d", rand() % 1000, rand() % 1000, rand() % 1000, rand() % 100);
}

// Gera um funcion·rio aleatÛrio
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
    //func->nome ao invÈs de &func->nome, pois string j· È ponteiro
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
    rewind(in); // Retorna ao inÌcio do arquivo

    clock_t start_time = clock(); // Inicia a contagem de tempo

     int comparacoes = 0; // Vari·vel para contar o n˙mero de comparaÁıes

    while ((func = le(in)) != NULL) {

        comparacoes++; // Incrementa o contador de comparaÁıes

        if (func->cod == codigo) {
            clock_t end_time = clock(); // Finaliza a contagem de tempo
            double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; // Calcula o tempo decorrido em segundos
            printf("\nTempo de busca: %.4f segundos\n", elapsed_time);

            printf("\nNumero de comparacoes: %d\n", comparacoes);

            return func; // Retorna o funcion·rio encontrado
        }

        free(func);
    }

    clock_t end_time = clock(); // Finaliza a contagem de tempo
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; // Calcula o tempo decorrido em segundos
    printf("\nTempo de busca: %.4f segundos\n", elapsed_time);
    printf("\nNumero de comparacoes: %d\n", comparacoes);
    return NULL; // Funcion·rio n„o encontrado
}

TFunc*  busca_binaria_por_codigo(FILE* in, int codigo) {
    fseek(in, 0, SEEK_END); // Move o cursor para o final do arquivo
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
        }

        if (func->cod == codigo) {
           clock_t end_time = clock(); // Finaliza a contagem de tempo
           double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; // Calcula o tempo decorrido em segundos
           printf("\nTempo de busca: %.4f segundos\n", elapsed_time);
           printf("\nNumero de comparacoes: %d\n", comparacoes);
           return func; // Retorna o funcion·rio encontrado
        } else if (func->cod < codigo) {
            left = mid + 1; // Atualiza o Ìndice inicial para a busca na metade superior
        } else {
            right = mid - 1; // Atualiza o Ìndice final para a busca na metade inferior
        }

        free(func);
    }

    clock_t end_time = clock(); // Finaliza a contagem de tempo
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; // Calcula o tempo decorrido em segundos
   printf("\nTempo de busca: %.4f segundos\n", elapsed_time);

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

void classificacaoInterna(FILE *arq, int M) {

    rewind(arq); //posiciona cursor no inicio do arquivo


    int reg = 0;
    int nFunc = qtdRegistros(arq);
    int qtdParticoes = 0;
    int t = tamanho();
    char nome[10];
    char numero[5];
    char extensao[5];

        //itoa(qtdParticoes,numero,10);

    while (reg != nFunc) {
        //le o arquivo e coloca no vetor
        TFunc *v[M];
        int i = 0;
        while (!feof(arq)) {
            fseek(arq, (reg) * tamanho(), SEEK_SET);
            v[i] = le(arq);
       //     imprime_funcionario(v[i]);
            i++;
            reg++;
            if(i>=M) break;
        }

        //ajusta tamanho M caso arquivo de entrada tenha terminado antes do vetor
        if (i != M) {
            M = i;
        }

        //faz ordenacao
        for (int j = 1; j < M; j++) {
            TFunc *f = v[j];
            i = j - 1;
            while ((i >= 0) && (v[i]->cod > f->cod)) {
                v[i + 1] = v[i];
                i = i - 1;
            }
            v[i + 1] = f;
        }

        //cria arquivo de particao e faz gravacao
        printf("\n\nParticao %d",qtdParticoes);
        strcpy(nome,"particao");
        strcpy(extensao,".dat");
        itoa(qtdParticoes,numero,10);
        strcat(nome,numero);
        strcat(nome,extensao);

        //printf("\n%s\n", nome);

        FILE *p;

        if ((p = fopen(nome, "wb+")) == NULL) {
            printf("Erro criar arquivo de saida\n");
        } else {
            for (int i = 0; i < M; i++) {
                fseek(p, (i) * tamanho(), SEEK_SET);
                salva(v[i], p);
                imprime(v[i]);
            }
            fclose(p);
            qtdParticoes++;
        }
        for(int jj = 0; jj<M; jj++)
            free(v[jj]);
    }
    //nParticoes = qtdParticoes;
}



void intercalacao_basico(FILE *out, int num_p) {

    char nome[10];
    char numero[5];
    char extensao[5];

                    //criando pilha com o conteudo das particoes geradas
                    TPilha **vetPilhas;
                    vetPilhas = (TPilha **) malloc(sizeof(TPilha *) * (num_p));
                    int *vetTopo;
                    vetTopo = (int *) malloc(sizeof(int) * (num_p));

                    for(int p = 0 ; p < num_p ; p++){
                        //alocando a mem√≥ria para salvar uma pilha para cada particao
                        vetPilhas[p] = (TPilha *) malloc(sizeof(TPilha) * (8));
                        //abrindo primeira parti√ß√£o para leitura
                        strcpy(nome,"particao");
                        strcpy(extensao,".dat");
                        itoa(p,numero,10);
                        strcat(nome,numero);
                        strcat(nome,extensao);
                        FILE *part = fopen(nome, "rb+");
                        //printf("%s \n", "Particao 0");
                        //nomes = nomes->prox;
                        //imprimindo os funcion√°rios gravados nas parti√ß√µes
                        //imprimirBase(part);
                        //inicializando os topos das pilhas
                        vetTopo[p] = -1;
                        //criando pilha atrav√©s da leitura da parti√ß√£o
                        cria_pilha_particao(vetPilhas[p], part, 8, &vetTopo[p]);
                        //fechando a parti√ß√£o
                        fclose(part);
                    }
                    //crioupilhas = 1;
                    //nomes = prox;

    int fim = 0; //variavel que controla fim do procedimento



        //cria vetor de particoes
        TVet v[num_p];

        //abre arquivos das particoes, colocando variavel de arquivo no campo f do vetor
        //e primeiro funcionario do arquivo no campo func do vetor
        for (int i=0; i < num_p; i++) {
            strcpy(nome,"particao");
            strcpy(extensao,".dat");
            itoa(i,numero,10);
            strcat(nome,numero);
            strcat(nome,extensao);

            //printf("%s",nome);

            v[i].f = fopen(nome, "rb");
            v[i].aux_p = 0;

            if (v[i].f != NULL) {
                fseek(v[i].f, v[i].aux_p * tamanho(), SEEK_SET);
                TFunc *f = le(v[i].f);
                if (f == NULL) {
                    //arquivo estava vazio
                    //coloca HIGH VALUE nessa posi??o do vetor
                    v[i].func = funcionario_aleatorio(INT_MAX);
                }
                else {
                    //conseguiu ler funcionario, coloca na posi??o atual do vetor
                    v[i].func = f;
                }
            }
            else {
                fim = 1;
            }
            //nome_particoes = nome_particoes->prox;
        }

        int aux = 0;
        while (!(fim)) { //conseguiu abrir todos os arquivos
            int menor = INT_MAX;
            int pos_menor;
            //encontra o funcionario com menor chave no vetor
            for(int i = 0; i < num_p; i++){
                if(v[i].func->cod < menor){
                    menor = v[i].func->cod;
                    pos_menor = i;
                }
            }
            if (menor == INT_MAX) {
                fim = 1; //terminou processamento
            }
            else {
                //salva funcionario no arquivo de sa√≠da
                fseek(out, aux * tamanho(), SEEK_SET);
                salva(v[pos_menor].func, out);
                //printf("%d ",pos_menor);
                //atualiza posi√ß√£o pos_menor do vetor com pr?ximo funcionario do arquivo
                v[pos_menor].aux_p++;
                fseek(v[pos_menor].f, v[pos_menor].aux_p * tamanho(), SEEK_SET);
                TFunc *f = le(v[pos_menor].f);
                aux++;
                if (f == NULL) {
                    //arquivo estava vazio
                    //coloca HIGH VALUE nessa posi√ßao do vetor
                    v[pos_menor].func = funcionario_aleatorio(INT_MAX);
                }
                else {
                    v[pos_menor].func = f;
                }

            }
        }

        //fecha arquivos das parti√á√µes de entrada
        for(int i = 0; i < num_p; i++){
            fclose(v[i].f);
        //    free(v[i].func);
        }
        //fecha arquivo de sa√≠da
        //fclose(out);

}




