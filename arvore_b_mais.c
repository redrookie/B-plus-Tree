#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <limits.h>
#include <stdlib.h>
#include "arvore_b_mais.h"
#include "metadados.h"
#include "no_folha.h"
#include "no_interno.h"
#include "cliente.h"

void redistribuicao(NoInterno *pai, NoFolha *esq, NoFolha *dir, FILE *index, FILE *data, int pos_pai, int op){	//0 esq e o resto dir
	if(op==0){
		int tam = esq->m + dir->m;
		Cliente** clientes = malloc(sizeof(Cliente*)*tam);
		int i,cont=0;
		for(i=0;i<esq->m;i++){
			clientes[cont++] = esq->clientes[i];
			esq->clientes[i]=NULL;
		}
		for(i=0;i<dir->m;i++){
			clientes[cont++] = dir->clientes[i];
			dir->clientes[i] = NULL;
		}
		esq->m = D;
		cont=0;
		for(i=0;i<D;i++){
			esq->clientes[i] = clientes[cont++];
		}
		pai->chaves[pos_pai-1] = clientes[cont]->cod_cliente;
		for(i=0;i<tam-D;i++){
			dir->clientes[i] = clientes[cont++];
		}
		dir->m = tam-D;
		free(clientes);
		fseek(index, esq->pont_pai, SEEK_SET);
		salva_no_interno(pai, index);
		fseek(data, pai->p[pos_pai-1], SEEK_SET);
		salva_no_folha(esq, data);
		fseek(data, pai->p[pos_pai], SEEK_SET);
		salva_no_folha(dir, data);
	}
	else{
		int tam = esq->m + dir->m;
		Cliente** clientes = malloc(sizeof(Cliente*)*tam);
		int i,cont=0;
		for(i=0;i<esq->m;i++){
			clientes[cont++] = esq->clientes[i];
			esq->clientes[i]=NULL;
		}
		for(i=0;i<dir->m;i++){
			clientes[cont++] = dir->clientes[i];
			dir->clientes[i] = NULL;
		}
		esq->m = D;
		cont=0;
		for(i=0;i<D;i++){
			esq->clientes[i] = clientes[cont++];
		}
		pai->chaves[pos_pai] = clientes[cont]->cod_cliente;
		for(i=0;i<tam-D;i++){
			dir->clientes[i] = clientes[cont++];
		}
		dir->m = tam-D;
		free(clientes);
		fseek(index, esq->pont_pai, SEEK_SET);
		salva_no_interno(pai, index);
		fseek(data, pai->p[pos_pai], SEEK_SET);
		salva_no_folha(esq, data);
		fseek(data, pai->p[pos_pai+1], SEEK_SET);
		salva_no_folha(dir, data);
	}


}

int posicao_pai_folha(NoFolha *a,int pont, FILE *in){
	fseek(in,a->pont_pai,SEEK_SET);
	NoInterno *pai = le_no_interno(in);
	int i;
	for(i=0;i<2*D+1;i++){
		if(pai->p[i]==pont){
			libera_no_interno(pai);
			return i;
		}
	}
	libera_no_interno(pai);
	return -1;	//Nunca deve acontecer
}

void shift_c(Cliente** arr, int pos, int size, int op) {	//0 insere e qualquer outro exclui
	if(op==0){
		for (int i = size - 2; i >= pos; i--) {
			arr[i + 1] = arr[i];
		}
	}
	else{
		for (int i = pos; i < size-1; i++) {
			arr[i] = arr[i+1];
		}
		arr[size-1] = NULL;
		
	}
}

void shift_p(int* arr, int pos, int size, int op) {	//0 insere e qualquer outro exclui
	if(op==0){
		for (int i = size - 2; i >= pos; i--) {
			arr[i + 1] = arr[i];
		}
	}
	else{
		for (int i = pos; i < size-1; i++) {
			arr[i] = arr[i+1];
		}
		arr[size-1] = -1;
	}
}


int busca(int cod_cli, char *nome_arquivo_metadados, char *nome_arquivo_indice, char *nome_arquivo_dados, int *pont_folha, int *encontrou)
{
	FILE *meta = fopen(nome_arquivo_metadados,"rb+");
	FILE *index = fopen(nome_arquivo_indice,"rb+");
	FILE *data = fopen(nome_arquivo_dados,"rb+");
	Metadados *m = le_metadados(meta);
	if(m->raiz_folha){
		fseek(data,m->pont_raiz,SEEK_SET);
		NoFolha *leaf = le_no_folha(data);
		int i;
		*pont_folha = m->pont_raiz;
		for(i=0;i<leaf->m;i++){
			if(leaf->clientes[i]->cod_cliente == cod_cli){
				*encontrou = 1;
				libera_no_folha(leaf);
				free(m);
				fclose(meta);
				fclose(index);
				fclose(data);
				return i;
			}
			else if(leaf->clientes[i]->cod_cliente > cod_cli){
				*encontrou = 0;
				libera_no_folha(leaf);
				free(m);
				fclose(meta);
				fclose(index);
				fclose(data);
				return i;
			}
		}
		*encontrou = 0;
		int aux = leaf->m;
		libera_no_folha(leaf);
		free(m);
		fclose(meta);
		fclose(index);
		fclose(data);
		return aux ;	//BUG

	}
	fseek(index,m->pont_raiz,SEEK_SET);
	NoInterno *node = le_no_interno(index);
	while(!node->aponta_folha){
		int i,trocou=0;
		for(i=0;i<node->m;i++){
			if(node->chaves[i] > cod_cli){
				fseek(index,node->p[i],SEEK_SET);
				libera_no_interno(node);
				node = le_no_interno(index);
				trocou=1;
				break;
			}
		}
		if(!trocou){
			fseek(index,node->p[node->m],SEEK_SET);
			libera_no_interno(node);
			node = le_no_interno(index);
		}
	}
	int i,achou=0;
	NoFolha *leaf;
	for(i=0;i<node->m;i++){
		if(node->chaves[i] > cod_cli){
			fseek(data,node->p[i],SEEK_SET);
			*pont_folha = node->p[i];
			libera_no_interno(node);
			leaf = le_no_folha(data);
			achou=1;
			break;
		}
	}
	if(achou){
		for(i=0;i<leaf->m;i++){
			if(leaf->clientes[i]->cod_cliente == cod_cli){
				*encontrou = 1;
				libera_no_folha(leaf);
				free(m);
				fclose(meta);
				fclose(index);
				fclose(data);
				return i;

			}
			else if(leaf->clientes[i]->cod_cliente > cod_cli){
				*encontrou=0;
				libera_no_folha(leaf);
				free(m);
				fclose(meta);
				fclose(index);
				fclose(data);
				return i;
			}
		}
		free(m);
		fclose(meta);
		fclose(index);
		fclose(data);
		int aux = leaf->m;
		libera_no_folha(leaf);
		return aux;

	}
	fseek(data, node->p[node->m],SEEK_SET);
	*pont_folha = node->p[node->m];
	libera_no_interno(node);
	leaf = le_no_folha(data);
	for(i=0;i<leaf->m;i++){
			if(leaf->clientes[i]->cod_cliente == cod_cli){
				*encontrou = 1;
				libera_no_folha(leaf);
				free(m);
				fclose(meta);
				fclose(index);
				fclose(data);
				return i;

			}
			else if(leaf->clientes[i]->cod_cliente > cod_cli){
				*encontrou=0;
				libera_no_folha(leaf);
				free(m);
				fclose(meta);
				fclose(index);
				fclose(data);
				return i;
			}

	}
	free(m);
	fclose(meta);
	fclose(index);
	fclose(data);
	int aux = leaf->m;
	libera_no_folha(leaf);
	return aux;
}

void update_childs(int pont_interno, FILE* indice, FILE* dados) {
	NoInterno* no;
	fseek(indice, pont_interno, SEEK_SET);
	no = le_no_interno(indice);
	
	for (int i = 0; i <= no->m; i++) {
		int pont_folha = no->p[i];
		fseek(dados, pont_folha, SEEK_SET);
		NoFolha* tmp = le_no_folha(dados);
		tmp->pont_pai = pont_interno;
		fseek(dados, pont_folha, SEEK_SET);
		salva_no_folha(tmp, dados);
		libera_no_folha(tmp);
	}
	libera_no_interno(no);
}

void insere_chave_no_indice(int pont, int chave, int pont_dir, int pos, FILE* indice, FILE* dados, Metadados* metadados) {
	NoInterno* no;
	fseek(indice, pont, SEEK_SET);
	no = le_no_interno(indice);
	
	if (pos == -1) {
		for (pos = 0; pos < no->m; pos++) {
			if (no->chaves[pos] > chave) break;
		}
	}

	if (no->m < 2 * D) {
		shift_p(no->p, pos + 1, 2 * D + 1, 0);
		shift_p(no->chaves, pos, 2 * D, 0);
		no->p[pos + 1] = pont_dir;
		no->chaves[pos] = chave;
		no->m++;
	} else {
		int pont_novo = metadados->pont_prox_no_interno_livre;
		metadados->pont_prox_no_interno_livre += tamanho_no_interno();

		if (no->pont_pai == -1) {
			int pont_raiz = metadados->pont_prox_no_interno_livre;
			metadados->pont_prox_no_interno_livre += tamanho_no_interno();
			metadados->pont_raiz = pont_raiz;

			NoInterno* nova_raiz = no_interno_vazio();
			nova_raiz->aponta_folha = 0;
			nova_raiz->p[0] = pont;
			nova_raiz->pont_pai = -1;
			no->pont_pai = pont_raiz;
			fseek(indice, pont_raiz, SEEK_SET);
			salva_no_interno(nova_raiz, indice);
			libera_no_interno(nova_raiz);
		}

		NoInterno* novo = no_interno_vazio();
		novo->pont_pai = no->pont_pai;
		novo->aponta_folha = no->aponta_folha;

		int aux_c[D];
		int aux_p[D];

		for (int i = 0; i <= 2 * D; i++) {
			int* tmp;
			int* tmp_pont;
			if (i == pos) {
				tmp = &chave;
				tmp_pont = &pont_dir;
			} else if (i > pos) {
				tmp = &no->chaves[i - 1];
				tmp_pont = &no->p[i];
			} else {
				tmp = &no->chaves[i];
				tmp_pont = &no->p[i + 1];
			}
			
			if (i == D) {
				insere_chave_no_indice(no->pont_pai, *tmp, pont_novo, -1, indice, dados, metadados);
				novo->p[0] = *tmp_pont;
				fseek(indice, pont_novo, SEEK_SET);
				salva_no_interno(novo, indice);
				libera_no_interno(novo);
				*tmp = -1;
				*tmp_pont = -1;
			} else if (i > D) {
				insere_chave_no_indice(pont_novo, *tmp, *tmp_pont, i - D - 1, indice, dados, metadados);
				*tmp = -1;
				*tmp_pont = -1;
			} else {
				aux_c[i] = *tmp;
				aux_p[i] = *tmp_pont;
			}
		}

		no->m = D;
		for (int i = 0; i < D; i++) {
			no->chaves[i] = aux_c[i];
			no->p[i+1] = aux_p[i];
		}

		if (no->aponta_folha) {
			update_childs(pont_novo, indice, dados);
		}
	}
	
	fseek(indice, pont, SEEK_SET);
	salva_no_interno(no, indice);
	libera_no_interno(no);
}

int insere_cliente_no_folha(int pont, Cliente* client, int pos, FILE* indice, FILE* dados, Metadados* metadados) {
	int pont_final = pont;
	NoFolha* no;

	fseek(dados, pont, SEEK_SET);
	no = le_no_folha(dados);

	if (no->m < 2 * D) {
		shift_c(no->clientes, pos, 2 * D, 0);
		no->clientes[pos] = client;
		no->m++;
	} else {
		int pont_nova_folha = metadados->pont_prox_no_folha_livre;
		metadados->pont_prox_no_folha_livre += tamanho_no_folha();

		if (no->pont_pai == -1) {
			int pont_raiz = metadados->pont_prox_no_interno_livre;
			metadados->pont_prox_no_interno_livre += tamanho_no_interno();
			metadados->pont_raiz = pont_raiz;
			metadados->raiz_folha = 0;

			NoInterno* nova_raiz = no_interno_vazio();
			nova_raiz->aponta_folha = 1;
			nova_raiz->p[0] = pont;
			nova_raiz->pont_pai = -1;
			no->pont_pai = pont_raiz;
			fseek(indice, pont_raiz, SEEK_SET);
			salva_no_interno(nova_raiz, indice);
			libera_no_interno(nova_raiz);
		}

		NoFolha* nova = no_folha_vazio();
		nova->pont_pai = no->pont_pai;
		nova->pont_prox = no->pont_prox;
		fseek(dados, pont_nova_folha, SEEK_SET);
		salva_no_folha(nova, dados);
		libera_no_folha(nova);

		if (pos >= D) {
			pont_final = pont_nova_folha;
		}

		Cliente* aux_c[D];

		for (int i = 0; i <= 2 * D; i++) {
			Cliente** tmp;
			if (i == pos) {
				tmp = &client;
			} else if (i > pos) {
				tmp = &no->clientes[i - 1];
			} else {
				tmp = &no->clientes[i];
			}
			
			if (i == D) {
				insere_chave_no_indice(no->pont_pai, (*tmp)->cod_cliente, pont_nova_folha, -1, indice, dados, metadados);
			}
			
			if (i >= D) {
				insere_cliente_no_folha(pont_nova_folha, *tmp, i - D, indice, dados, metadados);
				*tmp = NULL;
			} else {
				aux_c[i] = *tmp;
			}
		}

		no->m = D;
		no->pont_prox = pont_nova_folha;
		for (int i = 0; i < D; i++) {
			no->clientes[i] = aux_c[i];
		}
	}
	fseek(dados, pont, SEEK_SET);
	salva_no_folha(no, dados);
	libera_no_folha(no);
	return pont_final;
}

int insere(int cod_cli, char *nome_cli, char *nome_arquivo_metadados, char *nome_arquivo_indice, char *nome_arquivo_dados)
{
	int pont_folha, encontrou;
	int pos = busca(cod_cli, nome_arquivo_metadados, nome_arquivo_indice, nome_arquivo_dados, &pont_folha, &encontrou);
	if(encontrou) return -1;

	Metadados* metadados = le_arq_metadados(nome_arquivo_metadados);
	FILE* indice = fopen(nome_arquivo_indice, "rb+");
	FILE* dados = fopen(nome_arquivo_dados, "rb+");

	int pont_final = insere_cliente_no_folha(pont_folha, cliente(cod_cli, nome_cli), pos, indice, dados, metadados);

	salva_arq_metadados(nome_arquivo_metadados, metadados);
	free(metadados);
	fclose(indice);
	fclose(dados);
    return pont_final;
}

int exclui(int cod_cli, char *nome_arquivo_metadados, char *nome_arquivo_indice, char *nome_arquivo_dados)
{
	int pont_final,encontrou;
	int end = busca(cod_cli, nome_arquivo_metadados, nome_arquivo_indice, nome_arquivo_dados, &pont_final, &encontrou);
	if(!encontrou) return -1;
	FILE *index = fopen(nome_arquivo_indice, "rb+");
	FILE *data = fopen(nome_arquivo_dados, "rb+");
	fseek(data, pont_final, SEEK_SET);
	NoFolha *leaf = le_no_folha(data);
	free(leaf->clientes[end]);
	shift_c(leaf->clientes, end, 2*D, 1);
	leaf->m -= 1;
	if(leaf->m >= D){
		fseek(data, pont_final, SEEK_SET);
		salva_no_folha(leaf, data);
		fclose(index);
		fclose(data);
		libera_no_folha(leaf);
		return pont_final;
	}
	fseek(index,leaf->pont_pai,SEEK_SET);
	NoInterno *pai = le_no_interno(index);
	int pos_pai = posicao_pai_folha(leaf, pont_final, index);
	if(pos_pai-1>=0 && pai->p[pos_pai-1] != -1){	//Irmao da esquerda
		fseek(data, pai->p[pos_pai-1], SEEK_SET);
		NoFolha *e = le_no_folha(data);
		if(e->m + leaf->m >=2*D){	//Redistribuicao
			redistribuicao(pai, e, leaf, index, data, pos_pai, 0);
			libera_no_folha(leaf);
			libera_no_interno(pai);
			libera_no_folha(e);
			fclose(index);
			fclose(data);
			return pont_final;
		}

		libera_no_folha(e);
	}
	if(pos_pai+1<2*D+1 && pai->p[pos_pai+1] != -1){	//Irmao da direita
		fseek(data, pai->p[pos_pai+1], SEEK_SET);
		NoFolha *d = le_no_folha(data);
		if(d->m + leaf->m >=2*D){	//Redistribuicao
			redistribuicao(pai, leaf, d, index, data, pos_pai, 1);
			libera_no_folha(leaf);
			libera_no_interno(pai);
			libera_no_folha(d);
			fclose(index);
			fclose(data);
			return pont_final;
		}

		libera_no_folha(d);
	}	
}