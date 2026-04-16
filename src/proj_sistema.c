 /**
 * Ficheiro com a implementacao das funcoes das estruturas Sistema e Artigo
 * @file: proj_sistema.c
 * @author: ist1117964 (João Coelho)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proj_sistema.h"
#include "proj_constantes.h"
#include "proj_iva.h"
#include "proj_produto.h"
#include "proj_fatura.h"
#include "proj_aux.h"

struct artigo{
    char ean[MAXEAN + 1];
    int qtd_cesto;
    int pos_armazem;
};

struct sistema {
    Produto *armazem[MAXPRODUTOS]; 
    Fatura **faturas;
    Artigo *cesto;
    Iva **iva;
    int num_produtos;
    int num_produtos_cesto;
    int num_faturas;
    int num_faturas_emit;
    int capacidade_faturas;
    int capacidade_cesto;
    int total_itens_comprados;
    double valor_total_faturado;
};

/* GETTERS */

/** 
 * Obtem posicao do produto com o ean indicado no armazem
 * @param ean    ean a procurar
 * @param produtos    array de produtos (armazem)
 * @return  a posicao no armazem ou ERROR se nao existir
 */
static int obtem_pos_armazem(char *ean, Produto **produtos, int n_produtos) {
    int i;
    for (i = 0; i<n_produtos; i++){
        if (strcmp(obtem_ean_produto(produtos[i]), ean) == 0)
            return i;
    }
    return ERROR;
}

/** 
 * Obtem posicao do produto com o ean indicado no cesto
 * @param ean    ean a procurar
 * @param produtos    array de artigos (cesto)
 * @return  a posicao no cesto ou ERROR se nao existir
 */
static int obtem_pos_cesto(char *ean, Artigo *cesto, int n_produtos) { 
    int i;
    for (i = 0; i<n_produtos; i++){
        if (strcmp(cesto[i].ean, ean) == 0)
            return i;
    }
    return ERROR;
}

/* FUNCOES DO SISTEMA */

/** 
 * Inicializa e preenche a tabela de iva do sistema
 * @param s     sistema
 * @param argc    numero de argumentos 
 * @param argv    array com o nome dos argumentos introduzidos
 */
static void inicializa_iva_sis(Sistema *s, int argc, char **argv) {

    s->iva = inicializa_iva();

    /*procurar tabela de iva*/
    if (argc == 2)
       ler_ficheiro_iva(argv[1], s->iva); 
    
    /*preencher a tabela de iva (se nao for fornecido input)*/
    else if(argc == 1){
        preenche_tabela_iva(s->iva);
    }
}

Sistema* inicializa_sis(int argc, char **argv) {
    /*abrir memoria para o sistema*/
    Sistema *s = malloc(sizeof(Sistema));
    if (s == NULL) {
        puts(ENOMEMORY);
        exit(1);
    }

    s->num_produtos = 0;
    s->num_produtos_cesto = 0;
    s->num_faturas_emit = 0;
    s->num_faturas = 0;
    s->total_itens_comprados = 0;
    s->valor_total_faturado = 0;
    s->capacidade_faturas = CAPACIDADE; /*comecamos c/ espaco para 10 faturas*/
    s->capacidade_cesto = CAPACIDADE; /*comecamos c/ espaco para 10 produtos*/

    /*abrir memoria para as faturas*/
    s->faturas = (Fatura **) malloc(s->capacidade_faturas * sizeof(Fatura *));
    if (s->faturas == NULL){ /*se esgotamos memoria*/
        puts(ENOMEMORY);
        exit(1);
    }
    /*abrir memoria para o cesto*/
    s->cesto = (Artigo *) malloc(s->capacidade_cesto * sizeof(Artigo));
    if (s->cesto == NULL){ /*se esgotamos memoria*/
        puts(ENOMEMORY);
        exit(1);
    }
    /*abrir memoria para o IVA*/
    inicializa_iva_sis(s, argc, argv);
    return s;
}

/* COMANDO (q) */

void comando_q(Sistema *sistema){
    /*libertar faturas e os seus nomes*/
    for (int i = 0; i < sistema->num_faturas; i++){
        free(obtem_nome_ft(sistema->faturas[i]));
        free(sistema -> faturas[i]);
    }
    free(sistema->faturas);
    /*libertar cada produto*/
    for (int i = 0; i < sistema->num_produtos; i++)
        free(sistema->armazem[i]);       
    /*libertar IVA*/
    for (int i = 0; i < MAXIVA; i++)
        free(sistema -> iva[i]);
    free (sistema -> iva);

    free(sistema->cesto);

    free(sistema);
    /*libertar */
}

/* FUNCOES DO COMANDO (p) */

/** 
 * Atualiza os parametros de um produto
 * @param s    sistema
 * @param pos_armazem   posicao do produto no armazem
 * @param pos_cesto     posicao do produto no cesto
 * @param qtd     stock do produto
 * @param codigo_iva    codigo de iva do produto
 * @param preco     preco do produto
 * @param desc      descricao do produto
 * @return  devolve TRUE se atualizou o produto e FALSE caso tenha dado erro
 */
static int atualiza_prod(Sistema *s, int pos_armazem, int pos_cesto, int qtd,
                        char codigo_iva, double preco, char *desc){

    Iva *iva;
    Produto *produto = s -> armazem [pos_armazem];
    /*se se tentar alterar o preco de um produto que já está no cesto*/
    if (pos_cesto != ERROR){ /*produto existe no cesto*/
        if (preco != obtem_preco_produto(produto)){
            /*só dar erro se quantidade > 0*/
            if (s -> cesto[pos_cesto].qtd_cesto > 0){
                puts(EPRODUTOEMUSO);
                return FALSE;
            }
        }
    }
    /*atualizar o produto*/
    iva = s->iva[codigo_iva - 'A'];
    atualiza_iva_produto(produto, iva);
    atualiza_preco_produto(produto, preco);
    adiciona_qtd_produto(produto, qtd);
    atualiza_desc_prod(produto, desc);
    /*imprimir quantidade resultante*/
    printf("%d\n", (obtem_qtd_produto(produto)));
    return TRUE;
}

/** 
 * Adiciona um produto ao armazem
 * @param s    sistema
 * @param ean   posicao do produto no armazem
 * @param qtd     stock do produto
 * @param codigo_iva    codigo de iva do produto
 * @param preco     preco do produto
 * @param desc      descricao do produto
 * @return  devolve TRUE se adicionou o produto e FALSE caso tenha dado erro
 */
static int adiciona_prod(Sistema *s, char *ean, int qtd, char codigo_iva, 
                                                double preco, char *desc) {

    Produto *novo_prod;
    if (s->num_produtos >= MAXPRODUTOS){ /*se ja tivermos 10000 produtos*/
            puts(EPRODUTOINVALIDO);
            return FALSE;
        }
    /* Vamos criar o novo produto*/
    novo_prod = inicializa_prod(ean, codigo_iva, preco, 
                                qtd, desc, s->iva);
    /* adicionar ao fim do armazem */
    s -> armazem [s->num_produtos] = novo_prod;
    s -> num_produtos ++;
    printf("%d\n", obtem_qtd_produto(novo_prod));
    return TRUE;
}

void comando_p (Sistema *s, char *in){
    char ean [MAXEAN + 1],  desc [MAXDESCRICAO + 1], codigo_iva;
    char buf_desc [MAXINPUT + 1];
    double preco;
    int qtd, pos_cesto, pos_armazem;

    /*ler os valores*/
    sscanf(in + 2, "%s %c %lf %d %[^\n]" ,  ean, &codigo_iva, 
                                            &preco, &qtd, buf_desc);
    
    /*validacoes basicas do comando p*/
    if(!valida_prod(ean, codigo_iva, preco, qtd, buf_desc, s->iva))
        return;
    /*copiar buffer para a descricao*/
    strcpy(desc, buf_desc);
    /*ver se ja existe no armazem*/

    pos_armazem = obtem_pos_armazem(ean, s->armazem, s->num_produtos);
    pos_cesto = obtem_pos_cesto(ean, s->cesto, s->num_produtos_cesto);

    /* (A) - Produto existe no armazem*/
    if (pos_armazem != ERROR){
        /*atualizar o produto se passar validacoes*/
        if(!atualiza_prod  (s, pos_armazem, pos_cesto, qtd, 
                            codigo_iva, preco, desc))
            return;
    }
    /* (B) - Produto NÃO existe no armazem*/
    else{
        /*adicionar o produto se passar validacoes*/
        if(!adiciona_prod(s, ean, qtd, codigo_iva, preco, desc))
            return;
    }
}

/* FUNCOES DO COMANDO (l) */

/** 
 * imprime os produtos no armazem por ordem de criacao
 * @param armazem    vetor de produtos
 * @param num_produtos   tamanho armazem
 * @return  devolve TRUE se imprimiu e FALSE caso contrario
 */
static int lista_produtos_simples (Produto **armazem, int num_produtos){
    int i, imprimiu = FALSE;
    for (i=0; i< num_produtos; i++)
        /*so imprimir produtos com stock*/
        if (obtem_qtd_produto(armazem[i]) > 0){
            imprime_produto(armazem[i]);
            imprimiu = TRUE;
        }
    return imprimiu;
}

/** 
 * imprime os produtos no armazem com ean que combine
 * com os wildcards indicados e por ordem de criacao
 * @param armazem    vetor de produtos
 * @param n_prods   tamanho armazem
 * @param padrao    wildcard fornecido
 * @return  devolve TRUE se imprimiu e FALSE caso contrario
 */
static int lista_com_wildcard(Produto **armazem, int n_prods, char padrao[]) {
    int i, imprimiu = FALSE;
    for (i = 0; i < n_prods; i++) {
        if (obtem_qtd_produto(armazem[i]) > 0
            && eh_wildcard_valido(padrao, obtem_ean_produto(armazem[i]))) {
            imprime_produto(armazem[i]);
            imprimiu = TRUE;
        }
    }
    return imprimiu;
}

void comando_l (Sistema *s, char *in){
    int i = INICIOINPUT;
    char wildcard[MAXINPUT + 1];

    /*LISTA PRODUTOS SIMPLES*/
    /*se in[2] for '\0' o input é simples*/
    if (eh_fim_input(in,i)){
        /*se não houverem produtos a listar*/
        if (s->num_produtos == 0){
            printf("*: no such product\n");
            return;
            }
        else
            /*listar os produtos com qtd < 0*/
            if(!lista_produtos_simples(s->armazem, s->num_produtos)){
                /*se nao houverem produtos com qtd > 0*/
                printf("*: no such product\n");
                return;
            }
    }
    /*LISTA PRODUTOS COM WILDCARDS*/ 
    else{
        while(in[i] != '\0' && in[i]!= '\n'){
            i = ler_argumento(in, i, wildcard); /*pos do i = prox.espaco*/
            if(!lista_com_wildcard(s->armazem, s->num_produtos, wildcard)){
                /*se não houver produto correspondente*/
                printf("%s: no such product\n", wildcard);
                return;
            }
        }
    }
}

/* FUNCOES DO COMANDO (a) */

/** 
 * adiciona um artigo ao cesto por ordem crescente de codigo ean
 * @param s    sistema
 * @param prod   produto
 * @param qtd    quantidade
 * @return  devolve o indice do novo artigo no cesto
 */
static int adiciona_artigo_cesto(Sistema *s, Produto *prod, int qtd){ 
    int tamanho_cesto = s->num_produtos_cesto;
    int i, pos = tamanho_cesto;
    /*abrir espaco no cesto*/
    if(tamanho_cesto == s->capacidade_cesto){
        s->capacidade_cesto *= 2;

        s->cesto = (Artigo *) realloc  (s->cesto, 
                                        sizeof(Artigo) * s->capacidade_cesto);
        if (s->cesto == NULL){
            puts(ENOMEMORY);
            exit (1);
        }
    }
    /*adicionar por ordem*/
    /*encontrar posicao de insercao*/
    for(i = 0; i < tamanho_cesto; i++){
        if (strcmp(obtem_ean_produto(prod), s->cesto[i].ean) < 0) {  
            pos = i; /*pos de insercao, para no produto imediatamente maior*/
            break;   
        }
    }
    /*abrir espacos à direita da posicao de insercao*/
    for (i = tamanho_cesto; i > pos; i--){
        s->cesto[i] = s->cesto[i - 1];
    }
    /*inserir o artigo*/
    strcpy(s->cesto[pos].ean, obtem_ean_produto(prod));
    s->cesto[pos].qtd_cesto = qtd;

    return pos; /*devolve indice do novo artigo no cesto*/
}

/** 
 * Verifica se os argumentos introduzidos permitem adicionar
 * ou atualizar um artigo no cesto
 * @param s    sistema
 * @param ean   ean do artigo
 * @param qtd    quantidade a adicionar
 * @param pos_armazem   pos do artigo no armazem
 * @param pos_cesto     pos do artigo no cesto
 * @return  devolve TRUE se os argumentos sao validos e FALSE caso contrario
 */
static int valida_cesto(Sistema *s, char *ean, int qtd, 
                        int pos_armazem, int pos_cesto){

    /*VALIDACOES DA FUNCAO*/

    /*validar o ean*/
    if(!eh_ean(ean)){
        puts(EEANINVALIDO);
        return FALSE;
    }
    /*se o produto não existir*/
    if(pos_armazem == ERROR){
        printf("%s: no such product\n", ean);
        return FALSE;
    }
    /*se não houver quantidade suficiente*/
    if((obtem_qtd_produto(s->armazem[pos_armazem]) - qtd) < 0){
        puts(ESEMSTOCK);
        return FALSE;
    }
    /*quando queremos remover um produto*/
    if (qtd < 0){
        /*se quisermos remover produto q nao esta no cesto*/
        if(pos_cesto == ERROR){
            puts(EQTDINVALIDA);
            return FALSE;
        }
        else{
            /*se quisermos remover mais quantidade do que temos no cesto*/
            if ((qtd + s->cesto[pos_cesto].qtd_cesto) < 0){
                puts(EQTDINVALIDA);
                return FALSE;
            }
        }
    }
    return TRUE;
}

/** 
 * lista todos os artigos no cesto por ordem cresente de codigo ean
 * @param s    sistema
 */
static void lista_o_cesto(Sistema *s){
    int pos_armazem, qtd_cesto, i;
    double preco_final;
    Produto *prod;
    /*o cesto já esta ordenado*/
    for (i = 0; i < s->num_produtos_cesto; i++){
        qtd_cesto = s->cesto[i].qtd_cesto;
        if (qtd_cesto > 0){
            pos_armazem = s->cesto[i].pos_armazem;
            prod = s->armazem[pos_armazem];
            preco_final = calcula_preco_total_iva(prod, qtd_cesto);
            imprime_produto_cmd_a(prod, qtd_cesto, preco_final);
        }
    }
}

/** 
 * Concretiza o ato de adicionar ou atualizar um artigo no cesto
 * @param s    sistema
 * @param pos_cesto   posicao do artigo no cesto
 * @param pos_armazem   posicao do artigo no armazem
 */
static void regista_cmd_a(Sistema *s, int pos_cesto, int pos_armazem, int qtd){
    Produto *prod = s->armazem[pos_armazem];
    double preco_final;

    /*se quisermos adicionar (ou remover) quantidade a produto existente */
    if (pos_cesto != ERROR){
        s->cesto[pos_cesto].qtd_cesto += qtd;
        s->cesto[pos_cesto].pos_armazem = pos_armazem;
        /*por causa de eliminar eliminar produtos do armazem (^) */
    }
    /*se quisermos adicionar novo produto ao cesto*/
    else{
        pos_cesto = adiciona_artigo_cesto(s, prod, qtd);
        s->cesto[pos_cesto].pos_armazem = pos_armazem;
        s->num_produtos_cesto++;
    }
    /*registar a venda(ou desistência)*/
    adiciona_qtd_vendida(prod, qtd);
    preco_final = calcula_preco_total_iva(prod, s->cesto[pos_cesto].qtd_cesto);

    /*retirar (ou devolver) ao armazem o stock vendido(ou devolvido)*/
    retira_qtd_produto(prod, qtd);
    
    imprime_produto_cmd_a(prod, s->cesto[pos_cesto].qtd_cesto, preco_final);
}

void comando_a (Sistema *s, char *in){
    int pos_armazem, pos_cesto, i = INICIOINPUT, qtd; /*qtd = qtd a manipular*/
    char input_1[MAXINPUT + 1], input_2[MAXINPUT + 1], ean[MAXEAN + 1];

    /*ADICIONA AO CESTO SEM PARAMETROS*/
    if (eh_fim_input(in, i))
        lista_o_cesto(s);
    /*ADICIONA AO CESTO COM PARAMETROS*/
    else{
        /*primeiro input*/
        i = ler_argumento(in, i, input_1);
        while(in[i] == ' ')
            i++;
        /* (A) INTRODUZIU QUANTIDADE E EAN*/
        if (!eh_fim_input(in, i)){
            qtd = atoi(input_1); 
            ler_argumento(in, i, input_2);
            strcpy(ean, input_2); /*ean = input 2*/
        }
        /* (B) INTRODUZIU APENAS EAN*/
        else{
            qtd = QUANTIDADEMINIMA;
            strcpy(ean, input_1); /*ean = input 1*/
        }

        pos_armazem = obtem_pos_armazem(ean, s->armazem, s->num_produtos);
        pos_cesto = obtem_pos_cesto(ean, s->cesto, s->num_produtos_cesto);

        /* VALIDACOES DA FUNCAO */
        if(!valida_cesto(s, ean, qtd, pos_armazem, pos_cesto))
            return;

        /* ADICIONAR AO CESTO OU ATUALIZAR */
        regista_cmd_a(s, pos_cesto, pos_armazem, qtd);
    }
}

/* COMANDO (r) */

void comando_r(Sistema *s, char *in){
    int i = INICIOINPUT, j = 0, pos_armazem;
    char input[MAXINPUT + 1], ean[MAXEAN + 1];

    /*RESUMO FATURACAO SIMPLES*/
    if (eh_fim_input(in, i)){
        /*imprimir o resumo*/
        printf("%d %d %.2f\n", s->total_itens_comprados, 
                                s->num_faturas_emit, s->valor_total_faturado);
        /*imprimir a tabela de IVA (ja ordenada)*/
        for (j = 0; j < MAXIVA; j++){
            /*so foram preenchidos os valores >= 0*/
            if (obtem_valor_iva(s->iva[j]) != -1) 
                printf("%c %d%%\n", obtem_codigo_iva(s->iva[j]), 
                                    obtem_valor_iva(s->iva[j])); 
        }
    }
    /*RESUMO FATURACAO COM EAN*/
    else{
        ler_argumento(in, i, input);
        /*VALIDACOES DA FUNCAO*/

        /*validar ean*/
        if(!eh_ean(input)){
            puts(EEANINVALIDO);
            return;
        }
        /*se eh valido copiar para o vetor ean*/
        strcpy(ean, input);
        pos_armazem = obtem_pos_armazem(ean, s->armazem, s->num_produtos);
        /*se o produto nao existe no armazem*/
        if(pos_armazem == ERROR){
            printf("%s: no such product\n", ean);
            return;
        }
        
        /*FIM DAS VALIDACOES*/

        printf("%d %d %s\n",obtem_qtd_produto(s -> armazem [pos_armazem]),
                            obtem_qtd_vendida(s -> armazem [pos_armazem]),
                            obtem_desc_produto(s ->armazem [pos_armazem]));
    }
}

/* FUNCOES DO COMANDO (f) */

/** 
 * Devolve as quantidades de todos os produtos no cesto,
 * volta a adiciona-los ao armazem e diminui a quantidade vendida
 * @param s    sistema
 */
static void anular_venda(Sistema *s){
    int i, qtd_saiu_cesto, pos_armazem;
    int tamanho_cesto = s->num_produtos_cesto;
    
    for(i = 0; i < tamanho_cesto; i++){
        pos_armazem = s->cesto[i].pos_armazem;
        qtd_saiu_cesto = s->cesto[i].qtd_cesto;
        /*devolver quantidades*/
        adiciona_qtd_produto(s -> armazem[pos_armazem], qtd_saiu_cesto);
        /*atualizar estatisticas*/
        retira_qtd_vendida(s -> armazem[pos_armazem], qtd_saiu_cesto);
    }
    /*reiniciar o cesto (vai voltar a escrever o cesto do inicio)*/
    s->num_produtos_cesto = 0;
}

/** 
 * Cria uma fatura com todos os produtos no cesto,
 * @param s    sistema
 * @param nome  nome do cliente
 * @param nif nif
 */
static void fatura_o_cesto(Sistema *s, char *nome, int nif){
    Fatura *nova_fatura = NULL;
    int i, n_prods = 0, pos_armazem;
    double valor_pago = 0;

    /*abrir memoria para novas faturas se necessario*/
    if (s->num_faturas == s->capacidade_faturas){
        s->capacidade_faturas *= 2; /*duplicar capacidade*/
        s->faturas = (Fatura **)realloc(s->faturas,
                                sizeof(Fatura *) * s->capacidade_faturas);
        /*se rebentou memoria*/
        if (s->faturas == NULL){
            puts(ENOMEMORY);
            exit(1); /*rebentou*/
        }
    }

    for (i = 0; i < s->num_produtos_cesto; i++){
        /*registar cada produto na fatura*/
        n_prods += s->cesto[i].qtd_cesto;
        pos_armazem = s->cesto[i].pos_armazem;
        valor_pago += calcula_preco_total_iva  (s->armazem[pos_armazem], 
                                                s->cesto[i].qtd_cesto);
    }
    
    /*criar a nova fatura*/
    nova_fatura = inicializa_fatura(nif, nome, n_prods, valor_pago, 
                                    s->num_faturas_emit + 1);
    s->total_itens_comprados += n_prods;
    s->valor_total_faturado += valor_pago;

    /*registar fatura no sistema*/
    s->faturas[s->num_faturas] = nova_fatura;
    s->num_faturas ++;
    s->num_faturas_emit ++;

    /*reiniciar o cesto (vai voltar a escrever o cesto do inicio)*/
    s->num_produtos_cesto = 0;
}

void comando_f(Sistema *s, char *in){
    int i = INICIOINPUT, nif = NIFPADRAO;
    int um_arg = TRUE;
    char arg_1[MAXINPUT + 1], nome_buf[MAXINPUT +1];
    strcpy(nome_buf, "Cliente final");

    while(in[i] == ' ')
        i++;

    /*FATURA PRODUTOS SIMPLES*/
        /*do nothing (tudo inicializado)*/
    
    /*FATURA PRODUTOS COM PARAMETROS*/
    if(!eh_fim_input(in,i)){
        /*ler primeiro argumento*/
        /*a funcao ler argumento limpa as aspas logo*/
        i = ler_argumento(in, i, arg_1); /*pode ser nif ou nome*/
        if (i == ERROR){ /*se nao fechou aspas*/
            puts(ENOMEINVALIDO);
            return;
        }
        while(in[i] == ' ')
            i++;
        /*ver se existe segundo argumento*/
        if (!eh_fim_input(in, i)) /*se nao acaba a seguir as aspas*/
            um_arg = FALSE;
        else{ /*se so tem um argumento, é o nome*/
            strcpy(nome_buf, arg_1);
        }
        /* VALIDAR E PREENCHER ARGUMENTOS */
        if(!valida_ft(um_arg, &nif, i, in, arg_1, nome_buf))
            return;

        /*se nome eh "error"*/
        if (strcmp(nome_buf, "error") == 0){
            anular_venda(s);
            return;
        }
    }
    /*se tudo correu bem faturar os produtos*/
    fatura_o_cesto(s, nome_buf, nif);
    imprime_fatura(s->faturas[s->num_faturas - 1]);    
}   

/* COMANDO (c) */

void comando_c(Sistema *s, char *in){
    int i = INICIOINPUT, tds = FALSE;
    char nome_buf[MAXINPUT + 1]; 

    /*LISTA FATURAS SIMPLES*/
    if(eh_fim_input(in, i)){
        imprime_tds_ft_ord(s->faturas, s->num_faturas);
    }
    /*LISTA FATURAS POR CLIENTE*/
    else{
        /*ler nome cliente e limpa-lo das aspas*/
        i = ler_argumento(in, i, nome_buf);
        /*validar o nome*/
        /*se nome tiver espacos e nao aspas*/
        if(!eh_fim_input(in, i)){
            puts(ENOMEINVALIDO);
            return;
        }
        if (i == ERROR){ /*nao fechou aspas*/
            puts(ENOMEINVALIDO);
            return;
        }
        if(!eh_nome(nome_buf)){
            puts(ENOMEINVALIDO);
            return;
        }
        /*listar faturas por nome*/
        if(!imprime_ft_cliente(s->faturas, nome_buf, s->num_faturas, tds)){
            /*se nao existirem p/ esse cliente*/
            printf("%s: no such client\n", nome_buf);
            return;
        }
    }
}

/* FUNCOES DO COMANDO (d) */


/** 
 * valida se os argumentos dados permitem apagar um produto do sistema.
 * @param s   sistema
 * @param ean    ean do produto
 * @param qtd  quantidade a apagar
 * @param pos_armazem   posicao do produto no armazem        
 * @return  devolve a quantidade restante do produto 
 * se este puder ser apagado, ERROR caso contrario.
 */
static int valida_apaga_prod(Sistema *s, char *ean, int qtd, int pos_armazem){
    int pos_cesto, qtd_restante;
    Produto *prod;
    /*ver EAN*/
    if(!eh_ean(ean)){
        puts(EEANINVALIDO);
        return ERROR;
    }
    /*ver se produto existe*/
    if(pos_armazem == ERROR){
        printf("%s: no such product\n", ean);
        return ERROR;
    }
    prod = s->armazem[pos_armazem];
    /*verificar quantidade*/

    if(qtd <= 0 || qtd > obtem_qtd_produto(prod)){
        puts(EQTDINVALIDA);
        return ERROR;
    }
    
    qtd_restante = obtem_qtd_produto(prod) - qtd;

    if(qtd_restante == 0){ /*so da erro se for para apagar prod*/
        /*ver se queremos apagar produto q ja esta no cesto*/
        pos_cesto = obtem_pos_cesto(ean, s->cesto, s->num_produtos_cesto);
        if(pos_cesto != ERROR){
            /*só esta no cesto se qtd > 0*/
            if(s->cesto[pos_cesto].qtd_cesto > 0){
                puts(EPRODUTOEMUSO);
                return ERROR;
            }
        }
    }
    return qtd_restante;
}

/** 
 * Apaga um produto do armazem
 * @param s    sistema
 * @param int     posicao do produto no armazem
 */
static void apaga_produto(Sistema *s, int pos_armazem){
    /*libertar memoria do produto*/
    free(s->armazem[pos_armazem]);
    /*manter ordem de criacao (por causa do comando l)*/
    /*puxar todos para tras*/
    for (int j = pos_armazem; j < s -> num_produtos - 1; j++)
        s->armazem[j] = s->armazem [j + 1];
    /*retirar ultimo elemento*/
    s -> num_produtos --;
    /*atualizar posicoes armazem dos artigos no cesto*/
    for(int k = 0; k < s->num_produtos_cesto; k++)
        if (s->cesto[k].pos_armazem > pos_armazem)
            s->cesto[k].pos_armazem--;
}

/** 
 * Apaga uma fatura do sistema
 * @param s    sistema
 * @param int     posicao do produto no armazem
 */
static void apaga_fatura(Sistema *s, int pos_fatura){
    /*eliminar variaveis do resumo faturacao*/
    s->total_itens_comprados -= obtem_num_prod_ft(s -> faturas [pos_fatura]);
    s->valor_total_faturado -= obtem_valor_pago_ft(s -> faturas [pos_fatura]);
    /*libertar memoria do nome cliente e da fatura*/
    free(obtem_nome_ft(s -> faturas [pos_fatura]));
    free(s->faturas[pos_fatura]);
    /*puxar faturas para tras*/
    for (int j = pos_fatura; j < s -> num_faturas - 1; j++)
        s->faturas[j] = s->faturas [j + 1];
    s->num_faturas --;
}

/** 
 * Processa a parte do comando d relacionada ao produto
 * @param s   sistema
 * @param ean    ean do produto
 * @param qtd  quantidade a apagar
 * @return  devolve FALSE se der erro e TRUE caso contrario.
 */
static int comando_d_prod(Sistema *s, char *ean, int qtd){
    int qtd_restante, pos_armazem;
    Produto *prod = NULL;
    /*VALIDAR ARGS E DESCOBRIR QTD RESTANTE*/
    pos_armazem = obtem_pos_armazem(ean, s->armazem, s->num_produtos);
    qtd_restante = valida_apaga_prod(s, ean, qtd, pos_armazem);
    if(qtd_restante == ERROR)
        return FALSE;
    prod = s->armazem[pos_armazem];
    /*IMPRIMIR*/
    printf("%d %s\n", qtd_restante, obtem_desc_produto(prod));

    /*(I) SOBRA STOCK*/
    if(qtd_restante > 0)
        retira_qtd_produto(prod, qtd);
    /*(II) ELIMINAR PRODUTO*/
    else
        apaga_produto(s, pos_armazem); 
    return TRUE;
}

/** 
 * Processa a parte do comando d relacionada ah fatura
 * @param s   sistema
 * @param num_ft    numero da fatura a apagar
 * @return  devolve TRUE se apagar e FALSE se der erro.
 */
static int comando_d_ft(Sistema *s, char *num_ft){
    int num, pos_fatura;
    Fatura *fatura;
    num = atoi(num_ft);
    pos_fatura = obtem_pos_ft(s->faturas, s->num_faturas, num);
    if(pos_fatura == ERROR){
        printf("%s: no such invoice\n", num_ft);
        return FALSE;
    }
    /*IMPRIMIR*/
    fatura = s->faturas[pos_fatura];
    printf("%.2f %d %s\n",  obtem_valor_pago_ft(fatura),
                            obtem_nif_ft(fatura),
                            obtem_nome_ft(fatura));
    apaga_fatura(s, pos_fatura);
    return TRUE;
}    

void comando_d(Sistema *s, char *in){
    int i = INICIOINPUT, qtd;
    char arg1 [MAXINPUT + 1];

    i = ler_argumento(in, i, arg1);

    while (in[i] == ' ')
        i++;

    /* (A) DOIS ARGUMENTOS - APAGA QTD PRODUTO*/
    if(!eh_fim_input(in, i)){
        sscanf(in + i, " %d", &qtd);
        if(!comando_d_prod(s, arg1, qtd))
            return;
    }
    /* (B) UM ARGUMENTO - APAGA FATURA */
    else{
        if(!comando_d_ft(s, arg1))
            return;
    } 
}