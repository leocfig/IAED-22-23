/* Ficheiro: ligacao.h
Aluno: Leonor Costa Figueira
Nº de Aluno: 106157
Descricao: Ficheiro com estruturas e protótipos das funcoes de ligacoes */


#ifndef LIGACAO_H
#define LIGACAO_H

#include "tipos.h"
#include "paragem.h"


/* FUNCOES RELATIVAS A LIGACOES */

/* Funcoes relacionadas a objetos e nodes de ligacoes */


/* cria-se uma nova ligacao e a mesma e' devolvida */
pLigacao novaLig(pParagem par_origem, pParagem par_destino, double custo,
                double duracao);

/* e' libertada uma ligacao */
void freeLig(pLigacao l);

/* o no' de uma ligacao e' criado */
node_lig newNode_lig(pLigacao l);


/* Funcoes relacionadas a listas de ligacoes */


/* cria-se uma nova lista de ligacoes vazia */
lista_lig nova_lista_lig();

/* liberta memoria associada a uma lista de ligacoes */
void free_list_lig(lista_lig l);

/* insere-se uma ligacao no final da lista de ligacoes */
void insere_na_lista_lig(lista_lig l, pLigacao lig);

/* insere-se uma ligacao no inicio da lista de ligacoes */
void insere_na_lista_lig_inicio(lista_lig l, pLigacao lig);

/* procura e devolve uma ligacao, se a mesma estiver na lista de ligacoes */
pLigacao procura_na_lista_lig(lista_lig l, char* nome_paragem);

/* procura e devolve o node da ligacao numa lista, se existir */
node_lig getnode_Lig(lista_lig l, pLigacao lig);

/* remove o elemento da lista de ligacoes */
void remove_da_lista_lig(lista_lig l, pLigacao lig);


#endif /* LIGACAO_H */
