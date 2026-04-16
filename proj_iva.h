/**
 * Ficheiro com os prototipos das funcoes da estrutura Iva
 * @file: proj_iva.h
 * @author: ist1117964 (João Coelho)
 */

#ifndef IVA_H
#define IVA_H
#include "proj_constantes.h"

/**
 * Estrutura que representa o Iva.
 * Contem o codigo de iva e o respetivo valor.
 * @struct iva
 */
typedef struct iva Iva;

/* GETTERS */

/** 
 * Obtem o valor de um iva.
 * @param iva  iva
 * @return  devolve o valor associado ao iva
 */
int obtem_valor_iva (Iva *iva);

/** 
 * Obtem o codigo de um iva.
 * @param iva  iva
 * @return  devolve o codigo associado ao iva
 */
char obtem_codigo_iva (Iva *iva);

/* FUNCOES DA STRUCT IVA */

/** 
 * Inicializa e preenche uma tabela de iva
 * com os pares valor -1 e codigo '\0'.
 * @return  devolve a tabela de iva
 */
Iva** inicializa_iva(void);

/** 
 * Verifica se o codigo de iva introduzido esta na tabela de iva.
 * @param codigo_iva  iva
 * @param iva vetor de ivas
 * @return  devolve o valor associado ao iva se existir.
 * Devolve ERROR se o codigo for invalido (nao esta na tabela).
 */
int eh_codigo_iva(char codigo_iva, Iva **iva);

/** 
 * Le o ficheiro de codigos de iva preenchendo a tabela de ivas com 
 * os pares codigo - valor la presentes.
 * @param nome_ficheiro nome do ficheiro
 * @param iva vetor de ivas
 */
void ler_ficheiro_iva(char *nome_ficheiro, Iva **iva);

/** 
 * Preenche a tabela de iva com os valores e codigos predefinidos
 * 'A' - 0
 * 'B' - 6
 * 'C' - 13
 * 'D' - 26
 * @param iva vetor de ivas
 */
void preenche_tabela_iva(Iva **iva);

#endif
