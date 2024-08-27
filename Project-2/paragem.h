/* Ficheiro: paragem.h
Aluno: Leonor Costa Figueira
Nº de Aluno: 106157
Descricao: Ficheiro com constantes, estruturas
e protótipos das funcoes de paragens */


#ifndef PARAGEM_H
#define PARAGEM_H

#include "tipos.h"
#include "carreira.h"

#define TRUE          1      /* verdadeiro */
#define FALSE         0      /* falso */


/* FUNCOES RELATIVAS A PARAGENS */


/* Funcoes relacionadas a objetos e nodes de paragens */


/* cria-se uma nova paragem e a mesma e' devolvida*/
pParagem novaPar(char *nome, double latitude, double longitude);

/* e' libertada uma paragem */
void freePar(pParagem p);

/* o no' de uma paragem e' criado */
node_par newNode_par(pParagem p);


/* Funcoes relacionadas a listas de paragens */


/* cria-se uma nova lista de paragens vazia */
lista_par nova_lista_par();

/* liberta memoria associada a uma lista de paragens */
void free_list_par(lista_par p, int quero_eliminar);

/* insere-se uma paragem no final da lista de paragens */
void insere_na_lista_par(lista_par p, pParagem par);

/* procura e devolve uma paragem, se a mesma estiver na lista de paragens */
pParagem procura_na_lista_par(lista_par p, char* nome);

/* remove o elemento da lista de paragens */
void remove_da_lista_par(lista_par p, char *nome);


/* Funcoes relacionadas com tabelas de dispersao */


/* cria-se uma nova tabela de dispersao de paragens vazia */
lista_par *criarTabelaPar(int DimTabelaPar);

/* e' inserida uma paragem na tabela de dispersao das paragens */
void insereNaTabela_par(lista_par *tabela_par, pParagem p, int DimTabelaPar);

/* procura e devolve uma paragem, se a mesma 
estiver na tabela de dispersao de paragens */
pParagem procuraNaTabela_par(lista_par *tabela_par, 
                                char *nome, int DimTabelaPar);

/* e' eliminada uma paragem na tabela de dispersao das paragens */
void eliminaDaTabela_par(lista_par *tabela_par, char *nome, int DimTabelaPar);


#endif /* PARAGEM_H */
