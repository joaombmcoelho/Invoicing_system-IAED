/**
 * Ficheiro com as constantes usadas em todo o projeto
 * @file: proj_constantes.h
 * @author: ist1117964 (João Coelho)
 */

#ifndef CONSTANTES_H   
#define CONSTANTES_H   

#define FALSE 0		/**< valor logico de falso */
#define TRUE 1		/**< valor logico de verdadeiro */
#define ERROR -1 	/**< condicao de erro */
#define MAXEAN 13   /**< comprimento maximo do EAN */
#define MAXDESCRICAO 50		/**< comprimento maximo da descricao */
#define TAMANHOEAN8 8	/**< comprimento do EAN8 */
#define TAMANHOEAN13 13		/**< comprimento do EAN13 */
#define MULTEAN 3	/**< valor da constante usada no calculo do EAN */
#define MAXINPUT 65535		/**< comprimento maximo do input */
#define MAXPRODUTOS 10000	/**< tamanho maximo do armazem */
#define QUANTIDADEMINIMA 1	/**< qtd minima que se pode adicionar ao cesto */
#define MAXIVA 26	/**< tamanho maximo do armazem */
#define STANDARDIVA 4	/**< numero de pares codigo-valor de iva padrao */
#define INICIOINPUT 2	/**< indice do inicio de um input */
#define MAXNIF 9	/**< tamanho maximo do NIF */
#define NIFPADRAO 999999999	/**< valor predefinido do NIF */
#define MENORMAIUSCULA 192		/**< pos menor let. maius. acentuada ASCII */
#define MAIORMAIUSCULA 222		/**< pos maior let. maius. acentuada ASCII */
#define MENORMINUSCULA 223		/**< pos menor let. minus. acentuada ASCII */
#define MAIORMINUSCULA 254		/**< pos menor let. maius. acentuada ASCII */
#define CAPACIDADE 10	/**< capacidade minima de um vetor antes do realloc */

#define EEANINVALIDO "invalid ean"	/**< codigo EAN invalido */
#define EIVAINVALIDO "invalid iva"	/**< codigo IVA invalido */
#define EPRECOINVALIDO "invalid price"	/**< preco invalido */
#define EQTDINVALIDA "invalid quantity"	/**< quantidade invalida */
#define EDESCRICAOINVALIDA "invalid description"	/**< descricao invalida */
#define EPRODUTOEMUSO "product in use"	/**< alterar prod q esta no cesto */
#define EPRODUTOINVALIDO "invalid product"	/**< se exceder num prod regist. */
#define ESEMSTOCK "no stock"	/**< se nao houver qtd disp de um prod */
#define ENOMEINVALIDO "invalid name"	/**< nome invalido */
#define ENOMEMORY "No memory."	/**< se crashou */
#define EINPUTINVALIDO "Comando inválido." /**< comando invalido */

#endif                