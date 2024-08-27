/* Ficheiro: project1.h
Aluno: Leonor Costa Figueira
Nº de Aluno: 106157
Descricao: Ficheiro com constantes, estruturas e protótipos das funcoes */


#ifndef PROJECT1_H
#define PROJECT1_H


#define MAX_CARREIRAS     200    /* numero maximo de carreiras */
#define MAX_PARAGENS      10000  /* numero maximo de paragens */
#define MAX_LIGACOES      30000  /* numero maximo de ligacoes */

#define DIM_NOME_CARREIRA 21     /* comprimento maximo do nome da carreira */
#define DIM_NOME_PARAGEM  51     /* comprimento maximo do nome da paragem */
#define DIM_LATITUDE      17     /* comprimento maximo do parametro da latitude */
#define DIM_LONGITUDE     17     /* comprimento maximo do parametro da longitude */
#define INVERSO           8      /* comprimento maximo do parametro inverso */
#define CUSTO_DURACAO     11     /* comprimento maximo dos vetores dos valores do custo e duracao */



/* Tipos de Dados */


struct Paragem {

    char nome[DIM_NOME_PARAGEM];
    double localizacao;
    double latitude;
    double longitude;
    int nr_carreiras_par;

    /* cada paragem tem um vetor com todas as carreiras que passam pela mesma */
    struct Carreira *todas_carreiras[MAX_CARREIRAS];

};

struct Ligacao {

    struct Paragem *par_origem_ptr;
    struct Paragem *par_destino_ptr;
    double custo;
    double duracao;
    
};

struct Carreira {

    char nome[DIM_NOME_CARREIRA];
    int nr_ligacoes;

    /* para guardar as ligacoes, cria-se um vetor de ligacoes*/
    struct Ligacao *ligacoes[MAX_LIGACOES];

};



/* Funcoes */


/* funcao que le o proximo parametro existente no comando */
int leProximoParametro(char str[]);


/* funcao auxiliar que le os comandos da funcao "adic_lig" */
void leParametros_lig(char carreira[], char nome_paragem_origem[], 
                        char nome_paragem_destino[], double *custo_dou,
                        double *duracao_dou);


/* funcao que realiza um deslocamento de todos 
os elemetos uma unidade para a direita */
void shift_direita(struct Ligacao *ligacoes[], int nr_ligacoes);


/* funcao que ordena os elementos de um vetor alfabeticamente */
void bubble_sort_str(struct Carreira *todas_carreiras[], int nr_carreiras_par);


/* funcao que verifica se a carreira ainda nao e' existente */
int carr_nao_existe(struct Carreira carreiras[], int *nr_carreiras_ptr, 
                    char carreira[]);


/* funcao que cria uma nova carreira */
void cria_carr(char carreira[], struct Carreira carreiras[],
                int *nr_carreiras_ptr);


/* funcao que imprime as carreiras existentes */
void print_carr(struct Carreira carreiras[], int *nr_carreiras_ptr);


/* funcao que imprime as paragens de uma determinada carreira */
void print_par_carr(char carreira[], struct Carreira carreiras[],
                    int *nr_carreiras_ptr);


/* funcao que imprime as paragens de uma 
determinada carreia de forma invertida */
void print_par_carr_inverso(char carreira[], struct Carreira carreiras[],
                            int *nr_carreiras_ptr);


/* funcao que verifica se uma paragem ainda nao e' existente */
int par_nao_existe(struct Paragem paragens[], int *nr_paragens_ptr, 
                    char paragem[]);


/* funcao que imprime as paragens existentes */
void print_paragens(struct Paragem paragens[], int *nr_paragens_ptr);


/* funcao que devolve a paragem, caso exista*/
struct Paragem *get_par(struct Paragem paragens[], char nome_paragem[], 
                        int *nr_paragens_ptr);


/* funcao que cria uma nova paragem */
void cria_par(char latitude[], char longitude[], char paragem[], 
                struct Paragem paragens[], int *nr_paragens_ptr);


/* funcao que adiciona uma carreira no vetor de carreiras de uma paragem*/
void adic_carr_par(struct Paragem *par_ptr, struct Carreira *carreira);


/* funcao que cria uma ligacao */
int cria_lig(struct Carreira *carreira, struct Ligacao ligacoes[],
                int *nr_ligacoes_ptr, struct Paragem *par_origem_ptr,
                struct Paragem *par_destino_ptr, char nome_paragem_origem[],
                char nome_paragem_destino[], double custo_dou, double duracao_dou);


/* funcao que imprime os parametros de latitude e 
longitude de uma determinada paragem */
void print_localizacao(struct Paragem paragens[], int *nr_paragens_ptr, 
                        char paragem[]);


/* funcao que verifica se uma carreira ainda nao e' existente 
no vetor de carreiras de uma determinada paragem */
int par_carr_nao_existe(char nome_carreira[], struct Carreira *todas_carreiras[],
                        int nr_carreiras_par);


/* funcao que calcula o custo total de uma carreira */
double calc_custototal(struct Ligacao *ligacoes[], int nr_ligacoes);


/* funcao que calcula a duracao total de uma carreira */
double calc_durtotal(struct Ligacao *ligacoes[], int nr_ligacoes);


/* funcao que adiciona e lista as carreiras existentes no sistema */
void adiclist_carr(struct Carreira carreiras[], int *nr_carreiras_ptr);


/* funcao que adiciona e lista as paragens existentes no sistema */
void adiclist_par (struct Paragem paragens[], int *nr_paragens_ptr);


/* funcao que adiciona ligacoes */
void adic_lig(struct Carreira carreiras[], struct Paragem paragens[], 
                int *nr_carreiras_ptr, int *nr_paragens_ptr, 
                int *nr_ligacoes_ptr);


/* funcao que lista as intersecoes entre as carreiras */
void list_int (struct Paragem paragens[], int *nr_paragens_ptr);


#endif /* PROJECT1_H */
