/* Ficheiro: util.c
Aluno: Leonor Costa Figueira
Nº de Aluno: 106157
Descricao: Ficheiro com funcoes auxiliares ao projeto */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"


/* FUNCOES */


/* Funcoes relacionadas a memoria */

void no_memory() {

    printf("No memory.");
    exit(EXIT_FAILURE);
}

char *CriaVectorInstrucao(int tamanho) {

    char *v = (char*) malloc(tamanho * sizeof(char));
    if (v == NULL) no_memory();
    return v;
}

void free_instrucao(char *instrucao) {
    free(instrucao);
}

void free_palavra(char *palavra) {
    free(palavra);
}


/* Funcoes de leitura de dados de input */

void leInstrucao(char *instrucao_vazia) {

    int i = 0;
    char c;

    while ((c = getchar()) != '\n')
        instrucao_vazia[i++] = c;
    instrucao_vazia[i] = '\0';
}


int lePalavra(char **instrucao_ptr, char **palavra_ptr) {

    int cont = 0, i = 0, inicio, j, k, shift;
    char *instrucao = *instrucao_ptr;

    while (instrucao[i] == ' ' || instrucao[i] == '\t')
        i++;

    if (instrucao[i] == '"') {

        i++;
        inicio = i;

        while (instrucao[i++] != '"') 
            cont++;
    }

    else {
        inicio = i;

        /* \0 determina o final da instrucao */
        while (instrucao[i] != ' ' && instrucao[i] != '\t' 
                && instrucao[i] != '\0') {

            i++;
            cont++;
        }
    }

    if (cont == 0)
        return 0;

    *palavra_ptr = (char*) malloc((cont + 1) * sizeof(char));
    if (*palavra_ptr == NULL) no_memory();

    for (k = inicio, j = 0; j < cont; k++, j++) 
        (*palavra_ptr)[j] = instrucao[k];
    
    (*palavra_ptr)[j] = '\0';
    
    shift = i;

    /* o ponteiro avança */
    (*instrucao_ptr) += shift;

    return shift;
}


/* Funcao que duplica uma string */

char *strdup(char *str) {

    int comp = strlen(str);

    /* comp + 1 devido ao caracter '\0' */
    char *destino = (char*) malloc((comp + 1) * sizeof(char));
    if (destino == NULL) no_memory();
    memcpy(destino, str, sizeof(char) * (comp + 1));
    return destino;
}


/* Funcao hash utilizada nas tabelas de dispersao */

unsigned int hash(char *nome, int DimTabela) {

    int i;
    unsigned int valor_hash = 1;
    int comp = strlen(nome);

    for (i = 0; i < comp; i++)

        /* vai-se multiplicando a soma do valor ascii do elemento em
        questao com o valor ascii do ultimo elemento do nome */
        valor_hash *= nome[i] + nome[comp - 1];
    
    /* para o valor encontrar-se dentro dos limites da tabela */
    valor_hash = valor_hash % DimTabela;
    

    return valor_hash;
}

