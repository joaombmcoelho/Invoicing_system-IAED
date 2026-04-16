/**
 * Ficheiro com a implementacao das funcoes da estrutura Produto
 * @file: proj_produto.c
 * @author: ist1117964 (João Coelho)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proj_produto.h"
#include "proj_constantes.h"
#include "proj_iva.h"   
#include "proj_aux.h" 

struct produto{
    char ean[MAXEAN + 1];
    Iva *iva;
    double preco;
    int quantidade;
    int quantidade_vendida;
    char descricao[MAXDESCRICAO + 1];
};

/* GETTERS */

char* obtem_ean_produto (Produto *prod){
    return prod -> ean;
}

int obtem_qtd_produto (Produto *prod){
    return prod -> quantidade;
}

int obtem_qtd_vendida (Produto *prod){
    return prod -> quantidade_vendida;
}

double obtem_preco_produto (Produto *prod){
    return prod -> preco;
}

char* obtem_desc_produto (Produto *prod){
    return prod -> descricao;
}

/* SETTERS */

void adiciona_qtd_produto (Produto *prod, int nova_qtd){
    prod->quantidade += nova_qtd;
}

void retira_qtd_produto (Produto *prod, int qtd){
    prod->quantidade -= qtd;
}

void atualiza_iva_produto (Produto *prod, Iva *iva){
    prod->iva = iva;
}

void atualiza_preco_produto (Produto *prod, double preco){
    prod->preco = preco;
}

void adiciona_qtd_vendida (Produto *prod, int qtd){
    prod -> quantidade_vendida += qtd;
}

void retira_qtd_vendida (Produto *prod, int qtd){
    prod -> quantidade_vendida -= qtd;
}

void atualiza_desc_prod(Produto *prod, char *desc){
    strcpy(prod->descricao, desc);
}

/* FUNCOES DA STRUCT PRODUTO */

Produto* inicializa_prod(char *ean, char codigo_iva, double preco,
                                    int qtd, char *desc, Iva **iva){   
    
    Produto *p = malloc(sizeof(Produto));
    if (p == NULL){
        puts(ENOMEMORY);
        exit(1);   
    }

    strcpy(p->ean, ean);
    p->iva = iva[codigo_iva - 'A'];
    p->preco = preco;
    p->quantidade = qtd;
    p->quantidade_vendida = 0;
    strcpy(p->descricao, desc);

    return p;
}

int valida_prod(char *ean, char codigo_iva, double preco, int qtd, 
                                            char *desc, Iva **iva){    
    
    /*validacoes basicas do comando p*/
    /*se EAN errado*/
    if (!eh_ean(ean)){
        puts(EEANINVALIDO);
        return FALSE;
    }
    /*se IVA inválido*/
    if (eh_codigo_iva(codigo_iva, iva) == ERROR){
        puts(EIVAINVALIDO);
        return FALSE;
    }
    /*se Preço inválido*/
    if (!eh_preco(preco)){
        puts(EPRECOINVALIDO);
        return FALSE;
    }
    /*se Quantidade inválida*/
    if (!eh_quantidade(qtd)){
        puts(EQTDINVALIDA);
        return FALSE;
    }
    /*se Descricao invalida*/
    if (!eh_descricao(desc)){
        puts(EDESCRICAOINVALIDA);
        return FALSE;
    }
    return TRUE;
}

void imprime_produto (Produto *prod){
    printf("%s %c %.2f %d %d %s\n", 
    prod->ean,
    obtem_codigo_iva(prod->iva),
    prod->preco,
    prod->quantidade_vendida,
    prod->quantidade, /*quantidade disponivel*/
    prod->descricao);
}

void imprime_produto_cmd_a (Produto *prod, int qtd, double preco_final){
    printf("%c %.2f %d %.2f %s\n",  
        obtem_codigo_iva(prod -> iva),
        prod->preco,
        qtd,
        preco_final,
        prod->descricao);
}

double calcula_preco_total_iva(Produto *produto, int qtd){ 
    double total_sem_iva;
    double preco_unitario = produto->preco;
    double valor_final_arred;
    int percentagem_iva = obtem_valor_iva(produto->iva);
    int total_em_centimos;

    /*calculo do preço final*/
    total_sem_iva = preco_unitario * qtd;

    /*arredondamento simetrico aos centimos*/
    /*trabalhar com os centimos e cortar a partir das decimas*/

    /*
    *(int)((total_sem_iva * (1 + (percentagem_iva / 100.0))) * 100.0 + 0.5);
    *(^) formula (faz se direto para evitar erros arred na divisao)
    */

    total_em_centimos = (int)(total_sem_iva * (100 + percentagem_iva) + 0.5);
    valor_final_arred = total_em_centimos/100.0;

    return valor_final_arred;
}

