/* Ficheiro: project2.h
Aluno: Leonor Costa Figueira
Nº de Aluno: 106157
Descricao: Ficheiro com constantes, estruturas e protótipos das funcoes */


#ifndef PROJECT2_H
#define PROJECT2_H

#include "util.h"
#include "paragem.h"
#include "ligacao.h"
#include "carreira.h"

#define TRUE          1      /* verdadeiro */
#define FALSE         0      /* falso */


/* Funcoes do projeto numero 2: */


                        /* FUNCOES AUXILIARES */


/* Funcao que inicializa o sistema */

/* e' inicializado o sistema: as listas das paragens e das carreiras sao
criadas, assim como as tabelas de dispersao das paragens e das carreiras */
void inic_sistema(lista_par **tabela_par, lista_carr **tabela_carr,
                    lista_par *p, lista_carr *c, int dim_tabela_par,
                    int dim_tabela_carr);

 
/* Funcao de leitura de dados de input no comando de adicionar ligacoes */

/* funcao auxiliar que le os comandos da funcao "adic_lig" */
void leParametros_lig(char *instrucao, char **carreira,
                    char **nome_paragem_origem, char **nome_paragem_destino,
                    double *custo_dou, double *duracao_dou);


/* Funcoes auxliares relativas a carreiras */

/* funcao que cria uma nova carreira */
void cria_carr(lista_carr *tabela_carr, lista_carr c, char *carreira, 
                int DimTabelaCarr);

/* funcao que verifica se a carreira nao e' existente */
int carr_nao_existe(lista_carr *tabela_carr, char *carreira,
                    int DimTabelaCarr);

/* funcao que imprime as carreiras existentes */
void print_carr(lista_carr c);

/* funcao que imprime as paragens de uma determinada carreira */
void print_par_carr(char *carreira, lista_carr *tabela_carr, 
                    int DimTabelaCarr);

/* funcao que imprime as paragens de uma 
determinada carreia de forma invertida */
void print_par_carr_inverso(char *carreira, lista_carr *tabela_carr, 
                            int DimTabelaCarr);

/* funcao que calcula o custo total de uma carreira */
double calc_custototal(lista_lig l);

/* funcao que calcula a duracao total de uma carreira */
double calc_durtotal(lista_lig l);


/* Funcoes auxliares relativas a paragens */

/* funcao que cria uma nova paragem */
void cria_par(char *latitude, char *longitude, char *paragem,
                lista_par *tabela_par, lista_par p, int DimTabelaPar);

/* funcao que verifica se uma paragem nao e' existente */
int par_nao_existe(lista_par *tabela_par, char *paragem, int DimTabelaPar);

/* funcao que imprime as paragens existentes */
void print_paragens(lista_par p);

/* funcao que imprime os parametros de latitude e 
longitude de uma determinada paragem */
void print_localizacao(lista_par *tabela_par, char *paragem, 
                        int DimTabelaPar);

/* funcao que adiciona uma carreira na lista de carreiras de uma paragem*/
void adic_carr_par(lista_par *tabela_par, char *paragem,
                    pCarreira carr, int DimTabelaPar);

/* funcao que remove a carreira da lista
de carreiras das paragens dessa carreira */
void remove_carr_paragens(pCarreira carr, char *carreira);

/* funcao que verifica se uma carreira nao e' existente 
na lista de carreiras de uma determinada paragem */
int par_carr_nao_existe(lista_carr carreiras, char *carreira);


/* Funcoes auxliares relativas a ligacoes */

/* funcao que cria uma ligacao */
void cria_lig(pCarreira carr, lista_par *tabela_par, int DimTabelaPar,
                pParagem par_origem_ptr, pParagem par_destino_ptr,
                double custo_dou, double duracao_dou);

/* funcao que remove uma ligacao do sistema */
void remove_lig(pParagem par, pLigacao lig, node_carr ptr_c);

/* funcao que elimina uma ligacao do extremo de uma carreira */
void elimina_lig_ext(pParagem par, pLigacao lig, node_carr ptr_c);

/* funcao que elimina uma ligacao do meio de uma carreira */
void elimina_lig_nao_ext(pLigacao lig, node_carr ptr_c);



                        /* FUNCOES PRINCIPAIS */


/* funcao que adiciona e lista as carreiras existentes no sistema */
void adiclist_carr(char *instrucao, lista_carr *tabela_carr, lista_carr c,
                    int DimTabelaCarr);

/* funcao que adiciona e lista as paragens existentes no sistema */
void adiclist_par (char *instrucao, lista_par *tabela_par, lista_par p,
                    int DimTabelaPar);

/* funcao que adiciona ligacoes */
void adic_lig(char *instrucao, lista_carr *tabela_carr, lista_par *tabela_par,
                int DimTabelaCarr, int DimTabelaPar);

/* funcao que lista as intersecoes entre as carreiras */
void lista_interacoes(lista_par p);

/* funcao que remove uma carreira do sistema */
void remove_carr(char *instrucao, lista_carr *tabela_carr, lista_carr c,
                    int DimTabelaCarr);

/* funcao que remove uma paragem do sistema */
void elimina_par(char *instrucao, lista_par *tabela_par, lista_par p,
                    int DimTabelaPar);

/* funcao que apaga todos os dados do sistema */
void apaga_sistema(lista_par *tabela_par, lista_par p, 
                    lista_carr *tabela_carr, lista_carr c,
                    int DimTabelaPar, int DimTabelaCarr);


#endif /* PROJECT2_H */