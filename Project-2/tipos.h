/* Ficheiro: tipos.h
Aluno: Leonor Costa Figueira
Nº de Aluno: 106157
Descricao: Ficheiro com estruturas das paragens, ligacoes e carreiras */

#ifndef TIPOS_H
#define TIPOS_H


/* ESTRUTURAS */

typedef struct listaCarr *lista_carr;
typedef struct listaLig *lista_lig;
typedef struct listaPar *lista_par;


/* ESTRUTURAS DE PARAGENS */

typedef struct Paragem {

    char *nome;
    double latitude;
    double longitude;
    int nr_carreiras_par;

    /* cada paragem tem uma lista com todas 
    as carreiras que passam pela mesma */
    lista_carr ptr_carr_par;

} *pParagem;

typedef struct node_paragem {
    pParagem par;
    struct node_paragem *next;
} *node_par;

struct listaPar {
    struct node_paragem *head, *last;
};


/* ESTRUTURAS DE LIGACOES */

typedef struct Ligacao {

    pParagem par_origem_ptr;
    pParagem par_destino_ptr;
    double custo;
    double duracao;
    
} *pLigacao;

typedef struct node_ligacao {
    pLigacao lig;
    struct node_ligacao *next, *previous;
} *node_lig;

struct listaLig {
    struct node_ligacao *head, *last;
};


/* ESTRUTURAS DE CARREIRAS */

typedef struct Carreira {

    char *nome;
    int nr_ligacoes;

    /* cada carreira tem uma lista com todas as ligacoes da mesma */
    lista_lig ptr_lista_lig;

} *pCarreira;

typedef struct node_carreira {
    pCarreira carr;
    struct node_carreira *next;
} *node_carr;

struct listaCarr {
    struct node_carreira *head, *last;
};


#endif /* TIPOS_H */
