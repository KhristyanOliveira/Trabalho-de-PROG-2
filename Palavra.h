#ifndef PALAVRA_H
#define PALAVRA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_MAX_NOME_ARQ 40
#define TAM_MAX_PALAVRA 50

typedef struct Palavra palavra;

palavra **Le_Palavra(int* tam_vet, char* dir, int* qtd_palavras);
palavra *Inicializa_palavra(char* noticia);
static int calculaQuantidadeDeArquivos(char* dir);

char* getPalavra(palavra* pal);
static int Retorna_Idx_Palavra_Vetor(char palavraUnica[], palavra** vetorDePalavras, int qtd);
static int Verifica_Palavra_Ja_Existe_Noticia(char palavraUnica[], palavra** vetorDePalavras, int qtd);
int Le_Noticia_Unica(palavra** vetorDePalavras, FILE* arq, int tam);

#endif