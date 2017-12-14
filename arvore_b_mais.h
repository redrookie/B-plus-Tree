#ifndef ARVORE_B_MAIS_H
#define ARVORE_B_MAIS_H

// Executa busca em Arquivos utilizando Arvore B+
// Assumir que ponteiro para prpximo noh eh igual a -1 quando nao houver proximo noh
// cod_cli: chave do cliente que esta sendo buscado
// nome_arquivo_metadados: nome do arquivo que contem os metadados
// nome_arquivo_indice: nome do arquivo de indice (que contem os nohs internos da arvore B+)
// nome_arquivo_dados: nome do arquivo de dados (que contem as folhas da arvore B+)
// pont_folha: ponteiro para indicar pagina folha que contem chave (se encontrar)
//   ou ultima pagina folha examinada (caso contrario)
// encontrou: pointeiro para indicar se encontrou o cliente
//	 1 se encontrou, 0 caso contrario
// Retorna posicao em que a chave se encontra dentro da pagina (se encontrar)
//   ou a posicao, na pagina pont, onde a chave deveria estar inserida
int busca(int cod_cli, char *nome_arquivo_metadados, char *nome_arquivo_indice, char *nome_arquivo_dados, int *pont_folha, int *encontrou);

// Executa insercao em Arquivos Indexados por Arvore B+
// cod_cli: chave do cliente que esta sendo inserido
// nome_cli: nome do cliente a ser inserido
// nome_arquivo_metadados: nome do arquivo de metadados
// nome_arquivo_indice: nome do arquivo de indice (que contem os nohs internos da arvore B+)
// nome_arquivo_dados: nome do arquivo de dados (que contem as folhas da arvore B+)
// Retorna o ponteiro para a folha onde o registro foi inserido
int insere(int cod_cli, char *nome_cli, char *nome_arquivo_metadados, char *nome_arquivo_indice, char *nome_arquivo_dados);

// Executa exclusao em Arquivos Indexados por Arvores B+
// cod_cli: chave do cliente a ser excluido
// nome_arquivo_metadados: nome do arquivo que contem os metadados
// nome_arquivo_indice: nome do arquivo de indice (que contem os nohs internos da arvore B+)
// nome_arquivo_dados: nome do arquivo de dados (que contem as folhas da arvore B+)
// Retorna o ponteiro para a folha onde o registro foi excluido
int exclui(int cod_cli, char *nome_arquivo_metadados, char *nome_arquivo_indice, char *nome_arquivo_dados);

#endif