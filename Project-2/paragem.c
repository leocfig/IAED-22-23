/* Ficheiro: paragem.c
Aluno: Leonor Costa Figueira
Nº de Aluno: 106157
Descricao: Ficheiro com funcoes de abstracao de paragens */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tipos.h"
#include "util.h"
#include "paragem.h"


/* FUNCOES RELATIVAS A PARAGENS */

/* Funcoes relacionadas a objetos e nodes de paragens */

pParagem novaPar(char *nome, double latitude, double longitude) {

    pParagem new = (pParagem)malloc(sizeof(struct Paragem));
    if (new == NULL) no_memory();
    new->nome = strdup(nome);
    new->latitude = latitude;
    new->longitude = longitude;

    /* cria-se a lista das carreiras que passam numa paragem */
    new->ptr_carr_par = nova_lista_carr();
    new->nr_carreiras_par = 0;

    return new;
}

void freePar(pParagem p) {
    free(p->nome);
    free_list_carr(p->ptr_carr_par, FALSE);
    free(p);
}

node_par newNode_par(pParagem p) {

    node_par new = (node_par)malloc(sizeof(struct node_paragem));
    if (new == NULL) no_memory();
    new->par = p;
    new->next = NULL;
    return new;
}

/* Funcoes relacionadas a listas de paragens */

lista_par nova_lista_par() {

    lista_par p = (lista_par)malloc(sizeof(struct listaPar));
    if (p == NULL) no_memory();
    p->head = NULL;
    p->last = NULL;
    return p;
}

void free_list_par(lista_par p, int quero_eliminar) {

    node_par ptr;
    if (p != NULL) {
        while (p->head != NULL) {
            ptr = p->head;
            p->head = p->head->next;

            /* se for necessario eliminar tambem a paragem em si */
            if (quero_eliminar) 
                freePar(ptr->par);
            
            free(ptr);
        }
        free(p);
    }
}

void insere_na_lista_par(lista_par p, pParagem par) {

    node_par new = newNode_par(par);

    /* caso de ja' haver elemento(s) na lista */
    if (p->last != NULL)
        p->last->next = new;
    p->last = new;

    /* no caso de nao haver nenhum elemento na lista */
    if (p->head == NULL)
        p->head = new;
}

pParagem procura_na_lista_par(lista_par p, char* nome) {
    node_par ptr;

    if (p == NULL)
        return NULL;

    for (ptr = p->head; ptr != NULL; ptr = ptr->next)
        if(strcmp(ptr->par->nome, nome) == 0)
            return ptr->par;

    return NULL;
}

void remove_da_lista_par(lista_par p, char *nome) { 

    node_par ptr, prev;

    if (p == NULL)
        return;
    
    for (ptr = p->head, prev = NULL; ptr != NULL; prev = ptr, ptr = ptr->next){

        if (strcmp(ptr->par->nome, nome) == 0) {

            /* se for o primeiro elemento a ser eliminado */
            if (ptr == p->head) {
                p->head = ptr->next;

                /* existindo apenas um elemento */
                if (ptr->next == NULL)
                    p->last = NULL;
            }

            /* se for o ultimo elemento a ser eliminado */
            else if (ptr == p->last) {
                p->last = prev;
                p->last->next = NULL;
            }

            else
                prev->next = ptr->next;

            free(ptr);
            break;
        }
    }
}


/* Funcoes relacionadas com tabelas de dispersao de paragens */


lista_par *criarTabelaPar(int DimTabelaPar) {

    int i;
    lista_par *tabela_par = (lista_par*)malloc(DimTabelaPar *
                                                sizeof(lista_par));
    if (tabela_par == NULL) no_memory();
    for (i = 0; i < DimTabelaPar; i++) {
        tabela_par[i] = nova_lista_par();
    }
    return tabela_par;
}

void insereNaTabela_par(lista_par *tabela_par, pParagem p, int DimTabelaPar) {
    int indice = hash(p->nome, DimTabelaPar);
    insere_na_lista_par(tabela_par[indice], p);
}

pParagem procuraNaTabela_par(lista_par *tabela_par, 
                            char *nome, int DimTabelaPar) {

    int indice = hash(nome, DimTabelaPar);
    return procura_na_lista_par(tabela_par[indice], nome);
}

void eliminaDaTabela_par(lista_par *tabela_par, char *nome, int DimTabelaPar) {
    int indice = hash(nome, DimTabelaPar);
    remove_da_lista_par(tabela_par[indice], nome);
}