#ifndef NO_INTERNO_H
#define NO_INTERNO_H

#define D 2

#include <stdio.h>

typedef struct NoInterno {
	// m eh o numero total de chaves armazenados no noh
	int m;
	// flag que diz se noh aponta pra folha ou nao
	int aponta_folha;
	// ponteiro para o noh pai
	int pont_pai;
	// essa lista tera sempre m + 1 ponteiros
	int *p;
	// essa lista tera sempre m chaves
	int *chaves;
} NoInterno;

// Imprime noh interno
void imprime_no_interno(NoInterno *no);

// Cria noh interno. Lembrar de usar libera_no_interno(no)
NoInterno *no_interno(int m, int pont_pai, int aponta_folha);

// Cria noh interno. Lembrar de usar libera_no_interno(no)
NoInterno *no_interno_vazio();

// Cria noh interno com dados. Lembrar de usar libera_no_interno(no)
// Size deve ser 2m + 1
NoInterno *cria_no_interno(int m, int pont_pai, int aponta_folha, int size, ...);

// Grava uma pagina (noh) no arquivo em disco
void salva_no_interno(NoInterno *no, FILE *out);

// Le uma pagina (noh) do disco
NoInterno *le_no_interno(FILE *in);

// Compara dois nohs internos
// Retorna 1 se os valores dos atributos de ambos forem iguais
// e 0 caso contrario
int cmp_no_interno(NoInterno *n1, NoInterno *n2);

// Retorna tamanho do noh interno em bytes
int tamanho_no_interno();

// Libera noh interno
void libera_no_interno(NoInterno *no);

#endif