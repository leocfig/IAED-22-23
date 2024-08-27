/* Ficheiro: project1.c
Aluno: Leonor Costa Figueira
Nº de Aluno: 106157
Descricao: Primeiro Projeto de IAED */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project1.h"


/* para guardar as carreiras, cria-se um vetor de estruturas */
struct Carreira carreiras[MAX_CARREIRAS];

/* para guardar as ligacoes, cria-se um vetor de estruturas */
struct Ligacao ligacoes[MAX_LIGACOES];

/* para guardar as paragens, cria-se um vetor de estruturas */
struct Paragem paragens[MAX_PARAGENS];


int main () {

    char c;
    int nr_carreiras = 0;
    int nr_ligacoes = 0;
    int nr_paragens = 0;

    while (1) {

        switch (c = getchar()) {

            case 'c': 
                adiclist_carr(carreiras, &nr_carreiras);
                break;

            case 'p':
                adiclist_par(paragens, &nr_paragens);
                break;

            case 'l':
                adic_lig(carreiras, paragens, &nr_carreiras,
                        &nr_paragens, &nr_ligacoes);
                break;

            case 'i':
                list_int(paragens, &nr_paragens);
                break;

            case 'q':
                return 0;
        }
    }
}


int leProximoParametro(char str[]) {

    int i = 0;
	char c;

    c = getchar();

	while (c == ' ' || c == '\t')
		c = getchar();

    if (c == '"') {
        
        c = getchar();

        while (c != '"') {
            str[i++] = c;
            c = getchar();
        }
        c = getchar();
        str[i] = '\0';
    }

    else {

        while (c != ' ' && c != '\t' && c != '\n') {
            str[i++] = c;
            c = getchar();
        }
        str[i] = '\0';
    }

    /* se nao foi introduzido nenhum parametro */
    if (i == 0 && c == '\n')
        return -1;

    /* se o parametro e' o ultimo do comando */
    else if (c == '\n')
        return 1;
    
    else
	    return 0;
}


void leParametros_lig(char carreira[], char nome_paragem_origem[], 
                        char nome_paragem_destino[], double *custo_dou,
                        double *duracao_dou) {

    char custo[CUSTO_DURACAO], duracao[CUSTO_DURACAO];

    leProximoParametro(carreira);
    leProximoParametro(nome_paragem_origem);
    leProximoParametro(nome_paragem_destino);
    leProximoParametro(custo);
    leProximoParametro(duracao);

    *custo_dou = atof(custo);
    *duracao_dou = atof(duracao);
}


void shift_direita(struct Ligacao *ligacoes[], int nr_ligacoes) {

    int i;

    for (i = nr_ligacoes - 1; i >= 0; i--)
        ligacoes[i+1] = ligacoes[i];
}


void bubble_sort_str(struct Carreira *todas_carreiras[], int nr_carreiras_par) {

    int i, j, done = 1;
    struct Carreira *aux;

    for (i = 0; i < nr_carreiras_par; i++) {

        for (j = 0; j < nr_carreiras_par - 1 - i; j++) 

            if (strcmp(todas_carreiras[j]->nome, 
                        todas_carreiras[j + 1]->nome) > 0) {

                /* trocar elemento[j] com elemento[j+1] */

                aux = todas_carreiras[j];
                todas_carreiras[j] = todas_carreiras[j+1];
                todas_carreiras[j+1] = aux;

                done = 0;
            }
        
        /* se nao fizemos nenhuma troca */
        if (done) break;
        done = 1;
    }
}


int carr_nao_existe(struct Carreira carreiras[], int *nr_carreiras_ptr,
                    char carreira[]) {

    int j;

    for (j = 0; j <= *nr_carreiras_ptr; j++) {
            
        if (strcmp(carreira, carreiras[j].nome) == 0) 
            return 0;
    }
    return 1;
}


void cria_carr(char carreira[], struct Carreira carreiras[], 
                int *nr_carreiras_ptr) {

    strcpy(carreiras[*nr_carreiras_ptr].nome, carreira);
    (*nr_carreiras_ptr)++;
}


void print_carr(struct Carreira carreiras[], int *nr_carreiras_ptr) {

    int i;

    for (i = 0; i < *nr_carreiras_ptr; i++) 

        if (carreiras[i].nr_ligacoes == 0)
            printf("%s %d %.2f %.2f\n", carreiras[i].nome,
                    carreiras[i].nr_ligacoes,
                    calc_custototal(carreiras[i].ligacoes, 
                                    carreiras[i].nr_ligacoes),
                    calc_durtotal(carreiras[i].ligacoes, 
                                carreiras[i].nr_ligacoes));

        else 
            printf("%s %s %s %d %.2f %.2f\n", carreiras[i].nome,
                    carreiras[i].ligacoes[0]->par_origem_ptr->nome, 
                    carreiras[i].ligacoes[carreiras[i].nr_ligacoes - 1]
                                            ->par_destino_ptr->nome,
                    carreiras[i].nr_ligacoes + 1,
                    calc_custototal(carreiras[i].ligacoes, 
                                    carreiras[i].nr_ligacoes),
                    calc_durtotal(carreiras[i].ligacoes, 
                                    carreiras[i].nr_ligacoes));
}


void print_par_carr(char carreira[], struct Carreira carreiras[], 
                    int *nr_carreiras_ptr) {

    int i, j;

    for (i = 0; i < *nr_carreiras_ptr; i++) {

        if (strcmp(carreira, carreiras[i].nome) == 0 && 
            carreiras[i].nr_ligacoes > 0) {

            /* imprime-se inicialmente a paragem de origem da carreira */
            printf("%s", carreiras[i].ligacoes[0]->par_origem_ptr->nome);

            /* de seguida, vao-se imprimindo as paragens de destino
            de cada ligacao */
            for (j = 0; j < carreiras[i].nr_ligacoes; j++)
                printf(", %s", carreiras[i].ligacoes[j]->par_destino_ptr->nome);

            putchar('\n');
        }
    }
}


void print_par_carr_inverso(char carreira[], struct Carreira carreiras[], 
                            int *nr_carreiras_ptr) {

    int i, j;

    for (i = 0; i < *nr_carreiras_ptr; i++) {

        if (strcmp(carreira, carreiras[i].nome) == 0) {

            /* imprime-se inicialmente a paragem de destino da carreira */
            printf("%s", carreiras[i].ligacoes[carreiras[i].nr_ligacoes - 1]
                                                ->par_destino_ptr->nome);

            /* de seguida, vao-se imprimindo as paragens de origem
            de cada ligacao */
            for (j = carreiras[i].nr_ligacoes - 1; j >= 0; j--) 
                printf(", %s", carreiras[i].ligacoes[j]->par_origem_ptr->nome);
            
            putchar('\n');
        }
    }
}


int par_nao_existe(struct Paragem paragens[], int *nr_paragens_ptr, 
                    char paragem[]) {

    int j; 

    for (j = 0; j < *nr_paragens_ptr; j++) {
            
        if (strcmp(paragem, paragens[j].nome) == 0) 
            return 0;
    }
    return 1;
}


void print_paragens(struct Paragem paragens[], int *nr_paragens_ptr) {

    int i;

    for (i = 0; i < *nr_paragens_ptr; i++) 

        printf("%s: %16.12f %16.12f %d\n", 
                paragens[i].nome, paragens[i].latitude,
                paragens[i].longitude, paragens[i].nr_carreiras_par);
}


struct Paragem *get_par(struct Paragem paragens[], char nome_paragem[], 
                        int *nr_paragens_ptr) {

    int j;

    for (j = 0; j < *nr_paragens_ptr; j++) {

        if (strcmp(nome_paragem, paragens[j].nome) == 0) 
            return &paragens[j];
    }
    return NULL;
}


void cria_par(char latitude[], char longitude[], char paragem[], 
                struct Paragem paragens[], int *nr_paragens_ptr) {

    double latitude_dou, longitude_dou;

    latitude_dou = atof(latitude);
    longitude_dou = atof(longitude);
    strcpy(paragens[*nr_paragens_ptr].nome, paragem);
    paragens[*nr_paragens_ptr].latitude = latitude_dou;
    paragens[*nr_paragens_ptr].longitude = longitude_dou;
    (*nr_paragens_ptr)++;
}


void adic_carr_par(struct Paragem *par_ptr, struct Carreira *carreira) {

    if (par_carr_nao_existe(carreira->nome, par_ptr->todas_carreiras, 
                            par_ptr->nr_carreiras_par)) {

        par_ptr->todas_carreiras[par_ptr->nr_carreiras_par] = carreira;
        par_ptr->nr_carreiras_par++;
    }
}


int cria_lig(struct Carreira *carreira, struct Ligacao ligacoes[],
                int *nr_ligacoes_ptr, struct Paragem *par_origem_ptr,
                struct Paragem *par_destino_ptr, char nome_paragem_origem[],
                char nome_paragem_destino[], double custo_dou, double duracao_dou) {
    
    struct Ligacao *ligacao;
    
    if (carreira->nr_ligacoes == 0) {

        carreira->ligacoes[0] = &ligacoes[(*nr_ligacoes_ptr)++];
        ligacao = carreira->ligacoes[0];
    }

    /* caso de o extremo de destino da carreira coincidir 
    com a paragem de origem da ligacao */
    else if (strcmp(nome_paragem_origem, carreira->
            ligacoes[carreira->nr_ligacoes - 1]->par_destino_ptr->nome) == 0) {

        /* para ocupar a primeira posicao livre no vetor das ligacoes */
        carreira->ligacoes[carreira->nr_ligacoes] = &ligacoes[(*nr_ligacoes_ptr)++];
        ligacao = carreira->ligacoes[carreira->nr_ligacoes];
    }
    
    /* caso de o extremo de origem da carreira coincidir
    com a paragem de destino da ligacao */
    else if (strcmp(nome_paragem_destino, carreira->ligacoes[0]
                                        ->par_origem_ptr->nome) == 0) {

        /* para colocar na primeira posicao*/
        shift_direita(carreira->ligacoes, carreira->nr_ligacoes);
        carreira->ligacoes[0] = &ligacoes[(*nr_ligacoes_ptr)++];
        ligacao = carreira->ligacoes[0];
    }

    else {
        printf("link cannot be associated with bus line.\n");
        return -1;
    }
    
    ligacao->par_origem_ptr = par_origem_ptr;
    adic_carr_par(par_origem_ptr, carreira);

    ligacao->par_destino_ptr = par_destino_ptr;
    adic_carr_par(par_destino_ptr, carreira);
    
    ligacao->custo = custo_dou;
    ligacao->duracao = duracao_dou;
    carreira->nr_ligacoes++;
    return 0;
}

void print_localizacao(struct Paragem paragens[], int *nr_paragens_ptr,
                        char paragem[]) {

    int j; 

    for (j = 0; j < *nr_paragens_ptr; j++) {
            
        if (strcmp(paragem, paragens[j].nome) == 0) 

            printf("%16.12f %16.12f\n", paragens[j].latitude, 
                                        paragens[j].longitude);
    }
}


int par_carr_nao_existe(char nome_carreira[], struct Carreira *todas_carreiras[],
                        int nr_carreiras_par) {

    int i;

    for (i = 0; i < nr_carreiras_par; i++) {

        if (strcmp(todas_carreiras[i]->nome, nome_carreira) == 0)
            return 0;
    }

    return 1;
}


double calc_custototal(struct Ligacao *ligacoes[], int nr_ligacoes) {

    int i;
    double custo_total = 0.0;
    for (i = 0; i < nr_ligacoes; i++) 
        custo_total += ligacoes[i]->custo;

    return custo_total;
}


double calc_durtotal(struct Ligacao *ligacoes[], int nr_ligacoes) {

    int i;
    double dur_total = 0.0;
    for (i = 0; i < nr_ligacoes; i++) 
        dur_total += ligacoes[i]->duracao;

    return dur_total;
}


void adiclist_carr(struct Carreira carreiras[], int *nr_carreiras_ptr) {

    char carreira[DIM_NOME_CARREIRA];
    char palavra[INVERSO];

    int res_carreira = leProximoParametro(carreira);

    /*  se o comando e' apenas composto pelo caracter c */
    if (res_carreira == -1) 
        print_carr(carreiras, nr_carreiras_ptr);
        
    /* se o comando inclui uma carreira */
    else if (res_carreira == 0 || res_carreira == 1) {

        if (carr_nao_existe(carreiras, nr_carreiras_ptr, carreira)) 
            cria_carr(carreira, carreiras, nr_carreiras_ptr);
        
        /* se a carreira introduzida existe */
        else

            /* se o parametro inverso nao foi introduzido */
            if (res_carreira == 1) 
                print_par_carr(carreira, carreiras, nr_carreiras_ptr);
            
            /* se o parametro inverso foi introduzido */
            else {
                
                leProximoParametro(palavra);

                /* se a palavra for inverso ou uma das suas abreviaturas */
                if (palavra[0] == 'i' && ((strstr("inverso", palavra)) != NULL)
                    && strlen(palavra) >= 3) 

                    print_par_carr_inverso(carreira, carreiras, nr_carreiras_ptr);
                
                else
                    printf("incorrect sort option.\n");
            }
    }
}


void adiclist_par (struct Paragem paragens[], int *nr_paragens_ptr) {

    char paragem[DIM_NOME_PARAGEM];
    char latitude[DIM_LATITUDE];
    char longitude[DIM_LONGITUDE];

    int res_paragem = leProximoParametro(paragem);

    /* o comando e' apenas composto pelo caracter p */
    if (res_paragem == -1) 
        print_paragens(paragens, nr_paragens_ptr);

    /* se o comando inclui o parametro da localizacao */
    else if (res_paragem == 0) {

        leProximoParametro(latitude);
        leProximoParametro(longitude);

        if (par_nao_existe(paragens, nr_paragens_ptr, paragem)) 
            cria_par(latitude, longitude, paragem, paragens, nr_paragens_ptr);
        
        /* se ja existir uma paragem com o mesmo nome */
        else
            printf("%s: stop already exists.\n", paragem);
    }
        
    /* se o comando nao incluir o parametro da localizacao */
    else if (res_paragem == 1) {
        
        if (par_nao_existe(paragens, nr_paragens_ptr, paragem))
            printf("%s: no such stop.\n", paragem);
        else
            print_localizacao(paragens, nr_paragens_ptr, paragem);
    }
}


void adic_lig(struct Carreira carreiras[], struct Paragem paragens[],
                int *nr_carreiras_ptr, int *nr_paragens_ptr,
                int *nr_ligacoes_ptr) {

    int i, nao_entra = 1;
    double custo_dou, duracao_dou;
    char carreira[DIM_NOME_CARREIRA];
    char nome_paragem_origem[DIM_NOME_PARAGEM];
    char nome_paragem_destino[DIM_NOME_PARAGEM];
    struct Paragem *par_origem_ptr = NULL, *par_destino_ptr = NULL;

    leParametros_lig(carreira, nome_paragem_origem, nome_paragem_destino,
                    &custo_dou, &duracao_dou);

    if (custo_dou < 0 || duracao_dou < 0) {
        printf("negative cost or duration.\n");
        return;
    }

    for (i = 0; i < *nr_carreiras_ptr; i++) {

        if (strcmp(carreira, carreiras[i].nome) == 0) {

            nao_entra = 0;

            par_origem_ptr = get_par(paragens, nome_paragem_origem, nr_paragens_ptr);
            par_destino_ptr = get_par(paragens, nome_paragem_destino, nr_paragens_ptr);

            if (par_origem_ptr == NULL) {
                printf("%s: no such stop.\n", nome_paragem_origem);
                break;
            }

            else if (par_destino_ptr == NULL) {
                printf("%s: no such stop.\n", nome_paragem_destino);
                break;
            }

            cria_lig(&carreiras[i], ligacoes, nr_ligacoes_ptr, par_origem_ptr,
                par_destino_ptr, nome_paragem_origem, nome_paragem_destino,
                custo_dou, duracao_dou);

            break;
        }
    }

    if (nao_entra)
        printf("%s: no such line.\n", carreira);
}


void list_int (struct Paragem paragens[], int *nr_paragens_ptr) {

    int i, j;

    for (i = 0; i < *nr_paragens_ptr; i++) {

        if (paragens[i].nr_carreiras_par > 1) {

            /* ordena-se por ordem alfabetica as 
            carreiras de uma determinada paragem */
            bubble_sort_str(paragens[i].todas_carreiras, 
                            paragens[i].nr_carreiras_par);
            printf("%s %d:", paragens[i].nome, paragens[i].nr_carreiras_par);

            for (j = 0; j < paragens[i].nr_carreiras_par; j++)

                printf(" %s", paragens[i].todas_carreiras[j]->nome);

            putchar('\n');
        }
    }
}


