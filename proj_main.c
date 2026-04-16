/**
 * Ficheiro com a implementacao da funcao main que permite
 * executar os diferentes comandos do sistema de faturacao
 * @file: proj_main.c
 * @author: ist1117964 (João Coelho)
 */

#include <stdio.h>
#include <stdlib.h>
#include "proj_sistema.h"
#include "proj_constantes.h"

/* FUNCAO MAIN */

/** Sistema faturacao
 * @return	devolve sempre 0
 */
int main(int argc, char *argv[]) {
	char comando[MAXINPUT +1];

    /* Inicializa o sistema */
    Sistema *sistema = inicializa_sis(argc, argv);

	while (fgets(comando, MAXINPUT + 1, stdin))
		switch (comando[0]) {
			case 'q': comando_q(sistema); return 0;
			case 'p': comando_p(sistema, comando); break;
			case 'l': comando_l(sistema, comando); break;
			case 'a': comando_a(sistema, comando); break;
			case 'r': comando_r(sistema, comando); break;
			case 'f': comando_f(sistema, comando); break;
			case 'c': comando_c(sistema, comando); break;
			case 'd': comando_d(sistema, comando); break;
			default : puts(EINPUTINVALIDO); break;
		}
    comando_q(sistema);
	return 0;
}