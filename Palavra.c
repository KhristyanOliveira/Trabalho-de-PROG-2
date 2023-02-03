#include "Palavra.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct Palavra {
  char* palavra; // Cada palavra em si;
  int frequencia; // A quantidade de vezes que a palavra aparece em todos os documentos;
  float tfidf; // Valor individual do tfidf dessa palavra.
};

static int calculaQuantidadeDeArquivos(char* dir) {
  FILE* arq = fopen(dir, "r");

  int qtdLinhas = 0;

  char proxLetra = getc(arq);
  while (proxLetra != EOF) {
    if (proxLetra == '\n') {
      qtdLinhas = qtdLinhas + 1;
    }
    proxLetra = getc(arq);
  }

  fclose(arq);

  return qtdLinhas;
}

palavra **Le_Palavra(int* tam_vet, char* dir, int* qtd_palavras){
  int tam = 100, cont = 0;

  int qtdLinhasArq = calculaQuantidadeDeArquivos(dir);
  //printf("Quantidade de linhas do arquivo %s: %d\n", dir, qtdLinhasArq);
  *tam_vet =qtdLinhasArq;

  /* Lendo arquivo train.txt */

  /*leu-se o arquivo train.txt para se ter a quantidade de arquivos a serem lidos. fazendo isso pelo uso da funcao
  calculaQuantidadeDeArquivos que le a quantidade de linhas que contam os nomes dos arquivos.*/


  //nomesArquivos é uma matriz que armazena o nome de cada arquivo .txt a ser lido.  
  char nomesArquivos[qtdLinhasArq][TAM_MAX_NOME_ARQ];

  FILE* arq = fopen(dir, "r");

  int i = 0;
  int j = 0;
  char carac = '\0';
  for (i = 0; i < qtdLinhasArq; i++) {
    for (j = 0; j < TAM_MAX_NOME_ARQ; j++) {
      fscanf(arq, "%c", &carac);
      if (carac == ' ') {
        nomesArquivos[i][j] = '\0';
        fscanf(arq, "%*[^\n]\n");
        break;
      } else {
        nomesArquivos[i][j] = carac;
      }
    }
  }

  fclose(arq);

  //teste que printa o nome dos arquivos, para ver se ouve a leitura certa dos mesmos.
  /*
  i = 0;
  for (i = 0; i < qtdLinhasArq; i++) {
    printf("%s\n", nomesArquivos[i]);
  }
  */

  /* Lendo os arquivos de fato */
  int contador = 0;
  char copia_dir[15];
  char dirInicial[10] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
  
  //printf("\n%s\n", dir);

  for(i=0; i< 10; i++){
    if(dir[i] == '/'){
      contador++;
    }
    if(contador == 2){
      break;
    } else{
      dirInicial[i] = dir[i];
    }
  }
  contador = 0;
  //printf("\ndirInicial:%s\n", dirInicial);

  i = 0;
  int somador =0;
  char caminhoArquivo[1000];
  char noticia[100000];

  
  
  FILE* saida_palavra = fopen("saida_palavra.txt", "w");

  /* Declarando o vetor de palavras */
  palavra **vetorDePalavras = (palavra **) malloc(1 * sizeof(palavra*)); 
  int x = 0;

  const char s[2] = " ";
  char *palavra_pointer;
  int iguais =0, posicao_vetor_word = 0;
  int tamanho =2000;
  char **palavra_noticia = malloc(tam * sizeof (char*));
  int tamVetorDePalavras = 0;

  for (i = 0; i < qtdLinhasArq; i++) {
    // leArquivo()
    // dir = "./small/train.txt"
    // dir incial quebra na segunda barra.
    sprintf(caminhoArquivo, "%s/%s", dirInicial, nomesArquivos[i]);
    FILE* arq2 = fopen(caminhoArquivo, "r");

    fprintf(saida_palavra,"\ndiretorio:%s\n\n", caminhoArquivo);

    tamVetorDePalavras = Le_Noticia_Unica(vetorDePalavras, arq2, tamVetorDePalavras);
    
    somador = somador + tamVetorDePalavras;
         
    fclose(arq2);
  }
  fclose(saida_palavra);

  *qtd_palavras = somador;

  return vetorDePalavras;
}

palavra *Inicializa_palavra(char* noticia) {
  palavra* pal = (palavra*) malloc(sizeof(palavra));
  pal->palavra = strdup(noticia);
  pal->frequencia = 0;
  pal->tfidf = 0;
  return pal;
}

char *getPalavra(palavra* pal){
  char palavraRetorno[100];

  strcpy(palavraRetorno, pal->palavra);

  //return palavraRetorno;

  return pal->palavra;
}

static int Retorna_Idx_Palavra_Vetor(char palavraUnica[], palavra** vetorDePalavras, int qtd) {
  int i = 0;
  //char aux[100];
  
  for (i = 0; i < qtd; i++) {
    
    if (!strcmp(palavraUnica, getPalavra(vetorDePalavras[i]))) return i;
  }
  return -1; // palavra não existe no vetor
}

static int Verifica_Palavra_Ja_Existe_Noticia(char palavraUnica[], palavra** vetorDePalavras, int qtd) {
  if (Retorna_Idx_Palavra_Vetor(palavraUnica, vetorDePalavras, qtd) == -1) return 0;
  else return 1;
}

int Le_Noticia_Unica(palavra** vetorDePalavras, FILE* arq, int tam) {
  char palavraUnica[100];
  int i = 0, qtd_De_Palavras_Dif_Lidas = 0;
  for (i = 0; !feof(arq); i++) {
    fscanf(arq, "%s", palavraUnica);
    if (!Verifica_Palavra_Ja_Existe_Noticia(palavraUnica, vetorDePalavras, tam)) {
      if (tam != 0) vetorDePalavras = realloc(vetorDePalavras, (tam+1)*sizeof(palavra*));
      vetorDePalavras[tam] = Inicializa_palavra(palavraUnica);
      tam++;
    } else {
      int idx = Retorna_Idx_Palavra_Vetor(palavraUnica, vetorDePalavras, tam);
      vetorDePalavras[idx]->frequencia++;
    }
  }
  return tam;
}
float tf_idf(float frequencia_palavra,int qtd_documentos, int num_doc_que_palavra_aparece){
  float TF_IDF=0, IDF=0, aux=0;
  aux=(1+qtd_documentos)/(1+num_doc_que_palavra_aparece);
  IDF=log(aux)+1;
  // frequencia palavra é em relação a palavra ao documento
  TF_IDF=frequencia_palavra*IDF;

  return TF_IDF;

}
