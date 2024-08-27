/* Ficheiro: carreira.h
Aluno: Leonor Costa Figueira
Nº de Aluno: 106157
Descricao: Ficheiro com estruturas e protótipos das funcoes de carreiras */


#ifndef CARREIRA_H
#define CARREIRA_H


#include "tipos.h"
#include "ligacao.h"


/* FUNCOES RELATIVAS A CARREIRAS */


/* Funcoes relacionadas a objetos e nodes de carreiras */


/* cria-se uma nova carreira e a mesma e' devolvida */
pCarreira novaCarr(char *nome);

/* e' libertada uma carreira */
void freeCarr(pCarreira c);

/* o no' de uma carreira e' criado */
node_carr newNode_carr(pCarreira c);


/* Funcoes relacionadas a listas de carreiras */


/* cria-se uma nova lista de carreiras vazia */
lista_carr nova_lista_carr();

/* liberta memoria associada a uma lista de carreiras */
void free_list_carr(lista_carr c, int quero_eliminar);

/* insere-se uma carreira no final da lista de carreiras */
void insere_na_lista_carr(lista_carr c, pCarreira carr);

/* procura e devolve uma carreira, se a mesma estiver na lista de carreiras */
pCarreira procura_na_lista_carr(lista_carr c, char* nome);

/* remove o elemento da lista de carreiras */
void remove_da_lista_carr(lista_carr c, char *nome);

/* funcao que ordena os elementos de uma lista de ordem alfabetica */
void bubble_sort_str(lista_carr carr);

/* funcao que troca a informacao de duas carreiras numa lista */
void swap_node_inf(node_carr ptr_1, node_carr ptr_2);


/* Funcoes relacionadas com tabelas de dispersao de carreiras */


/* cria-se uma nova tabela de carreiras vazia */
lista_carr *criarTabelaCarr(int DimTabelaCarr);

/* e' inserida uma carreira na tabela de dispersao das carreiras */
void insereNaTabela_carr(lista_carr *tabela_carr, pCarreira c, 
                            int DimTabelaCarr);

/* procura e devolve uma carreira, se a mesma 
estiver na tabela de dispersao de carreiras */
pCarreira procuraNaTabela_carr(lista_carr *tabela_carr, 
                                char *nome, int DimTabelaCarr);

/* e' eliminada uma carreira na tabela de dispersao das carreiras */
void eliminaDaTabela_carr(lista_carr *tabela_carr, char *nome, 
                            int DimTabelaCarr);


#endif /* CARREIRA_H */

