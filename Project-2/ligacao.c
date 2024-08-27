/* Ficheiro: ligacao.c
Aluno: Leonor Costa Figueira
Nº de Aluno: 106157
Descricao: Ficheiro com funcoes de abstracao de ligacoes */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "tipos.h"
#include "ligacao.h"


/* FUNCOES RELATIVAS A LIGACOES */


/* Funcoes relacionadas a objetos e nodes de ligacoes */

pLigacao novaLig(pParagem par_origem, pParagem par_destino, double custo,
                double duracao) {

    pLigacao new = (pLigacao)malloc(sizeof(struct Ligacao));
    if (new == NULL) no_memory();
    new->par_origem_ptr = par_origem;
    new->par_destino_ptr = par_destino;
    new->custo = custo;
    new->duracao = duracao;
    return new;
}

void freeLig(pLigacao l) {
    free(l);
}

node_lig newNode_lig(pLigacao l) {

    node_lig new = (node_lig)malloc(sizeof(struct node_ligacao));
    if (new == NULL) no_memory();
    new->lig = l;
    new->next = NULL;
    new->previous = NULL;
    return new;
}


/* Funcoes relacionadas a listas de ligacoes */


lista_lig nova_lista_lig() {

    lista_lig l = (lista_lig)malloc(sizeof(struct listaLig));
    if (l == NULL) no_memory();
    l->head = NULL;
    l->last = NULL;
    return l;
}

void free_list_lig(lista_lig l) {

    node_lig ptr;
    if (l != NULL) {
        while (l->head != NULL) {
            ptr = l->head;
            l->head = l->head->next;

            freeLig(ptr->lig);
            free(ptr);
        }
        free(l);
    }
}

void insere_na_lista_lig(lista_lig l, pLigacao lig) {

    node_lig new = newNode_lig(lig);

    /* caso de ja' haver elemento(s) na lista */
    if (l->last != NULL) {
        l->last->next = new;
        new->previous = l->last;
    }
    l->last = new;

    /* caso de nao haver nenhum elemento na lista */
    if (l->head == NULL)
        l->head = new;
}

void insere_na_lista_lig_inicio(lista_lig l, pLigacao lig) {

    node_lig new = newNode_lig(lig);

    /* caso de ja' haver elemento(s) na lista */
    if (l->head != NULL) {
        l->head->previous = new;
        new->next = l->head;
    }
    /* caso de nao haver nenhum elemento na lista */
    else 
        l->last = new;
    l->head = new;
    
}

pLigacao procura_na_lista_lig(lista_lig l, char* nome_paragem) {
    node_lig ptr;

    if (l == NULL)
        return NULL;

    for (ptr = l->head; ptr != NULL; ptr = ptr->next)
        if(strcmp(ptr->lig->par_origem_ptr->nome, nome_paragem) == 0 ||
            strcmp(ptr->lig->par_destino_ptr->nome, nome_paragem) == 0)

            return ptr->lig;

    return NULL;
}

node_lig getnode_Lig(lista_lig l, pLigacao lig) {

    node_lig ptr_l;

    for (ptr_l = l->head; ptr_l != NULL;
                ptr_l = ptr_l->next)

        if (ptr_l->lig == lig)
            return ptr_l;
    return NULL;
}

void remove_da_lista_lig(lista_lig l, pLigacao lig) { 

    node_lig ptr;

    if (l == NULL)
        return;

    for (ptr = l->head; ptr != NULL; ptr = ptr->next) 

        if (ptr->lig == lig) {

            /* se for o primeiro elemento a ser eliminado */
            if (ptr == l->head) {
                l->head = ptr->next;
                if (ptr->next != NULL)
                    ptr->next->previous = NULL;
                
                /* existindo apenas um elemento */
                else
                    l->last = NULL;
            }

            /* se for o ultimo elemento a ser eliminado */
            else if (ptr == l->last) {
                l->last = ptr->previous;
                l->last->next = NULL;
            }

            else {
                ptr->previous->next = ptr->next;
                if (ptr->next != NULL)
                    ptr->next->previous = ptr->previous;
            }

            free(ptr);
            break;
        }
}