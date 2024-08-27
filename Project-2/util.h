/* Ficheiro: util.h
Aluno: Leonor Costa Figueira
Nº de Aluno: 106157
Descricao: Ficheiro com constantes e prototipos 
das funcoes auxiliares ao projeto */


#ifndef UTIL_H
#define UTIL_H


#define EXIT_FAILURE        1      /* programa terminou sem sucesso */
#define DIMTABELAPAR        1000   /* comprimento maximo da tabela  */
                                   /* de dispersao das paragens     */
#define DIMTABELACARR       1000   /* comprimento maximo da tabela  */
                                   /* de dispersao das carreiras    */


/* FUNCOES */


/* Funcoes relacionadas a memoria */


/* e' imprimido uma mensagem se a memoria
foi esgotada e o programa e' terminado */
void no_memory();

/* um vetor para a instrucao e' alocado dinamicamente */
char *CriaVectorInstrucao(int tamanho);

/* liberta-se a memoria alocada para o vetor da instrucao */
void free_instrucao(char *instrucao);

/* liberta-se a memoria alocada para o vetor da palavra */
void free_palavra(char *palavra);


/* Funcoes de leitura de dados de input */


/* funcao que le o input dado */
void leInstrucao(char *instrucao_vazia);

/* funcao que le uma determinada palavra */
int lePalavra(char **instrucao, char **palavra);


/* Funcoes Auxiliares */

/* uma string e' duplicada */
char *strdup(char *str);

/* funcao hash utilizada na tabela de dispersao */
unsigned int hash(char *nome, int DimTabela);


#endif /* UTIL_H */
