/* Ficheiro: main.c
Aluno: Leonor Costa Figueira
Nº de Aluno: 106157
Descricao: Funcao Main Do Segundo Projeto de IAED */


#include "tipos.h"
#include "project2.h"
#include "util.h"

#define DIM_INSTRUCAO 65535  /* comprimento maximo da instrucao recebida */

#define DIMTABELAPAR  1000   /* comprimento maximo da tabela */
                             /* de dispersao das paragens    */
#define DIMTABELACARR 1000   /* comprimento maximo da tabela */
                             /* de dispersao das carreiras   */


int main () {

    char *instrucao = CriaVectorInstrucao(DIM_INSTRUCAO);

    lista_par *tabela_par;
    lista_carr *tabela_carr;
    lista_carr c;
    lista_par p;

    inic_sistema(&tabela_par, &tabela_carr, &p, &c, DIMTABELAPAR,
                 DIMTABELACARR);

    while (1) {
        leInstrucao(instrucao);

        switch (instrucao[0]) {
            
            /* instrucao mais 1 para descartar 
                o primeiro elemento ja' lido */
            case 'c':
                adiclist_carr(instrucao + 1, tabela_carr, c, DIMTABELACARR);
                break;

            case 'p':
                adiclist_par(instrucao + 1, tabela_par, p, DIMTABELAPAR);
                break;

            case 'l':
                adic_lig(instrucao + 1, tabela_carr, tabela_par, DIMTABELACARR,
                        DIMTABELAPAR);
                break;

            case 'i': lista_interacoes(p);
                break;

            case 'r':
                remove_carr(instrucao + 1, tabela_carr, c, DIMTABELACARR);
                break;
            
            case 'e': elimina_par(instrucao + 1, tabela_par, p, DIMTABELAPAR);
                break;
            
            case 'a':
                apaga_sistema(tabela_par, p, tabela_carr, c, DIMTABELAPAR,
                                DIMTABELACARR);
                
                inic_sistema(&tabela_par, &tabela_carr, &p, &c, DIMTABELAPAR,
                                DIMTABELACARR);
                break;
            
            case 'q':
                apaga_sistema(tabela_par, p, tabela_carr, c, DIMTABELAPAR,
                                DIMTABELACARR);
                free_instrucao(instrucao);
                return 0;
        }
    }
}
