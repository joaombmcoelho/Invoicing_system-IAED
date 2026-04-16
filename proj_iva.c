/**
 * Ficheiro com a implementacao das funcoes da estrutura Iva
 * @file: proj_iva.c
 * @author: ist1117964 (João Coelho)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proj_iva.h"
#include "proj_constantes.h"
#include "proj_aux.h"

struct iva{
    char codigo;
    int valor;
};

/* GETTERS */

int obtem_valor_iva (Iva *iva){
    return iva->valor;
}

char obtem_codigo_iva (Iva *iva){
    return iva->codigo;
}

/* FUNCOES DA STRUCT IVA */

Iva** inicializa_iva(void){
    Iva **iva;
    /*abrir memoria para a tabela de IVA*/
    iva = malloc(MAXIVA * sizeof(Iva *));
    if (iva == NULL){
        puts(ENOMEMORY);
        exit(1);   
    }

    /*preencher a tabela de iva a valores inválidos*/
    for (int i = 0; i < MAXIVA; i++){
        iva[i] = malloc(sizeof(Iva));
        iva[i]->valor = -1;
        iva[i]->codigo = '\0';
    }
    return iva;
}

int eh_codigo_iva(char codigo_iva, Iva **iva){
    if(eh_maisucula(codigo_iva))
        return iva[codigo_iva - 'A']->valor; /*a tabela ja esta ordenada*/
        /*devolve -1 se nao foi preenchido*/
    else
        return ERROR;
}

void ler_ficheiro_iva(char *nome_ficheiro, Iva **iva){
    FILE *tabela_iva;
    char letra;
    int valor;
    int i;

    tabela_iva = fopen(nome_ficheiro, "r");

    /*enquanto o programa ler 2 elementos por linha*/
    while(fscanf(tabela_iva, "%c %d\n", &letra, &valor) == 2){
        i = letra - 'A'; /*calcula logo a posicao de 0 a 25 onde por*/
        iva[i]->codigo = letra;
        iva[i]->valor = valor;
    }
    fclose(tabela_iva);
}

void preenche_tabela_iva(Iva **iva){
    int i;
    char codigos[] = {'A', 'B', 'C', 'D'};
    int valores[] = {0, 6, 13, 23};
    for (i = 0; i < STANDARDIVA; i++){
        iva[i]->codigo = codigos[i];
        iva[i]->valor = valores[i];
    }
}