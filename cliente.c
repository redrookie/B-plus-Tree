#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string.h>
#include <stdlib.h>

#include "cliente.h"


void imprime_cliente(Cliente *cliente)
{
	printf("%d, %s\n", cliente->cod_cliente, cliente->nome);
}

Cliente *cliente(int cod, char *nome)
{
	Cliente *cliente = (Cliente *) malloc(sizeof(Cliente));
	if (cliente) memset(cliente, 0, sizeof(Cliente));
	cliente->cod_cliente = cod;
	strcpy(cliente->nome, nome);
	return cliente;
}

void salva_cliente(Cliente *cliente, FILE *out)
{
	fwrite(&cliente->cod_cliente, sizeof(int), 1, out);
	fwrite(cliente->nome, sizeof(char), sizeof(cliente->nome), out);
}

Cliente *le_cliente(FILE *in)
{
	Cliente *cliente = (Cliente *) malloc(sizeof(Cliente));
	if (0 >= fread(&cliente->cod_cliente, sizeof(int), 1, in)) {
		free(cliente);
		return NULL;
	}
	fread(cliente->nome, sizeof(char), sizeof(cliente->nome), in);
	return cliente;
}

int cmp_cliente(Cliente *c1, Cliente *c2)
{
	if (c1 == NULL) {
		return (c2 == NULL);
	}
	if (c1->cod_cliente != c2->cod_cliente) {
		return 0;
	}
	if (strcmp(c1->nome, c2->nome) != 0) {
		return 0;
	}
	return 1;
}

int tamanho_cliente()
{
	return sizeof(int) + // cod_cliente
		sizeof(char) * TAM_NOME; // nome
}