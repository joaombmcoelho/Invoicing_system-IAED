/**
 * Ficheiro com a implementacao das funcoes da estrutura Fatura
 * @file: proj_fatura.c
 * @author: ist1117964 (João Coelho)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proj_fatura.h"
#include "proj_produto.h"
#include "proj_constantes.h"
#include "proj_aux.h"

struct fatura{
    int nif;
    char *nome_cliente; 
    int numero_produtos;
    double valor_pago;
    int numero_fatura;
};

/* GETTERS */

int obtem_nif_ft(Fatura *fatura){
    return fatura->nif;
}

char *obtem_nome_ft(Fatura *fatura){
    return fatura -> nome_cliente;
}

int obtem_num_prod_ft(Fatura *fatura){
    return fatura->numero_produtos;
}

double obtem_valor_pago_ft(Fatura *fatura){
    return fatura->valor_pago;
}

int obtem_num_ft(Fatura *fatura){
    return fatura -> numero_fatura;
}

/* FUNCOES DA STRUCT FATURA */

Fatura* inicializa_fatura(int nif, char *nome, int num_prods, 
                                double valor_pago, int num_ft){
    /*abrir espaco para a fatura*/                                   
    Fatura *f = malloc(sizeof(Fatura));
    /*abrir espaco para o nome*/
    f->nome_cliente = (char *) malloc((strlen(nome) + 1) * sizeof(char));
    if (f->nome_cliente == NULL) {
        puts(ENOMEMORY);
        exit(1);
    }
    /*criar a fatura*/
    strcpy(f->nome_cliente, nome);
    f->nif = nif;
    f->numero_fatura = num_ft;
    f->numero_produtos = num_prods;
    f->valor_pago = valor_pago;

    return f;
}

int valida_ft(int um_arg, int *nif, int i, char *in, char *arg1, char *arg2){
    /*2 ARGUMENTOS*/
    if(!um_arg){
        if(!eh_numero(arg1)){
            printf("%s: no such nif\n", arg1);
            return FALSE;
        }
        /*Introduziu um número*/
        *nif = atoi(arg1);
        /*verificar se NIF é válido*/
        if (arg1[0] == '0' || strlen(arg1) != MAXNIF){
            printf("%s: no such nif\n", arg1);
            return FALSE;
        }
        /*LER O NOME*/ 
        i = ler_argumento (in, i, arg2);
        if (i == ERROR){ /*se nao fechou aspas*/
            puts(ENOMEINVALIDO);
            return FALSE;     
        }
    }
    /*validar o nome*/
    if(!eh_nome(arg2)){
        puts(ENOMEINVALIDO);
        return FALSE;
    }
    return TRUE;   
}

void imprime_fatura (Fatura *fatura){
    printf("%d %.2f %d\n",
        fatura->numero_produtos,
        fatura->valor_pago,
        fatura->numero_fatura);
}

int imprime_ft_cliente(Fatura **faturas, char *nome, int n_fts, int todas){
    int i, imprimiu = FALSE;
    for (i = 0; i < n_fts; i++ ){
        if (todas == TRUE){
            printf("%d %.2f %s\n", 
            faturas[i]->numero_fatura,
            faturas[i]->valor_pago,
            faturas[i]->nome_cliente);
            imprimiu = TRUE;
        }
        else{
            if(!strcmp(faturas[i]->nome_cliente, nome)){
            printf("%d %.2f %s\n", 
                faturas[i]->numero_fatura,
                faturas[i]->valor_pago,
                faturas[i]->nome_cliente);
                imprimiu = TRUE;
            }
        }
    }
    return imprimiu;
}

/**
 * Junta duas subsequencias ordenadas de faturas numa unica sequencia ordenada.
 * Esta funcao auxiliar do Merge Sort utiliza um array temporario para ordenar
 * e combinar os elementos entre os limites fornecidos.
 * @param faturas   vetor de faturas a ser ordenado.
 * @param aux   vetor auxiliar usado para guardar temp. os elementos.
 * @param esq   indice do limite esquerdo (inicio) da subsequencia a ordenar.
 * @param meio  indice final da 1a subsequencia (e divisao para a segunda).
 * @param dir indice do limite direito (fim) da segunda subsequencia a ordenar.
 */
static void combina(Fatura **faturas, Fatura **aux, int esq, int meio,int dir){
    int i, j, k;
    for (i = meio + 1; i > esq; i--)
        aux[i - 1] = faturas[i - 1];
    for (j = meio; j < dir; j++)
        aux[dir + meio - j] = faturas[j + 1];

    for (k = esq; k <= dir; k++){
        /*escolher elementos das pontas*/
        if((strcmp(aux[j]->nome_cliente, aux[i]->nome_cliente) < 0)||i==meio+1)
            faturas[k] = aux[j--];
        else
            faturas[k] = aux[i++];
    }
}

/**
 * ordena as faturas por ordem alfabetica e cronologica num vetor ah parte
 * usando o algoritmo de ordenacao Merge Sort.
 * @param out O vetor de elementos a ordenar
 * @param aux vetor auxiliar usado para guardar temp. os elementos.
 * @param esq O indice do limite esquerdo (inicio) da subsequencia a ordenar.
 * @param dir O indice do limite direito (fim) da subsequencia a ordenar.
 */
static void ordena_tds_faturas(Fatura **out, Fatura **aux, int esq, int dir){
    /*so preciso de ordenar por ordem alfabetica, pq, 
    como percorro por id, ja estao por ordem cronologica*/
    /*MERGE SORT*/
    int meio = (dir + esq) / 2;
    if (dir <= esq)
        return;
    ordena_tds_faturas(out, aux, esq, meio); /*metade esquerda*/
    ordena_tds_faturas(out, aux, meio + 1, dir); /*metade direita*/
    combina(out, aux, esq, meio, dir);
}

void imprime_tds_ft_ord(Fatura **faturas_in, int n_faturas){
    Fatura **aux; 
    Fatura **faturas_ord; 
    int i, todas = TRUE;

    if (n_faturas == 0)
        return;

    /*alocar memoria*/
    faturas_ord = (Fatura**) malloc(n_faturas *sizeof(Fatura *));
    aux = (Fatura**) malloc(n_faturas * sizeof(Fatura *));

    if (faturas_ord == NULL || aux == NULL) {
        puts(ENOMEMORY);
        exit(1);
    }

    /*copiar faturas para nao alterar ordem no original*/
    for (i = 0; i < n_faturas; i++)
        faturas_ord[i] = faturas_in[i];
    /*ordenar vetor copia*/
    ordena_tds_faturas(faturas_ord, aux, 0, (n_faturas -1));
    /*imprime todas as faturas*/
    if(!imprime_ft_cliente(faturas_ord, NULL, n_faturas, todas))
        return;
    free(faturas_ord);
    free(aux);
}

int obtem_pos_ft(Fatura **faturas, int n_faturas, int num){
    for (int i = 0; i < n_faturas; i++){
        if (obtem_num_ft(faturas[i]) == num)
            return i;
    }
    return ERROR;
}