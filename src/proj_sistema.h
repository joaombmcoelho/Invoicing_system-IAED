/**
 * Ficheiro com os prototipos das funcoes das estruturas Sistema e Artigo
 * @file: proj_sistema.h
 * @author: ist1117964 (João Coelho)
 */

#ifndef SISTEMA_H
#define SISTEMA_H

#include "proj_constantes.h"

/**
 * Estrutura que representa um produto no cesto.
 * Contem o ean do produto, a quantidade adicionada,
 * e a posicao do produto no armazem.
 * @struct  artigo
 */
typedef struct artigo Artigo;

/**
 * Estrutura que representa o sistema de faturacao.
 * Contem um vetor de produtos (armazem), um vetor de faturas,
 * o cesto de compras, a tabela de iva, e as variaveis que indicam
 * o tamanho do armazem, o tamanho do cesto, o tamanho das faturas,
 * e o numero de faturas emitidas e as variaveis que indicam a capacidade
 * dos vetores dinamicos faturas e cesto. Ainda contem o somatorio do
 * total de itens comprados e do valor total faturado.
 * @struct  sistema
 */
typedef struct sistema Sistema;

/* FUNCOES DO SISTEMA */

/** 
 * Inicializa o sistema.
 * @param argc    numero de argumentos 
 * @param argv    array com o nome dos argumentos introduzidos
 * @return  devolve o sistema inicializado
 */
Sistema* inicializa_sis(int argc, char **argv);

/** 
 * processa o comando p: termina o programa.
 * @param s    sistema 
 */
void comando_q(Sistema *s);

/** 
 * processa o comando p: 
 * introduz no sistema ou actualiza um novo produto.
 * @param s    sistema
 * @param in    input fornecido
 */
void comando_p (Sistema *s, char *in);

/** 
 * processa o comando l: lista produtos
 * @param s    sistema
 * @param in    input fornecido
 */
void comando_l (Sistema *s, char *in);

/** 
 * processa o comando a:
 * adiciona ao cesto a quantidade do produto indicado.
 * @param s    sistema
 * @param in    input fornecido
 */
void comando_a (Sistema *s, char *in);

/** 
 * processa o comando r: resumo de faturacao
 * @param s    sistema
 * @param in    input fornecido
 */
void comando_r(Sistema *s, char *in);

/** 
 * processa o comando f: fatura os produtos no cesto.
 * @param s    sistema
 * @param in    input fornecido
 */
void comando_f(Sistema *s, char *in);

/** 
 * processa o comando c: lista as faturas do sistema.
 * introduz no sistema ou actualiza um novo produto.
 * @param s    sistema
 * @param in    input fornecido
 */
void comando_c(Sistema *s, char *in);

/** 
 * processa o comando d: 
 * apaga o registo de um produto ou fatura.
 * @param s    sistema
 * @param in    input fornecido
 */
void comando_d(Sistema *s, char *in);

#endif
