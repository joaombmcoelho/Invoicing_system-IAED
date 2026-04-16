/**
 * Ficheiro com os prototipos das funcoes auxiliares usadas em todo o projeto
 * @file: proj_aux.h
 * @author: ist1117964 (João Coelho)
 */

#ifndef AUX_H
#define AUX_H

/** 
 * Determina se um caracter eh ou nao uma letra.
 * Tambem funciona para caracteres acentuados.
 * @param c	    o caracter a ser verificado
 * @return      TRUE se c eh uma letra e FALSE caso contrario
 */
int eh_letra(unsigned char c);

/** 
 * Determina se um caracter eh ou nao uma letra maiuscula.
 * Tambem funciona para caracteres acentuados.
 * @param c	    o caracter a ser verificado
 * @return      TRUE se c eh uma letra maiuscula e FALSE caso contrario
 */
int eh_maisucula(unsigned char c);

/** 
 * Determina se um vetor eh composto apenas por numeros.
 * @param caracteres    vetor de carcateres
 * @return      TRUE se c eh apenas composto por numeros e FALSE caso contrario
 */
int eh_numero(char *caracteres);

/** 
 * Determina se um vetor de carcateres eh um nome.
 * @param nome      vetor de carcateres
 * @return      TRUE se nome eh um nome e FALSE caso contrario
 */
int eh_nome(char *nome);

/** 
 * Determina se chegamos ao fim do input.
 * @param in    input
 * @param i     posicao em que estamos a percorrer o input
 * @return  TRUE se se chegamos ao fim do input e FALSE caso contrario
 */
int eh_fim_input(char *in, int i);

/** 
 * Determina se um vetor de carcateres eh um ean.
 * @param ean   vetor de carcateres
 * @return      TRUE se ean eh um ean e FALSE caso contrario
 */
int eh_ean(char *ean);

/** 
 * Determina se um numero eh um preco.
 * @param preco     preco
 * @return      TRUE se preco eh um preco e FALSE caso contrario
 */
int eh_preco(double preco);

/** 
 * Determina se um numero eh uma quantidade.
 * @param qtd   quantidade
 * @return      TRUE se qtd eh uma quantidade e FALSE caso contrario
 */
int eh_quantidade (int qtd);

/** 
 * Determina se um vetor de caracteres eh uma descricao.
 * @param desc  descricao
 * @return      TRUE se desc eh uma descricao e FALSE caso contrario
 */
int eh_descricao(char *desc);

/** 
 * Compara uma string com um padrao que pode conter os wildcards '*' e '?'.
 * @param padrao   O padrao de procura (com wildcards)
 * @param ean   A string a ser comparada (ean)
 * @return      TRUE se corresponder (match) e FALSE caso contrario
 */
int eh_wildcard_valido(char *padrao, char *ean) ;

/** 
 * Le um argumento de um input a partir da posicao i.
 * Se estiver entre aspas, le ate ao fim das aspas, limpando-as.
 * Caso contrario, le ate encontrar um espaco ou o fim do input.
 * @param in    input
 * @param i     posicao em que estamos a percorrer o input
 * @param out   argumento lido e limpo
 * @return  indice do proximo caracter do input 
 * ou ERRO se as aspas introduzidas nao foram fechadas
 */
int ler_argumento(char *in, int i, char *out);

#endif
