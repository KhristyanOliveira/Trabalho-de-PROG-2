#include "Documento.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct Documento {
  char *noticia; // A noticia por completo;
  int tam_noticia; // O tamanho da noticia(quantidade de caracteres que se tem na noticia);
  char* noticia_filtrada; // String que possui somente as palavras distintas;
  int qtd_palavras_distintas;//Quantidade de palavras distintas.
  int* posicao_da_palavra_na_noticia; // Armazena a posicao de cada palavra distinta(que e a posicao que a plavra aparece pela primeira vez);
  int* qtd_vezes_repetida; //Quantidade de vezes que se repete cada palavra distinta;
  float Tfidf; // Total;
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

static int CalculaQuntidadeCaracaters(char* noticia){
  int qtd;

  qtd=strlen(noticia);
  return qtd;
}

static int CalculaQuantidadePalavras(char* noticia, int qtd_caracteres){
  int qtd = 0;

  for(int i=0; i<qtd_caracteres; i++){
    if(noticia[i] == ' '){
      qtd++;
    }
  }
  qtd++;

  return qtd;
}

documento *Inicializa_Documento(char* noticia){
  documento *doc = malloc(sizeof(documento));
  doc->noticia = strdup(noticia);

  int qtd_caracteres_totais = CalculaQuntidadeCaracaters (noticia);
  //printf("Qtd_caracyeres:%d\n\n",qtd_caracteres_totais);

  doc->tam_noticia = qtd_caracteres_totais;

  int qtd_palavras_totais = CalculaQuantidadePalavras (noticia, qtd_caracteres_totais);
  printf("Qtd_palavras:%d\n\n",qtd_palavras_totais);

  int posicao_palavra[qtd_palavras_totais];
  int vezes_repitidas[qtd_palavras_totais];

  const char s[2] = " ";
  char *palavra_pointer;
  int x = 0;

  char palavras_noticia[qtd_palavras_totais][TAM_MAX_PALAVRA];
  char palavras_noticia_filtrada[qtd_palavras_totais][TAM_MAX_PALAVRA];
  
  /*
  palavra_pointer = strtok(noticia, s);

  while( palavra_pointer != NULL ) {
    //printf( " %s\n", palavra_pointer );
    strcpy(palavras_noticia[x], palavra_pointer);
    //AQUI A VARIAVEL palavra_pointer SERA CADA PALAVRA EM ORDEM NA NOTICIA.
    
    palavra_pointer = strtok(NULL, s);
    x++;
  }
  */
  

  /*printf("\n\nX: Z%d\n\n", x);

  FILE* matriz_palavras = fopen("matriz_palavras.txt", "w");

  for(int i=0; i<x; i++){

    fprintf(matriz_palavras,"Palavra %d: %s\n", i, palavras_noticia[i]);
  }

  fclose(matriz_palavras);*/


  int qtd_palavras_distintas = 0;

  /*
  for(int i=0; i < qtd_palavras_totais; i++){
    for(int j=0; j < qtd_palavras_totais; j++){
      //confere se sao iguais.
      if((strcmp(palavras_noticia[i], palavras_noticia[j])) == 0){
        //se sao iguai vou ver se ja a coloquei na minha matriz de palavras filtradas
        if(i == j){
          //strcpy(palavras_noticia_filtrada[qtd_palavras_distintas], palavras_noticia[j]);
          //posicao_palavra[contador] = j;
          qtd_palavras_distintas++;
        }
        else{
          break;
        }
        //se ela nao estiver na matriz de palavras, na posiçao qtd_palavras_distintas, adicionar esta palavra.
      }
    }
  }
  doc->qtd_palavras_distintas = qtd_palavras_distintas;
  printf("Qtd palavras distintas: %d\n\n", qtd_palavras_distintas);
  qtd_palavras_distintas = 0;

  */

  //printf("saiu");F

  /*
  printf("VETOR POSICOES DISTINTAS:");
  for(int j=0; j < qtd_palavras_distintas; j++){
    printf("%d, ", posicao_palavra[j]);
  }
  printf("\n\n");
  */

  //int *vetor_posicao_palavras_distintas;

  //vetor_posicao_palavras_distintas = posicao_palavra;

  doc->qtd_palavras_distintas = qtd_palavras_distintas;
  //doc-> posicao_da_palavra_na_noticia = posicao_palavra;

  
  return doc;
}

documento **Le_documento(int* tam_vet, char* dir){
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
  char caminhoArquivo[1000];
  char noticia[100000];
  FILE* saida_noticia = fopen("saida_noticia.txt", "w");

  /* Declarando o vetor de documentos */
  documento **doc = (documento **) malloc(1 * sizeof(documento*)); 

  for (i = 0; i < qtdLinhasArq; i++) {

    // leArquivo()
    // dir = "./small/train.txt"
    // dir incial quebra na segunda barra.
    
    sprintf(caminhoArquivo, "%s/%s", dirInicial, nomesArquivos[i]);
    FILE* arq2 = fopen(caminhoArquivo, "r");

    fprintf(saida_noticia,"\ndiretorio:%s\n\n", caminhoArquivo);
    fscanf(arq2, "%[^\n]", noticia);

    doc[i] = Inicializa_Documento(noticia);

    doc = realloc(doc, (i+2)*sizeof(documento*));

    fprintf(saida_noticia, "\nNoticia %d: %s\n\n", i, noticia);
        
    fclose(arq2);
  }
  fclose(saida_noticia);

  return doc;
}

void imprimeNoticia(documento** doc, int qtd) {
  FILE* tipo_doc = fopen("tipo_doc.txt", "w");

  for(int i =0; i< qtd; i++){
    fprintf(tipo_doc,"Noticia %d: %s\n", i, doc[i]->noticia);
    fprintf(tipo_doc,"Qtd_caracteres_totais: %d\n", i, doc[i]->tam_noticia);
    fprintf(tipo_doc,"Qtd_palavras_distintas: %d\n\n", i, doc[i]->qtd_palavras_distintas);
  }
  
  //fprintf(tipo_doc,"Palavra %d: %s\n",);

  fclose(tipo_doc);
}

void libera_documento(documento *documento){
  if(documento != NULL){
    free(documento->noticia);
    free(documento->noticia_filtrada);
    free(documento->posicao_da_palavra_na_noticia);
    free(documento->qtd_vezes_repetida);
  }
  free(documento);
}

void libera_Documentos(documento **documentos, int tamanho) {
  int i = 0;

  for(i=0; i<tamanho; i++) {
    libera_documento(documentos[i]);
  }
  free(documentos);
}