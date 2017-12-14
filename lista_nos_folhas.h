#ifndef LISTA_NOS_FOLHAS_H
#define LISTA_NOS_FOLHAS_H

#include "no_folha.h"

typedef struct ListaNosFolhas {
	NoFolha **lista;
	int qtd;
} ListaNosFolhas;

// Imprime nohs folhas
void imprime_nos_folhas(ListaNosFolhas *lc);

// Cria lista de nohs folhas. Lembrar de usar libera_nos_folhas(lista_nos)
ListaNosFolhas *cria_nos_folhas(int qtd, ...);

// Salva lista de nos folhas no arquivo nome_arquivo
void salva_nos_folhas(char *nome_arquivo, ListaNosFolhas *lc);

// Le lista de nos folhas do arquivo nome_arquivo
ListaNosFolhas *le_nos_folhas(char *nome_arquivo);

// Compara duas listas de nohs folhas
// Retorna 1 se os nohs das duas listas forem iguais
// e 0 caso contrario
int cmp_nos_folhas(ListaNosFolhas *c1, ListaNosFolhas *c2);

// Desaloca lista de nohs folhas
void libera_nos_folhas(ListaNosFolhas *lc);

#endif