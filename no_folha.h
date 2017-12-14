#ifndef NO_FOLHA_H
#define NO_FOLHA_H

#define D 2

#include <stdio.h>

#include "cliente.h"

typedef struct NoFolha {
	// m eh o numero total de registros armazenados no noh
	int m;
	// ponteiro para o noh pai
	int pont_pai;
	// ponteiro para o proximo noh folha
	int pont_prox;
	// essa lista tera sempre m clients
	Cliente **clientes;
} NoFolha;

// Imprime noh folha
void imprime_no_folha(NoFolha *no);

// Cria noh folha. Lembrar de usar libera_no_folha(no)
NoFolha *no_folha(int m, int pont_pai, int pont_prox);

// Cria noh folha. Lembrar de usar libera_no_folha(no)
NoFolha *no_folha_vazio();

// Cria noh folha com dados. Lembrar de usar libera_no_folha(no)
NoFolha *cria_no_folha(int pont_pai, int pont_prox, int m, ...);

// Grava uma pagina (noh) no arquivo em disco
void salva_no_folha(NoFolha *no, FILE *out);

// Le uma pagina (noh) do disco
NoFolha *le_no_folha(FILE *in);

// Compara dois nohs folhas
// Retorna 1 se os valores dos atributos de ambos forem iguais
// e 0 caso contrario
int cmp_no_folha(NoFolha *n1, NoFolha *n2);

// Retorna tamanho do noh folha em bytes
int tamanho_no_folha();

// Libera noh folha e clientes
void libera_no_folha(NoFolha *no);

#endif