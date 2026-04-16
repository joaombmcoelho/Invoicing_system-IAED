/**
 * Ficheiro com a implementacao das funcoes auxiliares usadas em todo o projeto
 * @file: proj_aux.c
 * @author: ist1117964 (João Coelho)
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h> 
#include "proj_aux.h"
#include "proj_constantes.h"

int eh_letra(unsigned char c){ /*forma de validar acentuadas*/
    if(isalpha(c))
        return TRUE;
    /*maiusculas latinas ASCII (À até Þ)*/
    if(c >= MENORMAIUSCULA && c <= MAIORMAIUSCULA)
        return TRUE;
    /*minusculas latinas ASCII (ß até þ)*/
    if(c >= MENORMINUSCULA && c <= MAIORMINUSCULA)
        return TRUE;
    return FALSE;
}

int eh_maisucula(unsigned char c){
    if(c >= 'A' && c <= 'Z')
        return TRUE;
    if(c >= MENORMAIUSCULA && c <= MAIORMAIUSCULA)
        return TRUE;
    return FALSE;
}

int eh_numero(char *caracteres){
    int i = 0;
    while (caracteres[i] != '\0'){
        if(caracteres[i] < '0' || caracteres[i] > '9')
            return FALSE;
        i++;
    }
    return TRUE;
}

int eh_nome(char *nome){
    int i = 0;
    /*um nome tem de comecar por uma letra*/
    if (!eh_letra(nome[i]))
        return FALSE;
    return TRUE;
}

int eh_fim_input(char *in, int i){
    if (in[i] == '\0' || in[i] == '\n')
        return TRUE;
    return FALSE;
}

/** 
 * Verifica se um ean de tamanho valido eh um ean pelo digito de controlo.
 * @param ean    ean
 * @param tamanho_ean   tamanho do ean (8 ou 13)
 * @return  devolve TRUE se o ultimo digito corresponde e FALSE caso contrario
 */
static int verifica_digito_controlo (char *ean, int tamanho_ean){
    int i = 0, ultimo_digito;
    int soma = 0;

    /* somar os numeros pares */
    for (i = 0; i < (tamanho_ean - 1); i = i+2)
        soma += (ean[i] - '0');
    /* adicionar os numeros impares */
    for (i = 1; i < (tamanho_ean - 1); i = i+2 )
        soma += ((ean[i] - '0') * MULTEAN);

    ultimo_digito = (10 - (soma%10)) % 10;
    
    if (ultimo_digito != ean[(tamanho_ean - 1)] - '0')
        return FALSE;
    else
        return TRUE;
}

int eh_ean(char *ean){
    int tamanho_ean = strlen(ean);
    
    if (tamanho_ean != TAMANHOEAN8 && tamanho_ean != TAMANHOEAN13)
        return FALSE;

    else{
        if (verifica_digito_controlo(ean, tamanho_ean))
            return TRUE;
        else
            return FALSE;
    }
}

int eh_preco(double preco){
    if (preco <=0)
        return FALSE;
    else
        return TRUE;
}

int eh_quantidade (int qtd){
    if (qtd <0)
        return FALSE;
    return TRUE;
}

int eh_descricao(char *desc){
    int tamanho_descricao = strlen(desc);
    if (!eh_maisucula(desc[0]))
        return FALSE;
    if (tamanho_descricao > (MAXDESCRICAO))
        return FALSE;
    return TRUE;
}

int eh_wildcard_valido(char *padrao, char *ean) {
    int i = 0, j = 0; /*i percorre padrao e j o ean*/  
    int ultimo_asterisco = ERROR, ultimo_num = ERROR;

    while (ean[j] != '\0') {
        /* Caso (1) Eh um asterisco */
        if (padrao[i] == '*') {
            while (padrao[i + 1] == '*') { /*asteriscos seguidos*/
                i++; /* ignora-los */
            }
            ultimo_asterisco = i; /*atual. ultimo asterisco*/
            ultimo_num = j; /* atual. onde ficamos no numero*/
            i++;  /* Avança o padrão para o numero a seguir ao '*' */
        } 
        /* Caso (2) Num certo na pos certa ou '?' */
        else if (padrao[i] == '?' || padrao[i] == ean[j]) {
            i++; /*saltar*/
            j++;
        } 
        /* Caso (3) Nao deu match mas temos '*' atras para tentar de novo */
        else if (ultimo_asterisco != ERROR) {
            i = ultimo_asterisco + 1; /* padrao passa a comecar dps do '*' */
            ultimo_num++;   /* saltamos um numero do ean pq nao encaixou*/
            j = ultimo_num;  /* recomeça a procura no ean a partir dai */
        } 
        /* Caso (4) Nao deu match e ja nao ha asteriscos */
        else
            return FALSE;
    }

    /* ean ja acabou mas o padrao ainda tem '*' no fim */
    while (padrao[i] == '*')
        i++;
    /* Se chegamos ao fim do padrao e passou eh valido */
    if (padrao[i] == '\0')
        return TRUE;
    return FALSE;
}

int ler_argumento(char *in, int i, char *out) {
    int j = 0;
    /* ignorar espaços iniciais */
    while (in[i] == ' ') 
        i++;
    if (in[i] == '"') {
        i++; /* saltar aspa de abertura */
        while (in[i] != '\0' && in[i] != '"') {
            out[j] = in[i];
            j++;
            i++;
        }
        if (in[i] != '"') 
            return ERROR; /* aspa de fecho não encontrada */
        i++; /* saltar aspa de fecho */
    } else {
        while (in[i] != '\0' && in[i] != '\n' && in[i] != ' ') {
            out[j] = in[i];
            j++;
            i++;
        }
    }
    out[j] = '\0';
    return i; /*retorna o indice do próximo espaço*/
}


