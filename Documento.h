#ifndef DOCUMENTO_H
#define DOCUMENTO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_MAX_NOME_ARQ 40

#define TAM_MAX_PALAVRA 50

typedef struct Documento documento;

typedef struct Palavra palavra;

documento **Le_documento(int* tam_vet, char* dir);
documento *Inicializa_Documento(char* noticia);

palavra **Le_Palavra(int* tam_vet, char* dir, int* qtd_palavras);
//palavra *Inicializa_palavra(char* noticia);

void imprimeNoticia(documento** doc, int qtd);

void libera_documento(documento *documento);
void libera_Documentos(documento **doc, int tamanho);

#endif