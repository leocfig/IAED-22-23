/* Ficheiro: project2.c
Aluno: Leonor Costa Figueira
Nº de Aluno: 106157
Descricao: Segundo Projeto de IAED */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project2.h"
#include "tipos.h"
#include "util.h"
#include "paragem.h"
#include "ligacao.h"
#include "carreira.h"


/* Funcoes do projeto numero 2: */


                        /* FUNCOES AUXILIARES */


/* Funcao que inicializa o sistema */

void inic_sistema(lista_par **tabela_par, lista_carr **tabela_carr,
                    lista_par *p, lista_carr *c, int dim_tabela_par,
                    int dim_tabela_carr) {
    
    /* sao inicializadas as tabelas de dispersao das paragens e das carreiras*/
    *tabela_par = criarTabelaPar(dim_tabela_par);
    *tabela_carr = criarTabelaCarr(dim_tabela_carr);

    /* sao inicializadas as listas de paragens e de carreiras */
    *p = nova_lista_par();
    *c = nova_lista_carr();
}


/* Funcao de leitura de dados de input no comando de adicionar ligacoes */

void leParametros_lig(char *instrucao, char **carreira,
                    char **nome_paragem_origem, char **nome_paragem_destino,
                    double *custo_dou, double *duracao_dou) {

    char *custo, *duracao;

    lePalavra(&instrucao, carreira);
    lePalavra(&instrucao, nome_paragem_origem);
    lePalavra(&instrucao, nome_paragem_destino);
    lePalavra(&instrucao, &custo);
    lePalavra(&instrucao, &duracao);

    *custo_dou = atof(custo);
    *duracao_dou = atof(duracao);

    free_palavra(custo);
    free_palavra(duracao);
}


/* Funcoes auxliares relativas a carreiras */

void cria_carr(lista_carr *tabela_carr, lista_carr c, char *carreira, 
                int dim_tabela_carr) {

    pCarreira nova_carr = novaCarr(carreira);
    insereNaTabela_carr(tabela_carr, nova_carr, dim_tabela_carr);
    insere_na_lista_carr(c, nova_carr);
}


int carr_nao_existe(lista_carr *tabela_carr, char *carreira,
                    int dim_tabela_carr) {

    return procuraNaTabela_carr(tabela_carr, carreira,
                                dim_tabela_carr) == NULL;
}


void print_carr(lista_carr c) {

    node_carr ptr;

    for (ptr = c->head; ptr != NULL; ptr = ptr->next) 

        if (ptr->carr->nr_ligacoes == 0)
            printf("%s %d %.2f %.2f\n", ptr->carr->nome,
                    ptr->carr->nr_ligacoes,
                    calc_custototal(ptr->carr->ptr_lista_lig),
                    calc_durtotal(ptr->carr->ptr_lista_lig));

        else {
            printf("%s %s %s %d %.2f %.2f\n", ptr->carr->nome,
                    ptr->carr->ptr_lista_lig->head->lig->par_origem_ptr->nome,
                    ptr->carr->ptr_lista_lig->last->lig->par_destino_ptr->nome,
                    ptr->carr->nr_ligacoes + 1,
                    calc_custototal(ptr->carr->ptr_lista_lig),
                    calc_durtotal(ptr->carr->ptr_lista_lig));
        }
}


void print_par_carr(char *carreira, lista_carr *tabela_carr, 
                    int dim_tabela_carr) {

    node_lig ptr;
    pCarreira carr = procuraNaTabela_carr(tabela_carr, carreira,
                                            dim_tabela_carr);

    if (carr != NULL && carr->nr_ligacoes > 0) {

        /* imprime-se inicialmente a paragem de origem da carreira */
        printf("%s", carr->ptr_lista_lig->head->lig->par_origem_ptr->nome);

        /* de seguida, vao-se imprimindo as paragens de destino
        de cada ligacao */
        for (ptr = carr->ptr_lista_lig->head; ptr != NULL; ptr = ptr->next)
        
            printf(", %s", ptr->lig->par_destino_ptr->nome);

        putchar('\n');
    }
}


void print_par_carr_inverso(char *carreira, lista_carr *tabela_carr, 
                            int dim_tabela_carr) {

    node_lig ptr;
    pCarreira carr = procuraNaTabela_carr(tabela_carr, carreira,
                                            dim_tabela_carr);

    if (carr != NULL && carr->nr_ligacoes > 0) {

        /* imprime-se inicialmente a paragem de destino da carreira */
        printf("%s", carr->ptr_lista_lig->last->lig->par_destino_ptr->nome);

        /* de seguida, vao-se imprimindo as paragens de origem
        de cada ligacao */
        for (ptr = carr->ptr_lista_lig->last; ptr->previous != NULL; 
            ptr = ptr->previous)

            printf(", %s", ptr->lig->par_origem_ptr->nome);
        
        putchar('\n');
    }
}


double calc_custototal(lista_lig l) {

    node_lig ptr;
    double custo_total = 0.0;
    for (ptr = l->head; ptr != NULL; ptr = ptr->next)
        custo_total += ptr->lig->custo;

    return custo_total;
}


double calc_durtotal(lista_lig l) {

    node_lig ptr;
    double dur_total = 0.0;
    for (ptr = l->head; ptr != NULL; ptr = ptr->next)
        dur_total += ptr->lig->duracao;

    return dur_total;
}


/* Funcoes auxliares relativas a paragens */

void cria_par(char *latitude, char *longitude, char *paragem,
                lista_par *tabela_par, lista_par p, int dim_tabela_par) {

    double latitude_dou = atof(latitude);
    double longitude_dou = atof(longitude);

    pParagem nova_par = novaPar(paragem, latitude_dou, longitude_dou);
    insereNaTabela_par(tabela_par, nova_par, dim_tabela_par);
    insere_na_lista_par(p, nova_par);
}


int par_nao_existe(lista_par *tabela_par, char *paragem, int dim_tabela_par) {

    return procuraNaTabela_par(tabela_par, paragem, dim_tabela_par) == NULL;
}


void print_paragens(lista_par p) {

    node_par ptr;

    for (ptr = p->head; ptr != NULL; ptr = ptr->next) 

        printf("%s: %16.12f %16.12f %d\n",
                ptr->par->nome, ptr->par->latitude,
                ptr->par->longitude, ptr->par->nr_carreiras_par);
}


void print_localizacao(lista_par *tabela_par, char *paragem, 
                        int dim_tabela_par) {

    pParagem p = procuraNaTabela_par(tabela_par, paragem, dim_tabela_par);

    printf("%16.12f %16.12f\n", p->latitude, p->longitude);
}


void adic_carr_par(lista_par *tabela_par, char *paragem,
                    pCarreira carr, int dim_tabela_par) {

    pParagem p = procuraNaTabela_par(tabela_par, paragem, dim_tabela_par);

    if (par_carr_nao_existe(p->ptr_carr_par, carr->nome)) {

        insere_na_lista_carr(p->ptr_carr_par, carr);
        p->nr_carreiras_par++;
    }
}


void remove_carr_paragens(pCarreira carr, char *carreira) {

    node_lig ptr;
        
    /* vai-se percorrendo todas as paragens da determinada
    carreira, e em cada paragem elimina-se a carreira da 
    lista de carreiras que passam na paragem */
    
    /* comecando pela paragem de origem, ve-se se a
    carreira existe na lista de carreiras da paragem */
    if (procura_na_lista_carr(carr->ptr_lista_lig->head->lig
                        ->par_origem_ptr->ptr_carr_par, carreira) != NULL){

        remove_da_lista_carr(carr->ptr_lista_lig->head->lig->par_origem_ptr
                            ->ptr_carr_par, carreira);
        carr->ptr_lista_lig->head->lig->par_origem_ptr->nr_carreiras_par--;
    }

    /* e de seguida percorre-se o resto das paragens */
    for (ptr = carr->ptr_lista_lig->head; ptr != NULL; ptr = ptr->next) {
        
        if (procura_na_lista_carr(ptr->lig->par_destino_ptr->ptr_carr_par,
                        carreira) != NULL) {
                        
            remove_da_lista_carr(ptr->lig->par_destino_ptr->ptr_carr_par,
                                carreira);
            ptr->lig->par_destino_ptr->nr_carreiras_par--;
        }
    }
}


int par_carr_nao_existe(lista_carr carreiras, char *carreira) {

    return procura_na_lista_carr(carreiras, carreira) == NULL;
}


/* Funcoes auxliares relativas a ligacoes */

void cria_lig(pCarreira carr, lista_par *tabela_par, int dim_tabela_par,
                pParagem par_origem_ptr, pParagem par_destino_ptr,
                double custo_dou, double duracao_dou) {
    
    pLigacao nova_lig = novaLig(par_origem_ptr, par_destino_ptr, custo_dou,
                                duracao_dou);

    /* caso de nao existirem ainda ligacoes ou o extremo de destino da
    carreira coincidir com a paragem de origem da ligacao */
    if (carr->nr_ligacoes == 0 ||
        par_origem_ptr == carr->ptr_lista_lig->last->lig->par_destino_ptr)
        
        /* para colocar na ultima posicao na lista das ligacoes */
        insere_na_lista_lig(carr->ptr_lista_lig, nova_lig);
    
    /* caso de o extremo de origem da carreira coincidir
    com a paragem de destino da ligacao */
    else if (par_destino_ptr == carr->ptr_lista_lig->head->lig
                                            ->par_origem_ptr)

        /* para colocar na primeira posicao na lista das ligacoes */
        insere_na_lista_lig_inicio(carr->ptr_lista_lig, nova_lig);

    else {
        printf("link cannot be associated with bus line.\n");
        return;
    }
    
    adic_carr_par(tabela_par, par_origem_ptr->nome, carr, dim_tabela_par);
    adic_carr_par(tabela_par, par_destino_ptr->nome, carr, dim_tabela_par);
    carr->nr_ligacoes++;
}


void remove_lig(pParagem par, pLigacao lig, node_carr ptr_c) {

    /* se a paragem a eliminar e' dos extremos da carreira */
    if ((lig == ptr_c->carr->ptr_lista_lig->head->lig && par ==
        ptr_c->carr->ptr_lista_lig->head->lig->par_origem_ptr) ||
        (lig == ptr_c->carr->ptr_lista_lig->last->lig && par ==
        ptr_c->carr->ptr_lista_lig->last->lig->par_destino_ptr)) 
        
        elimina_lig_ext(par, lig, ptr_c);
    
    /* se a paragem a eliminar nao e' dos extremos da carreira */
    else
        elimina_lig_nao_ext(lig, ptr_c);
    
    ptr_c->carr->nr_ligacoes--;
}


void elimina_lig_ext(pParagem par, pLigacao lig, node_carr ptr_c) {

    int eh_par_origem;

    if (ptr_c->carr->nr_ligacoes == 1) {
                        
        /* ve-se se a paragem a eliminar e' a 
        de origem na ligacao onde se encontra */
        eh_par_origem = (lig->par_origem_ptr ==
                        par) ? 1 : 0;

        /* remover a carreira da lista de carreiras da paragem
        que nao vai ser eliminada */

        /* se a paragem a eliminar e' da origem da ligacao */
        if (eh_par_origem && par != lig->par_destino_ptr) {
            remove_da_lista_carr(lig->par_destino_ptr
                            ->ptr_carr_par, ptr_c->carr->nome);
            lig->par_destino_ptr->nr_carreiras_par--;
        }

        else if (!eh_par_origem && par != lig->par_origem_ptr) {
            
            remove_da_lista_carr(lig->par_origem_ptr
                            ->ptr_carr_par, ptr_c->carr->nome);
            lig->par_origem_ptr->nr_carreiras_par--;
        }
    }
    /* remove-se a ligacao da lista de ligacoes da carreira */
    remove_da_lista_lig(ptr_c->carr->ptr_lista_lig, lig);
    freeLig(lig);
}


void elimina_lig_nao_ext(pLigacao lig, node_carr ptr_c) {

    node_lig ptr_l;
    pLigacao tmp_lig;

    ptr_l = getnode_Lig(ptr_c->carr->ptr_lista_lig, lig);

    /* a paragem de destino da ligacao passa a ser
    igual 'a paragem de destino da proxima ligacao */
    ptr_l->lig->par_destino_ptr =
    ptr_l->next->lig->par_destino_ptr;

    /* soma-se ao custo e duracao da ligacao o custo e duracao da ligacao 
    seguinte, para depois eliminar a ligacao seguinte */
    ptr_l->lig->custo += ptr_l->next->lig->custo;
    ptr_l->lig->duracao += ptr_l->next->lig->duracao;

    tmp_lig = ptr_l->next->lig;
    /* remove-se a proxima ligacao da
    lista de ligacoes da carreira*/
    remove_da_lista_lig(ptr_c->carr->ptr_lista_lig,
                    ptr_l->next->lig);
    freeLig(tmp_lig);
}



                        /* FUNCOES PRINCIPAIS */


void adiclist_carr(char *instrucao, lista_carr *tabela_carr, lista_carr c,
                    int dim_tabela_carr) {

    char *carreira , *palavra;

    /* para alterar o valor do ponteiro instrucao,
    para este avancar depois de ler a palavra */
    int shift = lePalavra(&instrucao, &carreira);

    /*  se o comando e' apenas composto pelo caracter c */
    if (shift == 0) {
        print_carr(c);
        return;
    }
        
    /* se o comando inclui uma carreira e esta nao existe */
    if (carr_nao_existe(tabela_carr, carreira, dim_tabela_carr)) {
        cria_carr(tabela_carr, c, carreira, dim_tabela_carr);
        free_palavra(carreira);
        return;
    }
    
    /* se a carreira introduzida existe, le-se o proximo parametro */
    shift = lePalavra(&instrucao, &palavra);

    /* se o parametro inverso nao foi introduzido */
    if (shift == 0) 
        print_par_carr(carreira, tabela_carr, dim_tabela_carr);
    
    /* se o parametro inverso foi introduzido */
    else {
        
        /* se a palavra for inverso ou uma das suas abreviaturas */
        if (palavra[0] == 'i' && ((strstr("inverso", palavra)) != NULL)
            && strlen(palavra) >= 3) 

            print_par_carr_inverso(carreira, tabela_carr, dim_tabela_carr);
        
        else
            printf("incorrect sort option.\n");

        free_palavra(palavra);
    }
    free_palavra(carreira);
}


void adiclist_par (char *instrucao, lista_par *tabela_par, lista_par p,
                    int dim_tabela_par) {

    char *paragem, *latitude, *longitude;

    int shift = lePalavra(&instrucao, &paragem);

    /* o comando e' apenas composto pelo caracter p */
    if (shift == 0) {
        print_paragens(p);
        return;
    }

    /* o comando inclui uma paragem, le-se os proximos parametros */

    shift = lePalavra(&instrucao, &latitude);
    shift = lePalavra(&instrucao, &longitude);

    /* se o comando nao incluir o parametro da localizacao */
    if (shift == 0) {
        if (par_nao_existe(tabela_par, paragem, dim_tabela_par))
            printf("%s: no such stop.\n", paragem);
        else
            print_localizacao(tabela_par, paragem, dim_tabela_par);
    }

    /* se o comando incluir o parametro da localizacao */
    else {
        if (par_nao_existe(tabela_par, paragem, dim_tabela_par)) 
            cria_par(latitude, longitude, paragem, tabela_par, p,
                    dim_tabela_par);
    
        /* se ja existir uma paragem com o mesmo nome */
        else
            printf("%s: stop already exists.\n", paragem);

        free_palavra(latitude);
        free_palavra(longitude);
    }
    free_palavra(paragem);
}


void adic_lig(char *instrucao, lista_carr *tabela_carr, lista_par *tabela_par,
                int dim_tabela_carr, int dim_tabela_par) {

    double custo_dou, duracao_dou;
    char *carreira, *nome_paragem_origem, *nome_paragem_destino;
    pCarreira carr;

    pParagem par_origem_ptr, par_destino_ptr;

    leParametros_lig(instrucao, &carreira, &nome_paragem_origem,
                    &nome_paragem_destino, &custo_dou, &duracao_dou);

    /* obtem-se a carreira onde se vai adicionar a ligacao */
    carr = procuraNaTabela_carr(tabela_carr, carreira, dim_tabela_carr);

    if (custo_dou < 0 || duracao_dou < 0) 
        printf("negative cost or duration.\n");
    
    else if (carr != NULL) {

        /* obtem-se as paragens de origem e destino da ligacao a adicionar */
        par_origem_ptr = procuraNaTabela_par(tabela_par, nome_paragem_origem,
                                            dim_tabela_par);
        par_destino_ptr = procuraNaTabela_par(tabela_par, nome_paragem_destino,
                                            dim_tabela_par);

        if (par_origem_ptr == NULL) 
            printf("%s: no such stop.\n", nome_paragem_origem);
        
        else if (par_destino_ptr == NULL) 
            printf("%s: no such stop.\n", nome_paragem_destino);

        else cria_lig(carr, tabela_par, dim_tabela_par, par_origem_ptr, 
                    par_destino_ptr, custo_dou, duracao_dou);
    }
    else
        printf("%s: no such line.\n", carreira);

    free_palavra(carreira);
    free_palavra(nome_paragem_origem);
    free_palavra(nome_paragem_destino);
}


void lista_interacoes(lista_par p) {

    node_par ptr_par;
    node_carr ptr_carr;

    for (ptr_par = p->head; ptr_par != NULL; ptr_par = ptr_par->next) 

        /* se passa mais do que uma carreira na determinada paragem */
        if (ptr_par->par->nr_carreiras_par > 1) {

            /* ordena-se por ordem alfabetica as 
            carreiras da determinada paragem */
            bubble_sort_str(ptr_par->par->ptr_carr_par);

            printf("%s %d:", ptr_par->par->nome,
                            ptr_par->par->nr_carreiras_par);
            
            /* imprimem-se as carreiras da lista de carreiras da paragem */
            for (ptr_carr = ptr_par->par->ptr_carr_par->head; ptr_carr != NULL;
                ptr_carr = ptr_carr->next)

                printf(" %s", ptr_carr->carr->nome);

            putchar('\n');
        }
}


void remove_carr(char *instrucao, lista_carr *tabela_carr, lista_carr c,
                    int dim_tabela_carr) {

    char *carreira;
    pCarreira carr;
    
    lePalavra(&instrucao, &carreira);
    carr = procuraNaTabela_carr(tabela_carr, carreira, dim_tabela_carr);

    if (carr == NULL) {
        printf("%s: no such line.\n", carreira);
        free_palavra(carreira);
        return;
    }

    if (carr->nr_ligacoes > 0) 

        /* remove-se a carreira da lista de carreiras
        de todas as paragens da carreira a eliminar */
        remove_carr_paragens(carr, carreira);

    eliminaDaTabela_carr(tabela_carr, carreira, dim_tabela_carr);

    /* remove-se a carreira da lista de carreiras existente */
    remove_da_lista_carr(c, carreira);

    freeCarr(carr);

    free_palavra(carreira);
}
    

void elimina_par(char *instrucao, lista_par *tabela_par, lista_par p,
                    int dim_tabela_par) {
    
    char *paragem;
    node_carr ptr_c;
    pParagem par;
    pLigacao lig;

    lePalavra(&instrucao, &paragem);
    par = procuraNaTabela_par(tabela_par, paragem, dim_tabela_par);

    if (par == NULL) {
        printf("%s: no such stop.\n", paragem);
        free_palavra(paragem);
        return;
    }

    if (par->nr_carreiras_par > 0) {

        /* percorre-se as carreiras com a paragem que vai ser eliminada,
        isto e', percorre-se a lista de carreiras da paragem */
        for (ptr_c = par->ptr_carr_par->head; ptr_c != NULL; 
            ptr_c = ptr_c->next) {
            
            /* obtem-se a ligacao dessa carreira onde esta' a paragem */
            lig = procura_na_lista_lig(ptr_c->carr->ptr_lista_lig, par->nome);

            while (lig != NULL) {

                /* a ligacao da carreira com a paragem e' apagada do sistema */
                remove_lig(par, lig, ptr_c);

                /* volta-se a obter uma ligacao com a paragem,
                caso existam paragens iguais na carreira */
                lig = procura_na_lista_lig(ptr_c->carr->ptr_lista_lig,
                                            par->nome);
            }
        }
    }

    eliminaDaTabela_par(tabela_par, paragem, dim_tabela_par);

    /* remove-se a paragem da lista de paragens existente */
    remove_da_lista_par(p, paragem);
    freePar(par);

    free_palavra(paragem);
}


void apaga_sistema(lista_par *tabela_par, lista_par p, 
                    lista_carr *tabela_carr, lista_carr c,
                    int dim_tabela_par, int dim_tabela_carr) {
    
    int i;

    /* elimina-se cada lista da tabela de dispersao de paragens */
    for (i = 0; i < dim_tabela_par; i++)

        /*"TRUE", porque alem da lista e respetivos nodes,
        e' tambem para eliminar as paragens em si */
        free_list_par(tabela_par[i], TRUE);
    
    /* eliminacao da tabela de dispersao de paragens */
    free(tabela_par); 

    /* elimina-se cada lista da tabela de dispersao de carreiras */
    for (i = 0; i < dim_tabela_carr; i++)

        /*"TRUE", porque alem da lista e dos respetivos nodes,
        e' tambem para eliminar as carreiras em si */
        free_list_carr(tabela_carr[i], TRUE);

    /* eliminacao da tabela de dispersao de carreiras */
    free(tabela_carr); 

    /* elimina-se apenas as listas e os respetivos nodes */
    free_list_par(p, FALSE);
    free_list_carr(c, FALSE);
}
