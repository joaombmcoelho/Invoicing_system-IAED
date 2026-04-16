/**
 * Ficheiro com os prototipos das funcoes da estrutura Fatura
 * @file: proj_fatura.h
 * @author: ist1117964 (João Coelho)
 */

#ifndef FATURA_H
#define FATURA_H
#include "proj_constantes.h"

/**
 * Estrutura que representa uma fatura no sistema.
 * Contem o nif, o nome do cliente, o numero de produtos a faturar,
 * o valor pago pelo cliente e o numero da fatura.
 * @struct fatura
 */
typedef struct fatura Fatura;

/* GETTERS */

/** 
 * Obtem o nif de uma fatura.
 * @param fatura    fatura
 * @return  devolve o nif associado ah fatura
 */
int obtem_nif_ft(Fatura *fatura);

/** 
 * Obtem o nome de uma fatura.
 * @param fatura    fatura
 * @return  devolve o nome associdado ah fatura
 */
char *obtem_nome_ft(Fatura *fatura);

/** 
 * Obtem o numero de produtos de uma fatura.
 * @param fatura    fatura
 * @return  devolve o numero de produtos associdado ah fatura
 */
int obtem_num_prod_ft(Fatura *fatura);

/** 
 * Obtem o valor pago de uma fatura.
 * @param fatura    fatura
 * @return  devolve o valor pago associdado ah fatura
 */
double obtem_valor_pago_ft(Fatura *fatura);

/** 
 * Obtem o numero de uma fatura.
 * @param fatura    fatura
 * @return  devolve o numero associdado ah fatura
 */
int obtem_num_ft(Fatura *fatura);

/* FUNCOES DA STRUCT FATURA */

/** 
 * Inicializa uma fatura com os argumentos fornecidos.
 * @param nif    nif
 * @param nome  nome do cliente
 * @param num_prods numero de produtos
 * @param valor_pago    valor pago
 * @param num_ft    numero da fatura
 * @return  devolve a fatura inicializada
 */
Fatura* inicializa_fatura(int nif, char *nome, int num_prods, 
                                double valor_pago, int num_ft);

/** 
 * valida se os argumentos dados para criar uma fatura sao validos.
 * Se um_arg eh TRUE trata do nif e nome, caso contrario trata do nome.
 * @param um_arg   flag de TRUE ou FALSE
 * @param nif    nif
 * @param i  posicao no input
 * @param in input
 * @param arg1  vetor nif (se relevante)
 * @param arg2 nome
 * @return  devolve TRUE se a fatura pode ser criada, FALSE caso contrario
 */
int valida_ft(int um_arg, int *nif, int i, char *in, char *arg1, char *arg2);

/** 
 * Imprime uma fatura
 * @param fatura    fatura
 */
void imprime_fatura (Fatura *fatura);

/** 
 * Imprime as faturas associadas ao nome de um cliente se TODAS = TRUE.
 * Caso contrario imprime todas as faturas no vetor de faturas.
 * @param faturas    vetor de faturas
 * @param nome      nome do cliente
 * @param n_fts     tamanho do vetor de faturas
 * @param todas     flag de TRUE ou FALSE
 * @return  devolve TRUE se imprimiu e FALSE caso contrario
 */
int imprime_ft_cliente(Fatura **faturas, char *nome, int n_fts, int todas);

/** 
 * Imprime todas as faturas do sistema por ordem alfabetica 
 * do nome do cliente e por ordem de criacao
 * @param faturas_in    vetor de faturas (nao eh alterado)
 * @param n_faturas    tamanho do vetor de faturas
 */
void imprime_tds_ft_ord(Fatura **faturas_in, int n_faturas);

/** 
 * Procura a posicao da fatura com o numero indicado
 * @param faturas    vetor de faturas
 * @param n_fts     tamanho do vetor de faturas
 * @param num     numero da fatura a procurar
 * @return  devolve a pos da fatura ou ERROR se nao existe
 */
int obtem_pos_ft(Fatura **faturas, int n_faturas, int num);

#endif