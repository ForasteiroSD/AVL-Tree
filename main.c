#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"

int main() {
    char nomeArquivo[30] = {"entrada.txt"};
    avl *arv;
    int elemRem;

    arv = criaArvore();
    processaCarga(arv, nomeArquivo);
    imprimePreOrdem(getRaiz(arv));
    printf("\n%d\n", getNumElementos(arv));

    free(arv);
}