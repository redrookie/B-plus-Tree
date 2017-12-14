#ifndef LISTA_NOS_INTERNOS_H
#define LISTA_NOS_INTERNOS_H

#include "no_interno.h"

typedef struct ListaNosInternos {
	NoInterno **lista;
	int qtd;
} ListaNosInternos;

// Imprime nohs internos
void imprime_nos_internos(ListaNosInternos *lc);

// Cria lista de nohs internos. Lembrar de usar libera_nos_internos(lista_nos)
ListaNosInternos *cria_nos_internos(int qtd, ...);

// Salva lista de nohs internos no arquivo nome_arquivo
void salva_nos_internos(char *nome_arquivo, ListaNosInternos *lc);

// Le lista de nohs internos do arquivo nome_arquivo
ListaNosInternos *le_nos_internos(char *nome_arquivo);

// Compara duas listas de nohs internos
// Retorna 1 se os nohs das duas listas forem iguais
// e 0 caso contrario
int cmp_nos_internos(ListaNosInternos *c1, ListaNosInternos *c2);

// Desaloca lista de nohs internos
void libera_nos_internos(ListaNosInternos *lc);

#endif