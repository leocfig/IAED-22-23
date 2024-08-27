/* Ficheiro: carreira.c
Aluno: Leonor Costa Figueira
Nº de Aluno: 106157
Descricao: Ficheiro com funcoes de abstracao de carreiras */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tipos.h"
#include "util.h"
#include "carreira.h"


/* FUNCOES RELATIVAS A CARREIRAS */


/* Funcoes relacionadas a objetos e nodes de carreiras */


pCarreira novaCarr(char *nome) {
    pCarreira new = (pCarreira)malloc(sizeof(struct Carreira));
    if (new == NULL) no_memory();
    new->nome = strdup(nome);

    /* cria-se a lista das ligacoes que cada carreira tem */
    new->ptr_lista_lig = nova_lista_lig();
    new->nr_ligacoes = 0;

    return new;
}

void freeCarr(pCarreira c) {
    free(c->nome);
    free_list_lig(c->ptr_lista_lig);
    free(c);
}

node_carr newNode_carr(pCarreira c) {

    node_carr new = (node_carr)malloc(sizeof(struct node_carreira));
    if (new == NULL) no_memory();
    new->carr = c;
    new->next = NULL;
    return new;
}

/* Funcoes relacionadas a listas de carreiras */

lista_carr nova_lista_carr() {

    lista_carr c = (lista_carr)malloc(sizeof(struct listaCarr));
    if (c == NULL) no_memory();
    c->head = NULL;
    c->last = NULL;
    return c;
}

void free_list_carr(lista_carr c, int quero_eliminar) {

    node_carr ptr;
    if (c != NULL) {
        while (c->head != NULL) {
            ptr = c->head;
            c->head = c->head->next;

            /* se for necessario eliminar tambem a paragem em si */
            if (quero_eliminar)
                freeCarr(ptr->carr);
            
            free(ptr);
        }
        free(c);
    }
}

void insere_na_lista_carr(lista_carr c, pCarreira carr) {

    node_carr new = newNode_carr(carr);

    /* caso de ja' haver elemento(s) na lista */
    if (c->last != NULL)
        c->last->next = new;
    c->last = new;

    /* no caso de nao haver nenhum elemento na lista */
    if (c->head == NULL)
        c->head = new;
    
}

pCarreira procura_na_lista_carr(lista_carr c, char* nome) {

    node_carr ptr;

    if (c == NULL)
        return NULL;

    for (ptr = c->head; ptr != NULL; ptr = ptr->next) {

        if(strcmp(ptr->carr->nome, nome) == 0)
            return ptr->carr;
    }
    return NULL;
}

void remove_da_lista_carr(lista_carr c, char *nome) {

    node_carr ptr, prev;

    if (c == NULL)
        return;

    for (ptr = c->head, prev = NULL; ptr != NULL; prev = ptr, ptr = ptr->next)

        if (strcmp(ptr->carr->nome, nome) == 0) {

            /* se for o primeiro elemento a ser eliminado */
            if (ptr == c->head) {
                c->head = ptr->next;

                /* existindo apenas um elemento */
                if (ptr->next == NULL)
                    c->last = NULL;
            }

            /* se for o ultimo elemento a ser eliminado */
            else if (ptr == c->last) {
                c->last = prev;
                c->last->next = NULL;
            }

            else
                prev->next = ptr->next;

            free(ptr);
            break;
        }
}

void bubble_sort_str(lista_carr carr) {

    int done = 1;
    node_carr ptr, ptr_aux, ptr_last_swap = NULL;

    /* caso de a lista estar vazia */
    if (carr->head == NULL)
        return;

    for (ptr = carr->head; ptr != NULL; ptr = ptr->next) { 
        done = 1;
        
        for (ptr_aux = carr->head; ptr_aux->next != ptr_last_swap; 
            ptr_aux = ptr_aux->next)

            if (strcmp(ptr_aux->carr->nome, ptr_aux->next->carr->nome) > 0) {
                
                swap_node_inf(ptr_aux, ptr_aux->next);
                done = 0;
            }
        
        ptr_last_swap = ptr_aux;

        /* se nao foi feita nenhuma troca */
        if (done) break;
    }
}

void swap_node_inf(node_carr ptr_1, node_carr ptr_2) {
    
    pCarreira tmp = ptr_2->carr;
    ptr_2->carr = ptr_1->carr;
    ptr_1->carr = tmp;
}


/* Funcoes relacionadas com tabelas de dispersao de carreiras */


lista_carr *criarTabelaCarr(int DimTabelaCarr) {

    int i;
    lista_carr *tabela_carr = (lista_carr*)malloc(DimTabelaCarr *
                                                    sizeof(lista_carr));
    if (tabela_carr == NULL) no_memory();
    for (i = 0; i < DimTabelaCarr; i++) {
        tabela_carr[i] = nova_lista_carr();
    }
    return tabela_carr;
}

void insereNaTabela_carr(lista_carr *tabela_carr, pCarreira c, 
                            int DimTabelaCarr) {

    int indice = hash(c->nome, DimTabelaCarr);
    insere_na_lista_carr(tabela_carr[indice], c);
}

pCarreira procuraNaTabela_carr(lista_carr *tabela_carr, 
                                char *nome, int DimTabelaCarr) {

    int indice = hash(nome, DimTabelaCarr);
    return procura_na_lista_carr(tabela_carr[indice], nome);
}

void eliminaDaTabela_carr(lista_carr *tabela_carr, char *nome, 
                            int DimTabelaCarr) {

    int indice = hash(nome, DimTabelaCarr);
    remove_da_lista_carr(tabela_carr[indice], nome);
}