#include  <stdio.h>
#include  <stdlib.h>
#include "Documento.h"
#include "Palavra.h"


int main(int argc, char *argv[]) {
    documento **doc;
    palavra **word;
    int tamanho_vet, qtd_palavras;

    char diretorio1[1000];
    sprintf(diretorio1, "%s", argv[1]);

    /*
    doc = Le_documento(&tamanho_vet, argv[1]);

    printf("Quantida de noticias: %d\n\n", tamanho_vet);

    imprimeNoticia(doc, tamanho_vet);

    libera_Documentos(doc,tamanho_vet);
    */

   
   word = Le_Palavra(&tamanho_vet, argv[1],&qtd_palavras);
   printf("Quantida de noticias: %d\n", tamanho_vet);
   printf("Quantida de palavras: %d\n\n", qtd_palavras);
   

    return 0;
}