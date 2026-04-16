/**
 * Ficheiro com os prototipos das funcoes da estrutura Produto
 * @file: proj_produto.h
 * @author: ist1117964 (João Coelho)
 */

#ifndef PRODUTO_H
#define PRODUTO_H
#include "proj_constantes.h"
#include "proj_iva.h"

/**
 * Estrutura que representa um produto no sistema.
 * Contem o ean, o iva, o preco do produto, a quantidade,
 * a quantidade vendida e a descricao.
 * @struct  produto
 */
typedef struct produto Produto;

/* GETTERS */

/**
 * Obtem o ean de um produto.
 * @param   prod    produto
 * @return  devolve o ean desse produto
 */
char* obtem_ean_produto (Produto *prod);

/**
 * Obtem a quantidade de um produto.
 * @param   prod    produto
 * @return  devolve a quantidade desse produto
 */
int obtem_qtd_produto (Produto *prod);

/**
 * Obtem a quantidade vendida de um produto.
 * @param   prod    produto
 * @return  devolve a quantidade vendida desse produto
 */
int obtem_qtd_vendida (Produto *prod);

/**
 * Obtem o preco de um produto.
 * @param   prod    produto
 * @return  devolve o preco desse produto
 */
double obtem_preco_produto (Produto *prod);

/**
 * Obtem a descricao de um produto.
 * @param   prod    produto
 * @return  devolve a descricao desse produto
 */
char* obtem_desc_produto (Produto *prod);

/* SETTERS */

/**
 * Adiciona a quantidade introduzida ao produto.
 * @param   prod    produto
 */
void adiciona_qtd_produto (Produto *prod, int nova_qtd);

/**
 * Retira a quantidade introduzida ao produto.
 * @param   prod    produto
 */
void retira_qtd_produto (Produto *prod, int qtd);

/**
 * Substitui o iva do produto pelo introduzido.
 * @param   prod    produto
 */
void atualiza_iva_produto (Produto *prod, Iva *iva);

/**
 * Substitui o preco do produto pelo introduzido.
 * @param   prod    produto
 */
void atualiza_preco_produto (Produto *prod, double preco);

/**
 * Adiciona a quantidade introduzida ah quantidade vendida do produto.
 * @param   prod    produto
 */
void adiciona_qtd_vendida (Produto *prod, int qtd);

/**
 * Retira a quantidade introduzida ah quantidade vendida do produto.
 * @param   prod    produto
 */
void retira_qtd_vendida (Produto *prod, int qtd);

/**
 * Substitui a descricao do produto pela introduzida.
 * @param   prod    produto
 */
void atualiza_desc_prod(Produto *prod, char *desc);

/* FUNCOES DA STRUCT PRODUTO */

/** 
 * Inicializa um produto com os argumentos fornecidos.
 * @param ean    ean
 * @param codigo_iva    codigo de iva
 * @param preco     preco
 * @param qtd    quantidade do produto
 * @param desc   descricao do produto
 * @param iva   vetor de ivas
 * @return  devolve o produto inicializado
 */
Produto* inicializa_prod(char *ean, char codigo_iva, double preco,
                                    int qtd, char *desc, Iva **iva);

/** 
 * valida se os argumentos dados para criar um produto sao validos.
 * @param ean    ean
 * @param codigo_iva    codigo de iva
 * @param preco     preco
 * @param qtd    quantidade do produto
 * @param desc   descricao do produto
 * @param iva   vetor de ivas
 * @return  devolve TRUE se o produto pode ser criado, FALSE caso contrario
 */
int valida_prod(char *ean, char codigo_iva, double preco, int qtd, 
                                            char *desc, Iva **iva);

/** 
 * Imprime um produto
 * @param prod    produto
 */
void imprime_produto (Produto *prod);

/** 
 * Imprime um produto de acordo com o formato pedido no comando a
 * @param   prod    produto
 * @param qtd   quantidade adicionada ao cesto
 * @param preco_final   preco a pagar pelo produto
 */
void imprime_produto_cmd_a (Produto *prod, int qtd, double preco_final);

/** 
 * Calcula o preco final de um produto de acordo com a quantidade
 * a comprar e com o iva a adicionar.
 * @param prod    prod
 * @param qtd    quantidade a adicionada ao cesto
 * @return  devolve o preco final
 */
double calcula_preco_total_iva(Produto *produto, int qtd);

#endif